# Makefile - compile all .c files to .asm (cc -S)

# Find all .c files in current dir
SOURCES := $(wildcard *.c)

# Replace .c with .asm for output files
ASMS := $(SOURCES:.c=.asm)

# Default target: build all .asm files
all: $(ASMS)

# Rule: how to turn one .c into .asm
%.asm: %.c
	cc -S $< -o $@ -masm=intel   # -masm=intel gives nicer Intel syntax (optional but recommended)
	@echo "Assembled $@ from $< 🔥"

# Clean up all generated .asm files
clean:
	rm -f *.asm
	@echo "Cleaned all .asm files, fresh start brö"

.PHONY: all clean