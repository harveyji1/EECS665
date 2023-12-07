.data
gbl_main: .quad 0
str_0: .asciz "\n"
.align 8
.globl main
.text
main: pushq %rbp
movq %rsp, %rbp
addq $16, %rbp
subq $32, %rsp
# Fn body main
 #             [myB] := 1
movq $1, %rax
movq %rax, -24(%rbp)
 #             [myA] := 1
movq $1, %rax
movq %rax, -32(%rbp)
 #             [tmp0] := NOT64 [myB]
movq -24(%rbp), %rax
cmpq $0, %rax
setz %al
movq %rax, -40(%rbp)
 #             IFZ [tmp0] GOTO lbl_2
movq -40(%rbp), %rdi
cmpq $0, %rdi
je lbl_2 #             [tmp1] := NEG64 1
movq $1, %rax
negq %rax
movq %rax, -48(%rbp)
 #             [myA] := [tmp1]
movq -48(%rbp), %rax
movq %rax, -32(%rbp)
lbl_2:  # lbl_2:      nop
nop
 #             WRITE [myA]
movq -32(%rbp), %rdi
callq printInt
 #             WRITE str_0
movq $str_0, %rdi
callq printString
 #             WRITE [myB]
movq -24(%rbp), %rdi
callq printBool
# Fn epilogue main
lbl_1: addq $32, %rsp
popq %rbp
retq
