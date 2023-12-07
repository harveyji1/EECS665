.data
gbl_main: .quad 0
str_0: .asciz "\n"
.align 8
.globl main
.text
main: pushq %rbp
movq %rsp, %rbp
addq $16, %rbp
subq $48, %rsp
# Fn body main
 #             [myFalse] := 0
movq $0, %rax
movq %rax, -24(%rbp)
 #             [myTrue] := 1
movq $1, %rax
movq %rax, -32(%rbp)
 #             [tmp0] := [myTrue] AND64 [myFalse]
movq -32(%rbp), %rax
movq -24(%rbp), %rbx
andq %rbx, %rax
movq %rax, -56(%rbp)
 #             [myAnd] := [tmp0]
movq -56(%rbp), %rax
movq %rax, -40(%rbp)
 #             [tmp1] := [myTrue] OR64 [myFalse]
movq -32(%rbp), %rax
movq -24(%rbp), %rbx
orq %rax, %rax
movq %rax, -64(%rbp)
 #             [myOr] := [tmp1]
movq -64(%rbp), %rax
movq %rax, -48(%rbp)
 #             WRITE [myTrue]
movq -32(%rbp), %rdi
callq printBool
 #             WRITE str_0
movq $str_0, %rdi
callq printString
 #             WRITE [myOr]
movq -48(%rbp), %rdi
callq printBool
# Fn epilogue main
lbl_1: addq $48, %rsp
popq %rbp
retq
