   .section .text
   .global _start
   .extern main

_start:
   call main
/* exit */
   mov %rax, %rdi
   mov $60, %rax
   syscall
/* unreachable */

