.data
gbl_callee1: .quad 0
gbl_callee2: .quad 0
gbl_callee3: .quad 0
gbl_main: .quad 0
.align 8
.globl main
.text
fun_callee1: pushq %rbp
movq %rsp, %rbp
addq $16, %rbp
subq $16, %rsp
# Fn body callee1
 #             getarg 1 [b]
movq %rdi, -24(%rbp)
 #             IFZ [b] GOTO lbl_2
movq -24(%rbp), %rdi
cmpq $0, %rdi
je lbl_2 #             setret 1
movq $1, %rax
 #             goto lbl_1
jmp lbl_1
 #             goto lbl_3
jmp lbl_3
lbl_2:  # lbl_2:      nop
nop
 #             setret 0
movq $0, %rax
 #             goto lbl_1
jmp lbl_1
lbl_3:  # lbl_3:      nop
nop
 #             WRITE [b]
movq -24(%rbp), %rsi
movq -24(%rbp), %rdi
callq printBool
# Fn epilogue callee1
lbl_1: addq $16, %rsp
popq %rbp
retq
fun_callee2: pushq %rbp
movq %rsp, %rbp
addq $16, %rbp
subq $0, %rsp
# Fn body callee2
 #             setret 1
movq $1, %rax
 #             goto lbl_4
jmp lbl_4
# Fn epilogue callee2
lbl_4: addq $0, %rsp
popq %rbp
retq
fun_callee3: pushq %rbp
movq %rsp, %rbp
addq $16, %rbp
subq $16, %rsp
# Fn body callee3
 #             getarg 1 [a]
movq %rdi, -32(%rbp)
 #             [tmp0] := [a] ADD64 1
movq -32(%rbp), %rax
movq $1, %rbx
addq %rbx, %rax
movq %rax, -24(%rbp)
 #             [a] := [tmp0]
movq -24(%rbp), %rax
movq %rax, -32(%rbp)
 #             WRITE [a]
movq -32(%rbp), %rsi
movq -32(%rbp), %rdi
callq printInt
# Fn epilogue callee3
lbl_5: addq $16, %rsp
popq %rbp
retq
main: pushq %rbp
movq %rsp, %rbp
addq $16, %rbp
subq $32, %rsp
# Fn body main
 #             [myB] := 1
movq $1, %rax
movq %rax, -24(%rbp)
 #             setarg 1 [myB]
movq -24(%rbp), %rdi
 #             call callee1
callq fun_callee1
addq $16, %rsp
 #             getret [tmp0]
movq %rax, -40(%rbp)
 #             [myA] := [tmp0]
movq -40(%rbp), %rax
movq %rax, -32(%rbp)
 #             call callee2
callq fun_callee2
 #             getret [tmp1]
movq %rax, -48(%rbp)
 #             [myB] := [tmp1]
movq -48(%rbp), %rax
movq %rax, -24(%rbp)
 #             setarg 1 [myA]
movq -32(%rbp), %rdi
 #             call callee3
callq fun_callee3
addq $16, %rsp
# Fn epilogue main
lbl_6: addq $32, %rsp
popq %rbp
retq
