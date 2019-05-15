GLOBAL io_read
GLOBAL io_write

section .text

io_read:
	push rbp
	mov rbp, rsp
	mov rax, 0
	push rdx
	mov rdx, rdi
	in al, dx
	pop rdx
	pop rbp
	ret

io_write:
	push rbp
	mov rbp, rsp
	push rdx
	push rax
	mov rdx, rdi
	mov rax, rsi
	out dx, al
	pop rax
	pop rdx
	pop rbp
	ret
