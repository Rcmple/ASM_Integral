extern f3_calc
section .rodata
    five dq 5.0
section .text
f3_calc:
    push ebp
    mov ebp, esp
    finit
    fld qword[five]
    fld qword[ebp + 8]
    fdiv
    fchs
    leave
    ret
