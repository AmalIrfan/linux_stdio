   .section .text
   .global puts
   .extern strlen
/* int puts(const char*const s, size_t l) */
puts:
   cmp $-1, %rsi
   je .strlen
/* syswrite
     rax: 1
     rdi: 1
     rsi: s
     rdx: l */
   mov $1, %rax
   mov %rsi, %rdx
   mov %rdi, %rsi
   mov $1, %rdi
   syscall
   ret
.strlen:
/* syswrite
     rax: 1
     rdi: 1
     rsi: s
     rdx: strlen(s) */
   push %rdi  /* duplicate s */
   call strlen
   mov %rax, %rdx
   mov $1, %rax
   mov $1, %rdi
   pop %rsi  /* pass s */
   syscall
   ret
