/*
    Sup? arm's still broken so...less commentary it is but I gotta start workin on the futureShit.md so... we're building the most basic bytecode interpreter 

    Found this awesome article: https://medium.com/bumble-tech/home-grown-bytecode-interpreters-51e12d59b25c

    and I've started questioning what 'Good programmer' is. A person who knows the stack bottom-up? A person can code without referance? A person
    with years of experience? or someone can get the shit to work by any means? I mean what's the difference between following a tutorial and prompting an AI?


    no fucking clue...

    btw again we're going with linus doctrine without using typedefs
*/


#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>
#include <assert.h>

struct {

    uint8_t *ip;
    uint64_t accumulator; //the (only) register 
}vm;  //our 'virtual machine'


enum opcode {OP_INCREMENT, OP_DECREMENT,OP_ADDI, OP_SUBI, OP_DONE};
enum interpret_res {SUCCESS, ERR_UKNWN_OP_CODE};

void vm_reset(void);
enum interpret_res vm_interpret(uint8_t *bytecode); //Main event



int main(void)
{

    {
            //the original program uses these scope curlies so I'll follow the pattern
            uint8_t code[] = {OP_INCREMENT, OP_INCREMENT,OP_DECREMENT,OP_DONE};
            enum interpret_res rc = vm_interpret(code);
            
            printf("vm state: %" PRIu64 "\n", vm.accumulator);   //I have no clue why we have a macro for "lu" is it because this is long int?
            assert(rc == SUCCESS);
            assert(vm.accumulator == 1); 
    }
    
    {
        uint8_t code[] = { OP_ADDI, 10, OP_SUBI, 3, OP_DONE };
        enum interpret_res rc = vm_interpret(code);
        printf("vm state: %" PRIu64 "\n", vm.accumulator);

        assert(rc == SUCCESS);
        assert(vm.accumulator == 7);
    }


    //well... that was the most basic bytecode interpreter I guess... is this even worth it to mark as done?
    return(0);
}


void vm_reset(void)
{
    puts("VM state reset");
    vm = (typeof(vm)) { 0 }; 
}

enum interpret_res vm_interpret(uint8_t *bytecode)
{
    vm_reset();
    puts("Interpret started I guess...");

    vm.ip = bytecode;

    while (1) {
        uint8_t ins = *vm.ip++;
        switch (ins) {
            
            case OP_INCREMENT: {
                vm.accumulator++;
                break;
            }
            
            case OP_DECREMENT:{
                vm.accumulator--;
                break;
            }
            
            case OP_ADDI:{
                uint8_t arg = *vm.ip++;
                vm.accumulator += arg;    //Inc by the arg val
                break;
            }
            
            case OP_SUBI:{
                uint8_t arg = *vm.ip++;
                vm.accumulator -= arg;    //decr by the arg val
                break;
            }
            
            case OP_DONE:{
                return(SUCCESS);
            }
            
            default: 
                return(ERR_UKNWN_OP_CODE);
        }
    }
    return(SUCCESS);
}
