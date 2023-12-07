.data
gbl_main: .quad 0
.align 8
.globl main
.text
main: pushq %rbp
movq %rsp, %rbp
addq $16, %rbp
subq $32, %rsp
# Fn body main
 #             [a] := 1
movq $1, %rax
movq %rax, -24(%rbp)
 #             [b] := 0
movq $0, %rax
movq %rax, -32(%rbp)
 #             [tmp0] := [a] AND64 [b]
movq -24(%rbp), %rax
movq -32(%rbp), %rbx
andq %rbx, %rax
movq %rax, -48(%rbp)
 #             [c] := [tmp0]
movq -48(%rbp), %rax
movq %rax, -40(%rbp)
 #             WRITE [c]
movq -40(%rbp), %rdi
callq printBool
# Fn epilogue main
lbl_1: addq $32, %rsp
popq %rbp
retq
