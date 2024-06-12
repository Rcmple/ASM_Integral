extern f1_calc
section .text
f1_calc:
    finit
    push ebp
    mov ebp, esp
    sub esp, 6

    fstcw word [ebp-2]
    or word [ebp-2], 0b110000000000
    fldcw word [ebp-2]

    fld qword [ebp+8]
    fldl2e
    fmulp

    fld1
    fld1
    faddp
    fyl2x

    fist dword [esp]

    fild dword [esp]
    fsub
    f2xm1
    fld1
    fadd
    fild dword [esp]
    fxch
    fscale

    fld1
    fld1
    faddp
    faddp
    leave
    ret
