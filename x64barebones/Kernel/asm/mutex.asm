GLOBAL _mutex_lock
GLOBAL _mutex_unlock

EXTERN _context_switch_process

section .text

_mutex_lock:
    mov rax, 1

    xchg rax, [rdi]

    test rax, rax

    jz ok

    call _context_switch_process
    jmp _mutex_lock

ok:
    ret

_mutex_unlock:
    mov rax, 0

    xchg rax, [rdi]

    ret