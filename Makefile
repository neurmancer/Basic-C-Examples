# Makefile - compile all .c files to .asm (cc -S)

# Find all .c files in current dir
SOURCES := $(wildcard *.c)

# Replace .c with .asm for output files
SS := $(SOURCES:.c=.s)

# Default target: build all .asm files
all: $(ASMS)

# Rule: how to turn one .c into .asm
%.asm: %.c
	cc -S $< -o $@ -masm=intel   # 
	@echo "Assembled $@ from $<"


clean:
	rm -f *.asm
	@echo "Cleaned all .asm files, fresh start bro"

.PHONY: all clean