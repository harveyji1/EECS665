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
subq $32, %rsp
# Fn body main
lbl_2:  # lbl_2:      nop
nop
 #             IFZ 0 GOTO lbl_3
movq $0, %rdi
cmpq $0, %rdi
je lbl_3 #             [a] := 1
movq $1, %rax
movq %rax, -24(%rbp)
 #             WRITE [a]
movq -24(%rbp), %rdi
callq printInt
 #             WRITE str_0
movq $str_0, %rdi
callq printString
 #             goto lbl_2
jmp lbl_2
lbl_3:  # lbl_3:      nop
nop
 #             IFZ 1 GOTO lbl_4
movq $1, %rdi
cmpq $0, %rdi
je lbl_4 #             [a] := 1
movq $1, %rax
movq %rax, -32(%rbp)
 #             WRITE [a]
movq -32(%rbp), %rdi
callq printInt
 #             WRITE str_1
movq $str_1, %rdi
callq printString
lbl_4:  # lbl_4:      nop
nop
 #             IFZ 0 GOTO lbl_5
movq $0, %rdi
cmpq $0, %rdi
je lbl_5 #             [a] := 1
movq $1, %rax
movq %rax, -40(%rbp)
 #             goto lbl_6
jmp lbl_6
lbl_5:  # lbl_5:      nop
nop
 #             [a] := 1
movq $1, %rax
movq %rax, -48(%rbp)
 #             [a] := [a] ADD64 1
movq -48(%rbp), %rax
movq $1, %rbx
addq %rbx, %rax
movq %rax, -48(%rbp)
 #             WRITE [a]
movq -48(%rbp), %rdi
callq printInt
 #             WRITE str_2
movq $str_2, %rdi
callq printString
 #             [a] := [a] SUB64 1
movq -48(%rbp), %rax
movq $1, %rbx
subq %rbx, %rax
movq %rax, -48(%rbp)
 #             WRITE [a]
movq -48(%rbp), %rdi
callq printInt
lbl_6:  # lbl_6:      nop
nop
# Fn epilogue main
lbl_1: addq $32, %rsp
popq %rbp
retq
