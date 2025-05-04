   .section .text
   .global gets
/* int gets(char*const*const s, size_t l) */
/* int gets(char**const s, -1) */
gets:
   cmp $-1, %rsi
   je .gets_buf
/* sysread
     rax: 0
     rdi: 0
     rsi: *s
     rdx: l */
   mov $0, %rax
   mov %rsi, %rdx
   mov (%rdi), %rsi
   mov $0, %rdi
   syscall
   ret
.gets_buf:
GETS_BUFSIZE=256
/* sysread
     rax: 0
     rdi: 0
     rsi: gets_buf
     rdx: GETS_BUFSIZE */
   push %rdi
   mov $0, %rax
   mov $0, %rdi
   lea gets_buf, %rsi
   mov $GETS_BUFSIZE, %rdx
   syscall
/* null terminator */
   lea gets_buf, %rsi
   movb $0, (%rsi,%rax)
/* *s = gets_buf */
   pop %rdi
   mov %rsi, (%rdi)
   ret

   .section .bss
   .lcomm gets_buf, GETS_BUFSIZE
