/*
    'Sup? Counting byte offsets by hand was cute until the loop grew legs and
    moved everu fucking jump
    So here is a tiny assembler for bytecode_advanced.c.

    Two passes: first we collect labels and measure instructions then we turn
    the actual instructions into bytes
    Forward jumps get to exist now
    Labels are case-sensitive instructions are uppercase. ';' starts a comment (like asm I knowwww).
    Numbers are unsigned decimal or 0x-prefixed hexadecimal. Jumps take labels.

    Build: cc -std=c11 -Wall -Wextra -Wpedantic assembler.c -o assembler
    Run:   ./assembler example.asm program.bin

*/

/*INCLUDES*/
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>
#include <string.h>
#include <ctype.h>
#include <errno.h>
#include <sys/stat.h> //Don't let two paths to the same file eat the source

/*DEFINES*/
//Input and VM limits
#define LINE_SIZE 512
#define LABEL_LIMIT 1024
#define LABEL_SIZE 64
#define CODE_LIMIT 65536
#define LOCAL_COUNT 16

/*OBJECTS*/
//Order matters: these values have to match bytecode_advanced.c exactly 'cuz reasons...
enum opcode {
    OP_INC, OP_DEC, OP_ADDI, OP_SUBI, OP_DONE, OP_LOADI, OP_MULI,
    OP_DIVI, OP_PUSH, OP_POP, OP_STORE, OP_LOAD, OP_JMP, OP_JZ
};

struct Instruction {
    const char *name;
    enum opcode opcode;
    unsigned int operand_size;
};

struct Label {
    char name[LABEL_SIZE];
    size_t offset;
};

/*FUNCTION PROTOTYPES*/
static int assemble(FILE *input, uint8_t *code, size_t *code_size);
static int validLabel(const char *name);
static int parseNumber(const char *text, uint64_t *value);
static const struct Instruction *findInstruction(const char *name);

/*MAIN*/
int main(int argc, char **argv)
{
    int retValue = 0;
    
    FILE *input = NULL;
    FILE *output = NULL;
    
    uint8_t *code = NULL;
    size_t code_size = 0;
    struct stat input_stat, output_stat;

    if (argc != 3) {
        fprintf(stderr, "Usage: %s input.asm output.bin\n", argv[0]);
        return(13);
    }

    input = fopen(argv[1], "r");
    if (input == NULL) { perror(argv[1]); return(-13); }
    code = (uint8_t *)malloc(CODE_LIMIT);
    if (code == NULL) { perror("malloc"); retValue = -1; goto cleanUp; }
    retValue = assemble(input, code, &code_size);
    if (retValue != 0) { goto cleanUp; }

    //Don't truncate the source just because certain someone fucking passed it twice
    if (strcmp(argv[1], argv[2]) == 0 ||
        (stat(argv[1], &input_stat) == 0 && stat(argv[2], &output_stat) == 0 &&
         input_stat.st_dev == output_stat.st_dev && input_stat.st_ino == output_stat.st_ino)) {

        fprintf(stderr, "Input and output must be different files.\n");

        retValue = 13;
        goto cleanUp;
    }

    output = fopen(argv[2], "wb");

    if (output == NULL) { perror(argv[2]); retValue = -13; goto cleanUp; }
    if (fwrite(code, 1, code_size, output) != code_size) {
        perror("writing bytecode"); retValue = -13;
    }

cleanUp:
    
if (output != NULL && fclose(output) != 0) { perror("closing output"); retValue = -13; }
    
    if (fclose(input) != 0) { perror("closing input"); retValue = -13; }
    
    free(code);
    
    return(retValue);
}

/*FUNCTION BODIES*/
//Parsing and encoding
static int assemble(FILE *input, uint8_t *code, size_t *code_size)
{
    struct Label labels[LABEL_LIMIT];
    size_t label_count = 0;
    size_t offset = 0;
    char line[LINE_SIZE];

    for (int pass = 0; pass < 2; pass++) {
        
        size_t line_number = 0;
        
        offset = 0;
        
        if (fseek(input, 0, SEEK_SET) != 0) { perror("rewinding input"); return(-13); }
        while (fgets(line, sizeof(line), input) != NULL) {
            
            char *comment, *token, *operand, *extra;
            
            const struct Instruction *instruction;
            
            size_t len;
            
            uint64_t value = 0;
            
            line_number++;
            len = strlen(line);
            
            if (len == sizeof(line) - 1 && line[len - 1] != '\n') {
                fprintf(stderr, "Line %zu: line too long.\n", line_number); return(13);
            }
            
            comment = strchr(line, ';');
            
            if (comment != NULL) { *comment = '\0'; }
            
            token = strtok(line, " \t\r\n");
            
            if (token == NULL) { continue; }
            
            len = strlen(token);
            
            if (token[len - 1] == ':') {
                token[len - 1] = '\0';
            
                if (!validLabel(token)) {
                    fprintf(stderr, "Line %zu: invalid label.\n", line_number); return(13);
                }
            
                if (pass == 0) {
            
                    for (size_t i = 0; i < label_count; i++) {
            
                        if (strcmp(labels[i].name, token) == 0) {
                            fprintf(stderr, "Line %zu: duplicate label '%s'.\n", line_number, token); return(13);
                        }
                    }
            
                    if (label_count == LABEL_LIMIT || offset >= CODE_LIMIT) {
                        fprintf(stderr, "Line %zu: label limit or address exceeded.\n", line_number); return(13);
                    }
            
                    strcpy(labels[label_count].name, token);
                    labels[label_count++].offset = offset;
                }
            
                token = strtok(NULL, " \t\r\n");
            
                if (token == NULL) { continue; }
            }
            
            instruction = findInstruction(token);
            operand = strtok(NULL, " \t\r\n");
            extra = strtok(NULL, " \t\r\n");
            
            if (instruction == NULL || extra != NULL ||
                
                (instruction->operand_size == 0 && operand != NULL) ||
                (instruction->operand_size != 0 && operand == NULL)) {
            
                fprintf(stderr, "Line %zu: unknown instruction or wrong operands.\n", line_number); return(13);
            }
            
            if (offset > CODE_LIMIT - 1 - instruction->operand_size) {
                fprintf(stderr, "Line %zu: program is too big.\n", line_number); return(13);
            }

            if (instruction->opcode == OP_JMP || instruction->opcode == OP_JZ) {
                
                if (!validLabel(operand)) {
                    fprintf(stderr, "Line %zu: jump expects a label.\n", line_number); return(13);
                }

                if (pass == 1) {
                    size_t i;
                    
                    for (i = 0; i < label_count && strcmp(labels[i].name, operand) != 0; i++) { }
                    
                    if (i == label_count || labels[i].offset >= *code_size) {
                        fprintf(stderr, "Line %zu: missing label or jump to end: '%s'.\n", line_number, operand); return(13);
                    }
                    
                    value = labels[i].offset;
                }
            } else if (instruction->operand_size != 0) {
                if (!parseNumber(operand, &value) ||
                    (instruction->operand_size == 1 && value > UINT8_MAX) ||
                    ((instruction->opcode == OP_LOAD || instruction->opcode == OP_STORE) && value >= LOCAL_COUNT)) {
                    
                        fprintf(stderr, "Line %zu: invalid or out-of-range operand.\n", line_number); return(13);
                }
            }

            if (pass == 1) {
                code[offset] = (uint8_t)instruction->opcode;
                //Little endian: least significant byte goes first yk
                for (unsigned int i = 0; i < instruction->operand_size; i++) {
                    code[offset + 1 + i] = (uint8_t)(value >> (8 * i));
                }
            }
            offset += 1 + instruction->operand_size;
        }
    
        if (ferror(input)) { perror("reading input"); return(-13); }
        if (pass == 0) { *code_size = offset; }
    }
    if (offset == 0) { fprintf(stderr, "Empty program.\n"); return(13); }
    
    return(0);
}

//Helpers
static int validLabel(const char *name)
{
    size_t len = strlen(name);
    
    if (len == 0 || len >= LABEL_SIZE || !(isalpha((unsigned char)name[0]) || name[0] == '_')) { return(0); }
    
    for (size_t i = 1; i < len; i++) {
        if (!(isalnum((unsigned char)name[i]) || name[i] == '_')) { return(0); }
    }
    
    return(1);
}

static int parseNumber(const char *text, uint64_t *value)
{
    char *end;
    
    uintmax_t parsed;
    
    int base = 10;
    
    if (!isdigit((unsigned char)text[0])) { return(0); }
    if (text[0] == '0' && (text[1] == 'x' || text[1] == 'X')) { base = 16; }
    
    errno = 0;
    parsed = strtoumax(text, &end, base);
    
    if (errno == ERANGE || *end != '\0' || parsed > UINT64_MAX) { return(0); }
    
    *value = (uint64_t)parsed;
    
    return(1);
}

static const struct Instruction *findInstruction(const char *name)
{
    
    static const struct Instruction instructions[] = {
        {"INC", OP_INC, 0}, {"DEC", OP_DEC, 0}, {"ADDI", OP_ADDI, 1},
        {"SUBI", OP_SUBI, 1}, {"DONE", OP_DONE, 0}, {"LOADI", OP_LOADI, 8},
        {"MULI", OP_MULI, 1}, {"DIVI", OP_DIVI, 1}, {"PUSH", OP_PUSH, 0},
        {"POP", OP_POP, 0}, {"STORE", OP_STORE, 1}, {"LOAD", OP_LOAD, 1},
        {"JMP", OP_JMP, 2}, {"JZ", OP_JZ, 2}
    };
    
    for (size_t i = 0; i < sizeof(instructions) / sizeof(instructions[0]); i++) {
        if (strcmp(name, instructions[i].name) == 0) { return(&instructions[i]); }
    }

    return(NULL);
}
