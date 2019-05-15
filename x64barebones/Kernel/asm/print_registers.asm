GLOBAL print_all_registers

extern new_line
extern set_current_process_terminate
extern draw_err_string
extern draw_err_number

section .text

%macro push_all 0
	push rax
	push rbx
	push rcx
	push rdx
	push rbp
	push rdi
	push rsi
	push r8
	push r9
	push r10
	push r11
	push r12
	push r13
	push r14
	push r15
%endmacro

%macro pop_all 0
	pop r15
	pop r14
	pop r13
	pop r12
	pop r11
	pop r10
	pop r9
	pop r8
	pop rsi
	pop rdi
	pop rbp
	pop rdx
	pop rcx
	pop rbx
	pop rax
%endmacro

print_all_registers:
		push_all
		mov rdi, register9
		call draw_err_string
		mov rdi,[rsp + 15 * 8]
		call draw_err_number
		call new_line
		pop_all

    push_all
    mov rdi, register1
    call draw_err_string
    mov rdi,rax
    call draw_err_number
    call new_line
    pop_all

    push_all
    mov rdi, register2
    call draw_err_string
    mov rdi,rbx
    call draw_err_number
    call new_line
    pop_all

    push_all
    mov rdi, register4
    call draw_err_string
    mov rdi,rdx
    call draw_err_number
    call new_line
    pop_all

    push_all
    mov rdi, register5
    call draw_err_string
    mov rdi,rsi
    call draw_err_number
    call new_line
    pop_all

    push_all
    mov rdi, register6
    call draw_err_string
    mov rdi,rdi
    call draw_err_number
    call new_line
    pop_all

    push_all
    mov rdi, register7
    call draw_err_string
    mov rdi,rsp
    call draw_err_number
    call new_line
    pop_all

    push_all
    mov rdi, register8
    call draw_err_string
    mov rdi,rbp
    call draw_err_number
    call new_line
    pop_all

    push_all
    mov rdi, register10
    call draw_err_string
    mov rdi,r8
    call draw_err_number
    call new_line
    pop_all

    push_all
    mov rdi, register11
    call draw_err_string
    mov rdi,r9
    call draw_err_number
    call new_line
    pop_all

    call set_current_process_terminate

section .rodata
  register1 db "RAX= ", 0
  register2 db "RBC= ", 0
  register4 db "RDX= ", 0
  register5 db "RSI= ", 0
  register6 db "RDI= ", 0
  register7 db "RSP= ", 0
  register8 db "RBP= ", 0
  register9 db "RIP= ", 0
  register10 db "R8= ", 0
  register11 db "R9= ", 0
