; Count down from 5, adding 3 to local 1 each time. Result: 15.
ADDI 5
STORE 0
loop: LOAD 0
JZ finished
DEC
STORE 0
LOAD 1
ADDI 3
STORE 1
JMP loop
finished: LOAD 1
DONE
