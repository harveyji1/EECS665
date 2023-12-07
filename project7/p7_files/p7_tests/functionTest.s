.data
gbl_fn1: .quad 0
gbl_fn2: .quad 0
gbl_fn3: .quad 0
gbl_main: .quad 0
str_2: .asciz "\n"
str_1: .asciz "test"
str_0: .asciz "\n"
.align 8
.globl main
.text
fun_fn1: pushq %rbp
movq %rsp, %rbp
addq $16, %rbp
subq $16, %rsp
# Fn body fn1
 #             getarg 1 [arg1]
movq %rdi, -32(%rbp)
 #             [a] := [arg1]
movq -32(%rbp), %rax
movq %rax, -24(%rbp)
 #             WRITE [a]
movq -24(%rbp), %rdi
callq printInt
 #             WRITE str_0
movq $str_0, %rdi
callq printString
# Fn epilogue fn1
lbl_1: addq $16, %rsp
popq %rbp
retq
fun_fn2: pushq %rbp
movq %rsp, %rbp
addq $16, %rbp
subq $0, %rsp
# Fn body fn2
 #             WRITE str_1
movq $str_1, %rdi
callq printString
 #             WRITE str_2
movq $str_2, %rdi
callq printString
# Fn epilogue fn2
lbl_2: addq $0, %rsp
popq %rbp
retq
fun_fn3: pushq %rbp
movq %rsp, %rbp
addq $16, %rbp
subq $16, %rsp
# Fn body fn3
 #             [c] := 1
movq $1, %rax
movq %rax, -24(%rbp)
 #             WRITE [c]
movq -24(%rbp), %rdi
callq printBool
# Fn epilogue fn3
lbl_3: addq $16, %rsp
popq %rbp
retq
main: pushq %rbp
movq %rsp, %rbp
addq $16, %rbp
subq $0, %rsp
# Fn body main
 #             setarg 1 3
movq $3, %rdi
 #             call fn1
callq fun_fn1
 #             call fn2
callq fun_fn2
 #             call fn3
callq fun_fn3
# Fn epilogue main
lbl_4: addq $0, %rsp
popq %rbp
retq
