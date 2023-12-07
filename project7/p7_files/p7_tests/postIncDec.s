.data
gbl_main: .quad 0
str_1: .asciz "\n"
str_0: .asciz "\n"
.align 8
.globl main
.text
main: pushq %rbp
movq %rsp, %rbp
addq $16, %rbp
subq $80, %rsp
# Fn body main
 #             [a] := 1
movq $1, %rax
movq %rax, -24(%rbp)
 #             [a] := [a] ADD64 1
movq -24(%rbp), %rax
movq $1, %rbx
addq %rbx, %rax
movq %rax, -24(%rbp)
 #             [a] := [a] SUB64 1
movq -24(%rbp), %rax
movq $1, %rbx
subq %rbx, %rax
movq %rax, -24(%rbp)
 #             [b] := 2
movq $2, %rax
movq %rax, -32(%rbp)
 #             [tmp0] := [a] EQ64 [b]
movq -24(%rbp), %rax
movq -32(%rbp), %rbx
cmpq %rbx, %rax
sete %al
movq %rax, -48(%rbp)
 #             [c] := [tmp0]
movq -48(%rbp), %rax
movq %rax, -40(%rbp)
 #             [tmp1] := [a] GTE64 [b]
movq -24(%rbp), %rax
movq -32(%rbp), %rbx
cmpq %rbx, %rax
setge %al
movq %rax, -56(%rbp)
 #             [c] := [tmp1]
movq -56(%rbp), %rax
movq %rax, -40(%rbp)
 #             [tmp2] := [a] LTE64 [b]
movq -24(%rbp), %rax
movq -32(%rbp), %rbx
cmpq %rbx, %rax
setle %al
movq %rax, -64(%rbp)
 #             [c] := [tmp2]
movq -64(%rbp), %rax
movq %rax, -40(%rbp)
 #             [tmp3] := [a] LT64 [b]
movq -24(%rbp), %rax
movq -32(%rbp), %rbx
cmpq %rbx, %rax
setl %al
movq %rax, -72(%rbp)
 #             [c] := [tmp3]
movq -72(%rbp), %rax
movq %rax, -40(%rbp)
 #             [tmp4] := [a] GT64 [b]
movq -24(%rbp), %rax
movq -32(%rbp), %rbx
cmpq %rbx, %rax
setg %al
movq %rax, -80(%rbp)
 #             [c] := [tmp4]
movq -80(%rbp), %rax
movq %rax, -40(%rbp)
 #             [tmp5] := [a] NEQ64 [b]
movq -24(%rbp), %rax
movq -32(%rbp), %rbx
cmpq %rbx, %rax
setne %al
movq %rax, -88(%rbp)
 #             [c] := [tmp5]
movq -88(%rbp), %rax
movq %rax, -40(%rbp)
 #             WRITE [b]
movq -32(%rbp), %rdi
callq printInt
 #             WRITE str_0
movq $str_0, %rdi
callq printString
 #             WRITE [c]
movq -40(%rbp), %rdi
callq printBool
 #             WRITE str_1
movq $str_1, %rdi
callq printString
 #             WRITE [a]
movq -24(%rbp), %rdi
callq printInt
# Fn epilogue main
lbl_1: addq $80, %rsp
popq %rbp
retq
