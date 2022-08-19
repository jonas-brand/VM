#ifndef __CPU_H__
#define __CPU_H__

//instruction type
typedef uint16_t instr_t;

//instructions
enum
{
    nop,
    mov,
    sip,
    ssp,
    sivtp,
    psh,
    pop,
    cli,
    sei,
    add,
    sub,
    mul,
    div,
    inc,
    dec,
    fadd,
    fsub,
    fmul,
    fdiv,
    fsqrt,
    shl,
    shr,
    and,
    or,
    not,
    xor,
    jmp,
    jz,
    jnz
}instructions;

enum
{
    l16,
    l32,
    m16,
    m32,
    r16,
    r32
}arg_types;

#endif //! __CPU_H__