#ifndef __CPU_H__
#define __CPU_H__

#include <stdint.h>

//instruction type
typedef uint16_t instr_t;

#define INSTR(arg1, arg2, instruction) (instr_t)((arg1 << 12) | (arg2 << 8) | instruction)

//instructions
enum
{
    nop,
    mov,
    psh,
    pop,
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
    jz
}instructions;

typedef enum
{
    l8,
    l16,
    l32,
    m8,
    m16,
    m32,
    r16,
    r32
}arg_type_t;

//function for executing next programm step
void cpu_clk(void);

#endif //! __CPU_H__