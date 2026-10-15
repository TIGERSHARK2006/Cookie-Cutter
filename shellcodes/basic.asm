global _start

section .data
    message db "I ALWAYS COME BACK!"

section .txt

_start:
    mov rsi, message
    mov rdi, 1
    mov rdx,18
    mov rax, 1
    syscall

    mov rax,60
    mov rdi, 0
    syscall

