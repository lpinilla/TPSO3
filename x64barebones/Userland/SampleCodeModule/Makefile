include ../Makefile.inc

MODULE=0000-sampleCodeModule.bin
SOURCES=$(wildcard [^_]*.c)
SOURCES_ASM=$(wildcard asm/*.asm)

OBJECTS=$(SOURCES:.c=.o)
OBJECTS_ASM=$(SOURCES_ASM:.asm=.o)

%.o: %.c
	$(GCC) $(GCCFLAGS) -I./include -c _loader.c $(SOURCES)

%.o : %.asm
	$(ASM) $(ASMFLAGS) $< -o $@

all: $(MODULE)

$(MODULE): $(OBJECTS) $(OBJECTS_ASM)
	$(LD) -T sampleCodeModule.ld _loader.o $(OBJECTS) $(OBJECTS_ASM) -o ../$(MODULE)
	$(LD) -T sampleCodeModule.ld _loader.o $(OBJECTS) $(OBJECTS_ASM) --oformat=elf64-x86-64 -o ../sampleCodeModule.elf


clean:
	rm -rf *.o

.PHONY: all clean print
