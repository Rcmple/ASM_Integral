extern f2_calc
section .rodata
    eight dq 8.0
section .text
f2_calc:
    finit
    push ebp
    mov ebp, esp
    fld qword[ebp + 8]
    fld1
    fld1
    faddp
    fmul
    fchs
    fld qword[eight]
    fadd
    leave
    ret
