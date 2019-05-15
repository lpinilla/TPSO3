TASTEFUL = tasteful

GCC = gcc
NASM = nasm
ASMFLAGS = -f elf64
CFLAGS = -Wall -g -std=gnu99

#------------------
TARGETS = mem_manager_test ipc_test lib_test
SOURCES = ../Tasteful/testing_suite ../x64barebones/Kernel/mem_manager ../x64barebones/Userland/SampleCodeModule/mem_manager ../x64barebones/Userland/SampleCodeModule/syscall ../x64barebones/Kernel/ipc ../x64barebones/Kernel/lib
ASM_FILES = ../x64barebones/Userland/SampleCodeModule/asm/call_int_80


all: clean $(TARGETS)

$(TARGETS):
	@$(NASM) $(ASMFLAGS) $(ASM_FILES:=.asm) -o $(ASM_FILES:=.o)
	@$(GCC) $(CFLAGS) $(SOURCES:=.c) $(ASM_FILES:=.o) $@.c -o $@.tasty -lrt

clean:
	@rm -f $(TARGETS) $(TARGETS:=.o) $(TARGETS:=.tasty)
	@rm -f $(SOURCES) $(SOURCES:=.o)

test: all $(TARGETS)
	@$(GCC) $(CFLAGS) ../Tasteful/$(TASTEFUL:=.c) -o $(TASTEFUL)
	@./tasteful

.PHONY: all, clean, test