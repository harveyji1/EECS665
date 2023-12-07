.data
gbl_a: .quad 0
gbl_b: .quad 0
gbl_main: .quad 0
.align 8
.globl main
.text
main: pushq %rbp
movq %rsp, %rbp
addq $16, %rbp
subq $0, %rsp
# Fn body main
# Fn epilogue main
lbl_1: addq $0, %rsp
popq %rbp
retq
