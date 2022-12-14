#ifndef __CPU_H__
#define __CPU_H__

#include <stdint.h>

//instruction type
typedef uint16_t instr_t;

#define INSTR(arg1, arg2, instruction) (instr_t)((arg1 << 12) | (arg2 << 8) | instruction)

//instructions
enum
{
    vm_nop,
    vm_mov,
    vm_psh,
    vm_pop,
    vm_add,
    vm_sub,
    vm_mul,
    vm_div,
    vm_inc,
    vm_dec,
    vm_fadd,
    vm_fsub,
    vm_fmul,
    vm_fdiv,
    vm_fsqrt,
    vm_shl,
    vm_shr,
    vm_and,
    vm_or,
    vm_not,
    vm_xor,
    vm_jmp,
    vm_jze
}instructions;

typedef enum
{
    none,
    l8,
    l16,
    l32,
    m8,
    m16,
    m32,
    r16,
    r32
}arg_type_t;

//types for pointers to registers
typedef enum
{
    gpr0,
    gpr1 = gpr0 + 4,
    gpr2 = gpr1 + 4,
    gpr3 = gpr2 + 4
}r32ptr_t;

typedef enum
{
    gpr0l = gpr0,
    gpr0h = gpr0 + 2,
    gpr1l = gpr1,
    gpr1h = gpr1 + 2,
    gpr2l = gpr2,
    gpr2h = gpr2 + 2,
    gpr3l = gpr3,
    gpr3h = gpr3 + 2,
    ip = gpr3 + 4,
    sp = ip + 2,
    stat = sp + 2
}r16ptr_t;

//function for executing next programm step
void cpu_clk(void);

//function for printing out cpu state
void cpu_print(void);

#endif //! __CPU_H__