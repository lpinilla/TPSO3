#include <stdint.h>
#include <string.h>
#include <lib.h>
#include <moduleLoader.h>
#include <naiveConsole.h>
#include <graphics.h>
#include <time.h>
#include <idt_loader.h>
#include <mem_manager.h>
#include <process.h>
#include <scheduler.h>
#include <semaphore.h>
#include <interrupts.h>
#include <ipc.h>

extern uint8_t text;
extern uint8_t rodata;
extern uint8_t data;
extern uint8_t bss;
extern uint8_t endOfKernelBinary;
extern uint8_t endOfKernel;
static const uint64_t PageSize = 0x1000;

static void * const sampleCodeModuleAddress = (void*)0x400000;
static void * const sampleDataModuleAddress = (void*)0x500000;
static void * const memory_location = (void *)0x700000;

typedef int (*EntryPoint)();

void initial_info(void);

void clearBSS(void * bssAddress, uint64_t bssSize)
{
	memset(bssAddress, 0, bssSize);
}

void * getStackBase()
{
	return (void*)(
		(uint64_t)&endOfKernel
		+ PageSize * 8				//The size of the stack itself, 32KiB
		- sizeof(uint64_t)			//Begin at the top of the stack
	);
}

void * initializeKernelBinary(){
	
	void * moduleAddresses[] = {
		sampleCodeModuleAddress,
		sampleDataModuleAddress
	};

	loadModules(&endOfKernelBinary, moduleAddresses);
	clearBSS(&bss, &endOfKernel - &bss);


	initialize_list(memory_location, 1024*1024*100); // 100 Mb
	init_graphics();
	init_scheduler();
	init_semaphores();
	init_processes();
	init_mailbox();
	
	load_idt();

	return getStackBase();
}

void init(){
	clear_screen();
	//ACA ES DONDE SALTA A USERLAND, COMENTAR ESTA LINEA SI QUEREMOS PROBAR COSAS DE KERNEL
	uint64_t start = (uint64_t)((EntryPoint)sampleCodeModuleAddress);
	process_t process = create_process(start, "shell", 2);
	run_process(process);
}

int main()
{
	init();
	
	return 0;
}

