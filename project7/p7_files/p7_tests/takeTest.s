.data
gbl_main: .quad 0
.align 8
.globl main
.text
main: pushq %rbp
movq %rsp, %rbp
addq $16, %rbp
subq $16, %rsp
# Fn body main
 #             READ [a]
movq -24(%rbp), %rdi
callq getInt
movq %rax, -24(%rbp)
 #             WRITE [a]
movq -24(%rbp), %rdi
callq printInt
# Fn epilogue main
lbl_1: addq $16, %rsp
popq %rbp
retq
