.global _ZN5Riscv5pushAEv
.type _ZN5Riscv5pushAEv, @function
_ZN5Riscv5pushAEv:
    addi sp, sp, -16
    sd x10, 0(sp)
    ret



.global _ZN5Riscv4popAEv
.type _ZN5Riscv4popAEv, @function
_ZN5Riscv4popAEv:
    ld x10 , 0(sp)
    addi sp,sp,16
    ret

