.data
gbl_main: .quad 0
str_2: .asciz "\n"
str_1: .asciz "\n"
str_0: .asciz "\n"
.align 8
.globl main
.text
main: pushq %rbp
movq %rsp, %rbp
addq $16, %rbp
subq $64, %rsp
# Fn body main
 #             [myB] := 2
movq $2, %rax
movq %rax, -24(%rbp)
 #             [myA] := 1
movq $1, %rax
movq %rax, -32(%rbp)
 #             [tmp0] := [myA] ADD64 [myB]
movq -32(%rbp), %rax
movq -24(%rbp), %rbx
addq %rbx, %rax
movq %rax, -56(%rbp)
 #             [myC] := [tmp0]
movq -56(%rbp), %rax
movq %rax, -40(%rbp)
 #             [tmp1] := [myC] MULT64 3
movq -40(%rbp), %rax
movq $3, %rbx
imulq %rbx, %rax
movq %rax, -64(%rbp)
 #             [myD] := [tmp1]
movq -64(%rbp), %rax
movq %rax, -48(%rbp)
 #             [tmp2] := [myD] DIV64 3
movq -48(%rbp), %rdx
movq $3, %rax
movq $0, %rdx
idivq %rbx
movq %rax, %rbx
movq %rbx, -72(%rbp)
 #             [myB] := [tmp2]
movq -72(%rbp), %rax
movq %rax, -24(%rbp)
 #             [tmp3] := [myB] SUB64 2
movq -24(%rbp), %rax
movq $2, %rbx
subq %rbx, %rax
movq %rax, -80(%rbp)
 #             [myA] := [tmp3]
movq -80(%rbp), %rax
movq %rax, -32(%rbp)
 #             WRITE [myA]
movq -32(%rbp), %rdi
callq printInt
 #             WRITE str_0
movq $str_0, %rdi
callq printString
 #             WRITE [myB]
movq -24(%rbp), %rdi
callq printInt
 #             WRITE str_1
movq $str_1, %rdi
callq printString
 #             WRITE [myC]
movq -40(%rbp), %rdi
callq printInt
 #             WRITE str_2
movq $str_2, %rdi
callq printString
 #             WRITE [myD]
movq -48(%rbp), %rdi
callq printInt
# Fn epilogue main
lbl_1: addq $64, %rsp
popq %rbp
retq
