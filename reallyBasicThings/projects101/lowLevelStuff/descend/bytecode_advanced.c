/*
    Sup? the first VM could add and subtract. Cool. It could also walk straight
    off the bytecode buffer if we forgot OP_DONE. Less cool.

    So here's the same little accumulator machine with some actual boundaries,
    a stack, local slots and jumps. Enough to run a loop without trusting every
    damn byte somebody hands us. Still no typedefs. Linus doctrine continues.

    Build: cc -std=c11 -Wall -Wextra -Wpedantic bytecode_advanced.c -o bytecode_advanced
    Run:   ./bytecode_advanced

    Bytecode format (bytes, not native C structs):
      INC/DEC/DONE/PUSH/POP: opcode only
      ADDI/SUBI/MULI/DIVI: opcode + unsigned 8-bit immediate
      STORE/LOAD: opcode + unsigned 8-bit local slot index
      LOADI: opcode + unsigned 64-bit immediate, little endian
      JMP/JZ: opcode + unsigned 16-bit ABSOLUTE byte offset, little endian

    Arithmetic wraps modulo 2^64, just like the original uint64_t accumulator.
    JZ tests the accumulator; PUSH/STORE leave it alone; POP/LOAD replace it.
    Locals start at zero on every run. Falling off the program is an error.
    All bytes must decode, even unreachable ones. Jumps must land on opcodes.
    No files, compiler or JIT here yet. One educational VM, not a whole OS lol.
*/

#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>
#include <stddef.h>
#include <stdlib.h>

#define STACK_CAPACITY 64
#define LOCAL_COUNT 16

/* Keep the original five values so its little programs still work. */
enum opcode {
    OP_INCREMENT, OP_DECREMENT, OP_ADDI, OP_SUBI, OP_DONE,
    OP_LOADI, OP_MULI, OP_DIVI, OP_PUSH, OP_POP,
    OP_STORE, OP_LOAD, OP_JMP, OP_JZ
};

enum interpret_res {
    SUCCESS, ERR_UKNWN_OP_CODE, ERR_BAD_ARGUMENT, ERR_TRUNCATED,
    ERR_NO_DONE, ERR_BAD_JUMP, ERR_BAD_LOCAL, ERR_STACK_OVERFLOW,
    ERR_STACK_UNDERFLOW, ERR_DIV_ZERO, ERR_STEP_LIMIT
};

struct vm {
    size_t ip;             //offset, so we can actually check the fucking thing
    size_t fault_ip;       //offending opcode (or end of buffer for ERR_NO_DONE)
    size_t steps;
    uint64_t accumulator;
    uint64_t stack[STACK_CAPACITY];
    size_t sp;             //number of live entries, not the last entry's index
    uint64_t locals[LOCAL_COUNT];
};

static void vm_reset(struct vm *vm)
{
    *vm = (struct vm) {0};  //plain C11. No typeof needed for a named struct.
}

static size_t instruction_size(uint8_t op)
{
    switch (op) {
    case OP_INCREMENT: case OP_DECREMENT: case OP_DONE:
    case OP_PUSH: case OP_POP:
        return 1;
    case OP_ADDI: case OP_SUBI: case OP_MULI: case OP_DIVI:
    case OP_STORE: case OP_LOAD:
        return 2;
    case OP_JMP: case OP_JZ:
        return 3;
    case OP_LOADI:
        return 9;
    default:
        return 0;
    }
}

static size_t jump_target(const uint8_t *operand)
{
    return (size_t)operand[0] | ((size_t)operand[1] << 8);
}

/* Only called AFTER the first pass proves every instruction is complete.
   Walking the program saves an allocation here; a bigger VM wants a bitmap. */
static int is_instruction(const uint8_t *code, size_t length, size_t target)
{
    size_t ip = 0;

    if (target >= length)
        return 0;
    while (ip < target)
        ip += instruction_size(code[ip]);
    return ip == target;
}

static enum interpret_res validate(struct vm *vm, const uint8_t *code,
                                   size_t length)
{
    size_t ip;

    for (ip = 0; ip < length; ) {
        size_t width = instruction_size(code[ip]);

        vm->fault_ip = ip;
        if (width == 0)
            return ERR_UKNWN_OP_CODE;
        if (width > length - ip) //subtract first; ip + width could overflow
            return ERR_TRUNCATED;
        if ((code[ip] == OP_STORE || code[ip] == OP_LOAD) &&
            code[ip + 1] >= LOCAL_COUNT)
            return ERR_BAD_LOCAL;
        ip += width;
    }

    for (ip = 0; ip < length; ip += instruction_size(code[ip])) {
        if (code[ip] == OP_JMP || code[ip] == OP_JZ) {
            vm->fault_ip = ip;
            if (!is_instruction(code, length, jump_target(code + ip + 1)))
                return ERR_BAD_JUMP;
        }
    }
    vm->fault_ip = 0;
    return SUCCESS;
}

/* code must point to length readable bytes and stay unchanged during this call.
   Every call starts fresh. On failure, inspect fault_ip and the partial state.
   step_limit counts dispatched instructions, including OP_DONE. */
static enum interpret_res vm_interpret(struct vm *vm, const uint8_t *code,
                                       size_t length, size_t step_limit)
{
    enum interpret_res rc;

    if (vm == NULL)
        return ERR_BAD_ARGUMENT;
    vm_reset(vm);
    if (code == NULL)
        return ERR_BAD_ARGUMENT;
    rc = validate(vm, code, length);
    if (rc != SUCCESS)
        return rc;

    for (;;) {
        uint8_t op;
        size_t operand;

        vm->fault_ip = vm->ip;
        if (vm->ip == length)
            return ERR_NO_DONE;
        if (vm->steps == step_limit)
            return ERR_STEP_LIMIT; //while (1) doesn't get to hold us hostage

        op = code[vm->ip];
        operand = vm->ip + 1;
        vm->ip += instruction_size(op);
        vm->steps++;

        switch (op) {
        case OP_INCREMENT:
            vm->accumulator++;
            break;
        case OP_DECREMENT:
            vm->accumulator--;
            break;
        case OP_ADDI:
            vm->accumulator += code[operand];
            break;
        case OP_SUBI:
            vm->accumulator -= code[operand];
            break;
        case OP_LOADI:
            vm->accumulator = 0;
            for (size_t i = 0; i < 8; i++)
                vm->accumulator |= (uint64_t)code[operand + i] << (8 * i);
            break; //no unaligned pointer casts or host-endianness bullshit
        case OP_MULI:
            vm->accumulator *= code[operand];
            break;
        case OP_DIVI:
            if (code[operand] == 0)
                return ERR_DIV_ZERO;
            vm->accumulator /= code[operand];
            break;
        case OP_PUSH:
            if (vm->sp == STACK_CAPACITY)
                return ERR_STACK_OVERFLOW;
            vm->stack[vm->sp++] = vm->accumulator;
            break;
        case OP_POP:
            if (vm->sp == 0)
                return ERR_STACK_UNDERFLOW;
            vm->accumulator = vm->stack[--vm->sp];
            break;
        case OP_STORE:
            vm->locals[code[operand]] = vm->accumulator;
            break;
        case OP_LOAD:
            vm->accumulator = vm->locals[code[operand]];
            break;
        case OP_JMP:
            vm->ip = jump_target(code + operand);
            break;
        case OP_JZ:
            if (vm->accumulator == 0)
                vm->ip = jump_target(code + operand);
            break;
        case OP_DONE:
            return SUCCESS;
        default:
            return ERR_UKNWN_OP_CODE;
        }
    }
}

static const char *result_name(enum interpret_res rc)
{
    switch (rc) {
    case SUCCESS: return "success";
    case ERR_UKNWN_OP_CODE: return "unknown opcode";
    case ERR_BAD_ARGUMENT: return "bad argument";
    case ERR_TRUNCATED: return "truncated operand";
    case ERR_NO_DONE: return "ran out of code before OP_DONE";
    case ERR_BAD_JUMP: return "jump doesn't land on an instruction";
    case ERR_BAD_LOCAL: return "local slot out of range";
    case ERR_STACK_OVERFLOW: return "stack overflow";
    case ERR_STACK_UNDERFLOW: return "stack underflow";
    case ERR_DIV_ZERO: return "division by zero";
    case ERR_STEP_LIMIT: return "instruction budget exhausted";
    default: return "unknown result";
    }
}

/* These checks still run with -DNDEBUG. assert disappearing would be awkward. */
static int check(const char *name, const uint8_t *code, size_t length,
                 size_t budget, enum interpret_res expected, uint64_t value,
                 size_t fault)
{
    struct vm vm;
    enum interpret_res rc = vm_interpret(&vm, code, length, budget);

    if (rc != expected || vm.accumulator != value ||
        (rc != SUCCESS && vm.fault_ip != fault)) {
        fprintf(stderr, "%s: got %s, accumulator=%" PRIu64 ", byte=%zu\n",
                name, result_name(rc), vm.accumulator, vm.fault_ip);
        return 1;
    }
    return 0;
}

int main(void)
{
    struct vm vm;
    int failures = 0;
    enum interpret_res rc;

    /* Count down from 5. Each lap adds 3 to local 1. Result: 15.
       Byte offsets are written out because counting these by eye sucks. */
    const uint8_t loop[] = {
        /*  0 */ OP_ADDI, 5,
        /*  2 */ OP_STORE, 0,
        /*  4 */ OP_LOAD, 0,
        /*  6 */ OP_JZ, 24, 0,
        /*  9 */ OP_DECREMENT,
        /* 10 */ OP_STORE, 0,
        /* 12 */ OP_LOAD, 1,
        /* 14 */ OP_ADDI, 3,
        /* 16 */ OP_STORE, 1,
        /* 18 */ OP_LOAD, 0,
        /* 20 */ OP_JMP, 6, 0,
        /* 23 */ OP_DONE, //unreachable but still valid bytecode
        /* 24 */ OP_LOAD, 1,
        /* 26 */ OP_DONE
    };

    rc = vm_interpret(&vm, loop, sizeof(loop), 1000);
    printf("vm state: %" PRIu64 " (%s, %zu instructions)\n",
           vm.accumulator, result_name(rc), vm.steps);
    if (rc != SUCCESS || vm.accumulator != 15 || vm.locals[0] != 0 ||
        vm.locals[1] != 15 || vm.steps != 46)
        failures++;

    {
        const uint8_t code[] = {OP_INCREMENT, OP_INCREMENT, OP_DECREMENT, OP_DONE};
        failures += check("original inc/dec", code, sizeof(code), 4, SUCCESS, 1, 0);
    }
    {
        const uint8_t code[] = {OP_ADDI, 10, OP_SUBI, 3, OP_DONE};
        failures += check("original immediates", code, sizeof(code), 3, SUCCESS, 7, 0);
    }
    {
        const uint8_t code[] = {
            OP_LOADI, 8, 7, 6, 5, 4, 3, 2, 1,
            OP_PUSH, OP_ADDI, 9, OP_PUSH, OP_POP, OP_POP, OP_DONE
        };
        failures += check("wide load / LIFO stack", code, sizeof(code), 20,
                          SUCCESS, UINT64_C(0x0102030405060708), 0);
    }
    {
        const uint8_t code[] = {OP_ADDI, 7, OP_MULI, 6, OP_DIVI, 2, OP_DONE};
        failures += check("multiply / divide", code, sizeof(code), 4, SUCCESS, 21, 0);
    }
    {
        const uint8_t code[] = {OP_DECREMENT, OP_DONE};
        failures += check("unsigned wrap", code, sizeof(code), 2, SUCCESS, UINT64_MAX, 0);
    }

    /* Now feed it garbage on purpose. This is where the first VM got spicy. */
    {
        const struct {
            const char *name;
            uint8_t code[5];
            size_t length;
            size_t budget;
            enum interpret_res expected;
            size_t fault;
        } cases[] = {
            {"unknown opcode", {255}, 1, 10, ERR_UKNWN_OP_CODE, 0},
            {"short immediate", {OP_ADDI}, 1, 10, ERR_TRUNCATED, 0},
            {"short wide load", {OP_LOADI, 1}, 2, 10, ERR_TRUNCATED, 0},
            {"short jump", {OP_JMP, 0}, 2, 10, ERR_TRUNCATED, 0},
            {"empty program", {0}, 0, 10, ERR_NO_DONE, 0},
            {"missing done", {OP_ADDI, 0}, 2, 10, ERR_NO_DONE, 2},
            {"jump into operand", {OP_JMP, 1, 0}, 3, 10, ERR_BAD_JUMP, 0},
            {"jump to end", {OP_JMP, 3, 0}, 3, 10, ERR_BAD_JUMP, 0},
            {"far jump", {OP_JMP, 255, 255}, 3, 10, ERR_BAD_JUMP, 0},
            {"bad conditional", {OP_JZ, 1, 0}, 3, 10, ERR_BAD_JUMP, 0},
            {"bad store", {OP_STORE, LOCAL_COUNT}, 2, 10, ERR_BAD_LOCAL, 0},
            {"bad load", {OP_LOAD, LOCAL_COUNT}, 2, 10, ERR_BAD_LOCAL, 0},
            {"empty stack", {OP_POP, OP_DONE}, 2, 10, ERR_STACK_UNDERFLOW, 0},
            {"zero divisor", {OP_DIVI, 0, OP_DONE}, 3, 10, ERR_DIV_ZERO, 0},
            {"endless loop", {OP_JMP, 0, 0}, 3, 10, ERR_STEP_LIMIT, 0},
            {"zero budget", {OP_DONE}, 1, 0, ERR_STEP_LIMIT, 0},
            {"budget before done", {OP_ADDI, 0, OP_DONE}, 3, 1, ERR_STEP_LIMIT, 2},
            {"invalid dead code", {OP_DONE, 255}, 2, 10, ERR_UKNWN_OP_CODE, 1},
            {"fault offset", {OP_ADDI, 0, OP_POP}, 3, 10, ERR_STACK_UNDERFLOW, 2}
        };

        for (size_t i = 0; i < sizeof(cases) / sizeof(cases[0]); i++)
            failures += check(cases[i].name, cases[i].code, cases[i].length,
                              cases[i].budget, cases[i].expected, 0, cases[i].fault);
    }
    {
        uint8_t code[STACK_CAPACITY + 2];

        for (size_t i = 0; i < STACK_CAPACITY + 1; i++)
            code[i] = OP_PUSH;
        code[STACK_CAPACITY + 1] = OP_DONE;
        failures += check("full stack", code, sizeof(code), 100,
                          ERR_STACK_OVERFLOW, 0, STACK_CAPACITY);
        code[STACK_CAPACITY] = OP_DONE;
        failures += check("exact stack capacity", code, STACK_CAPACITY + 1, 100,
                          SUCCESS, 0, 0);
    }
    {
        const uint8_t code[] = {OP_LOAD, 1, OP_DONE};

        /* Reuse the loop's VM. Old locals, stack and counters must disappear. */
        rc = vm_interpret(&vm, code, sizeof(code), 2);
        if (rc != SUCCESS || vm.accumulator != 0 || vm.sp != 0 || vm.steps != 2)
            failures++;
        failures += check("null bytecode", NULL, 0, 10, ERR_BAD_ARGUMENT, 0, 0);
        if (vm_interpret(NULL, code, sizeof(code), 10) != ERR_BAD_ARGUMENT)
            failures++;
    }

    if (failures != 0) {
        fprintf(stderr, "%d checks failed. Well, shit.\n", failures);
        return EXIT_FAILURE;
    }
    puts("All checks passed. Tiny VM, slightly less sketchy now.");
    return EXIT_SUCCESS;
}
