#include <process.h>
#include <scheduler.h>
#include <mem_manager.h>
#include <graphics.h>
#include <interrupts.h>
#include <files.h>
#include <keyboard.h>

static void init_fds(process_t process);

typedef struct fd_infoADT {
    inode_t file;
    fd_t type;
}fd_infoADT;

typedef struct processADT {
	char * name[MAX_PROCESS_NAME];
    size_t pid;
	size_t ppid;
    pstate_t state;
	uint64_t stack_start;
    uint64_t stack_pointer;
	int priority;
	fd_info_t fds[MAX_FD];
} processADT;

typedef struct {
	//Registers restore context
	uint64_t gs;
	uint64_t fs;
	uint64_t r15;
	uint64_t r14;
	uint64_t r13;
	uint64_t r12;
	uint64_t r11;
	uint64_t r10;
	uint64_t r9;
	uint64_t r8;
	uint64_t rsi;
	uint64_t rdi;
	uint64_t rbp;
	uint64_t rdx;
	uint64_t rcx;
	uint64_t rbx;
	uint64_t rax;

	//iretq hook
	uint64_t rip;
	uint64_t cs;
	uint64_t eflags;
	uint64_t rsp;
	uint64_t ss;
	uint64_t base;
}stack_t;

static uint64_t init_stack(process_t process, uint64_t process_start, uint64_t stack_pointer); 
static void process_caller(process_t process, uint64_t process_start);
static uint64_t init_stack_args(process_t process, uint64_t process_start, uint64_t stack_pointer, int argc, void ** argv); 
static void process_caller_args(process_t process, uint64_t process_start, int argc, void ** argv);

static size_t global_pid;
static process_t all_processes[MAX_PROCESSES];
static process_t foreground_process;

void init_processes(){
	global_pid = 0;
	foreground_process = NULL;
	for(int i = 0; i < MAX_PROCESSES; i++){
		all_processes[i] = NULL;
	}
}

process_t create_process(uint64_t process_start, char * process_name, int priority){

    process_t new_process = (process_t)mem_alloc(sizeof(*new_process));
	str_cpy(process_name, (char*)(new_process->name));
    new_process->pid = global_pid;
    new_process->state = P_READY;
	new_process->stack_start = (uint64_t)mem_alloc(STACK_SIZE);
    new_process->stack_pointer = init_stack(new_process, process_start, new_process->stack_start);
	new_process->priority = priority;
	init_fds(new_process);
	if(global_pid != 0){
		new_process->ppid = get_current_process()->pid;
	}
	else{
		foreground_process = new_process;
		new_process->ppid = 0;
	}

	all_processes[global_pid++] = new_process;

    return new_process;
}

process_t create_process_args(uint64_t process_start, char * process_name, int argc, void ** argv, int priority){

    process_t new_process = (process_t)mem_alloc(sizeof(*new_process));
	str_cpy(process_name, (char*)(new_process->name));
    new_process->pid = global_pid;
    new_process->state = P_READY;
	new_process->stack_start = (uint64_t)mem_alloc(STACK_SIZE);
    new_process->stack_pointer = init_stack_args(new_process, process_start, new_process->stack_start, argc, argv);
	new_process->priority = priority;
	init_fds(new_process);
	if(global_pid != 0){
		new_process->ppid = get_current_process()->pid;
	}
	else{
		foreground_process = new_process;
		new_process->ppid = 0;
	}

	all_processes[global_pid++] = new_process;

    return new_process;
}

void set_foreground_process(size_t pid){
	if(all_processes[pid] != NULL){
		foreground_process = all_processes[pid];
	}
}

int is_current_process_foreground(){
	return foreground_process == get_current_process();
}

void delete_process(process_t process){
	all_processes[process->pid] = NULL;
    free_mem((void *)process->stack_start);
    free_mem(process);
}

void set_state(process_t process, pstate_t state){
    process->state = state;
	if(state == P_TERMINATE && process == foreground_process){
		foreground_process = all_processes[process->ppid];
		_context_switch_process();
	}
}

void set_current_process_terminate(){
	set_state(get_current_process(), P_TERMINATE);
}

pstate_t get_state(process_t process){
    return process->state;
}

void set_stack_pointer(process_t process, uint64_t stack_pointer){
    process->stack_pointer=stack_pointer;
}

void set_state_id(size_t pid, pstate_t state){
	all_processes[pid]->state = state;
}

size_t get_pid(process_t process){
	return process->pid;
}

uint64_t get_stack_pointer(process_t process){
	return process->stack_pointer;
}

static uint64_t init_stack(process_t process, uint64_t process_start, uint64_t stack_pointer) {
    stack_t * frame = (stack_t *)(stack_pointer + STACK_SIZE - sizeof(stack_t) - 1);

	frame->gs = 0x000;
	frame->fs =	0x000;
	frame->r15 = 0x000;
	frame->r14 = 0x000;
	frame->r13 = 0x000;
	frame->r12 = 0x000;
	frame->r11 = 0x000;
	frame->r10 = 0x000;
	frame->r9 =	0x000;
	frame->r8 =	0x000;
	frame->rsi = process_start;
	frame->rdi = (uint64_t)process;
	frame->rbp = 0x000;
	frame->rdx = 0x000;
	frame->rcx = 0x000;
	frame->rbx = 0x000;
	frame->rax = 0x000;

	frame->rip = (uint64_t)process_caller;
	frame->cs =	0x008;
	frame->eflags = 0x202;
	frame->rsp = (uint64_t)&(frame->base);
	frame->ss = 0x000;
	frame->base = 0x000;

	return (uint64_t)frame;
}

static uint64_t init_stack_args(process_t process, uint64_t process_start, uint64_t stack_pointer, int argc, void ** argv) {
    stack_t * frame = (stack_t *)(stack_pointer + STACK_SIZE - sizeof(stack_t) - 1);

	frame->gs = 0x000;
	frame->fs =	0x000;
	frame->r15 = 0x000;
	frame->r14 = 0x000;
	frame->r13 = 0x000;
	frame->r12 = 0x000;
	frame->r11 = 0x000;
	frame->r10 = 0x000;
	frame->r9 =	0x000;
	frame->r8 =	0x000;
	frame->rsi = process_start;
	frame->rdi = (uint64_t)process;
	frame->rbp = 0x000;
	frame->rdx = (uint64_t)argc;
	frame->rcx = (uint64_t)argv;
	frame->rbx = 0x000;
	frame->rax = 0x000;

	frame->rip = (uint64_t)process_caller_args;
	frame->cs =	0x008;
	frame->eflags = 0x202;
	frame->rsp = (uint64_t)&(frame->base);
	frame->ss = 0x000;
	frame->base = 0x000;

	return (uint64_t)frame;
}

void print_process(void * p){
	process_t process = (process_t)p; 
	draw_string("PID: ");
	draw_number(process->pid);
	draw_string(" PROCESS NAME: ");
	draw_string((char *)process->name);
	draw_string(" STATE: ");
	if(process->state == P_READY){
		draw_string("P_READY");
	}
	else if(process->state == P_RUNNING){
		draw_string("P_RUNNING");
	}
	else if(process->state == P_WAITING){
		draw_string("P_WAITING");
	}
	else{
		draw_string("P_TERMINATE");
	}
	draw_string(" PPID: ");
	draw_number(process->ppid);
	draw_string(" STACK: ");
	draw_number((int)process->stack_start);
	if(foreground_process == process){
		draw_string(" PROCESS IN: FOREGROUND");
	}
	else{
		draw_string(" PROCESS IN: BACKGROUND");
	}
	draw_string(" PRIORITY: ");
	if(process->priority == 0){
		draw_number(3);
	}
	else if(process->priority == 1){
		draw_number(2);
	}
	else if(process->priority == 2){
		draw_number(1);
	}

	new_line();
}

static void process_caller(process_t process, uint64_t process_start){
	void (*process_call)(void) = (void (*)(void))process_start;
	(*process_call)();
	if(foreground_process == process){
		set_foreground_process(process->ppid);
	}
	kill_current_process();
}

static void process_caller_args(process_t process, uint64_t process_start, int argc, void ** argv){
	void (*process_call)(int , void **) = (void (*)(int , void **))process_start;
	(*process_call)(argc, argv);
	if(foreground_process == process){
		set_foreground_process(process->ppid);
	}
	kill_current_process();
}

int get_priority(process_t process){
	return process->priority;
}

pstate_t get_state_id(size_t pid){
	return all_processes[pid]->state;
}

int set_priority(int pid, int priority) {
	if(priority >= PRIORITIES) {
		return -1;
	}
	all_processes[pid]->priority=priority;
	return priority;
}

static void init_fds(process_t process){
	process->fds[0] = mem_alloc(sizeof(fd_infoADT));
	process->fds[1] = mem_alloc(sizeof(fd_infoADT));
	process->fds[2] = mem_alloc(sizeof(fd_infoADT));
	process->fds[0]->type=STDIN;
	process->fds[1]->type=STDOUT;
	process->fds[2]->type=STDERR;
	for(int i=3; i<MAX_FD; i++){
		process->fds[i]=NULL;
	}
}

int open_fd(char * path, fd_t type){
	inode_t aux = get_file(path);
	if(aux==NULL){
		return -1;
	}
	process_t current = get_current_process();
	for(int i=0; i<MAX_FD; i++){
		if(current->fds[i]==NULL){
			current->fds[i]=mem_alloc(sizeof(fd_infoADT));
			current->fds[i]->type= type;
			current->fds[i]->file=aux;
			return i;
		}
	}
	return -1;
}

int close_fd(int fd_pos){
	process_t current = get_current_process();
	if(current->fds[fd_pos]!=NULL){
		free_mem(current->fds[fd_pos]);
		return 0;
	}
	return 1;
}

void write_fd(int fd, const char * buff, int q){
	process_t current = get_current_process();
	switch(current->fds[fd]->type){
		case STD_OUT:
			for(int i=0; i<q; i++){
				draw_char(*buff);
				buff++;
			}
			break;
		case STD_ERR:
			for(int i=0; i<q; i++){
				draw_err_char(*buff);
				buff++;
			}
			break;
		case W_ONLY:
			write_file(current->fds[fd]->file, buff, q);
			break;
		case STD_IN:
		case R_ONLY:
			break;
	}
}

void read_fd(int fd, char * buff, int q){
	process_t current = get_current_process();
	switch(current->fds[fd]->type){
		case STD_IN:
			for(int i=0; i<q; i++){
				*buff=get_char();
			}
			break;
		case R_ONLY:
			read_file(current->fds[fd]->file, buff, q);
			break;
		case STD_OUT:
		case STD_ERR:
		case W_ONLY:
			break;
	}
}