#include "cpu.h"
#include "memory/mem_access.h"
#include <stdbool.h>

//bit value macro
#define BV(bit) (1 << bit)

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

//status register bits
enum
{
    ivtptr = 0,
    paie = 12,
    ie = 13,
    ca = 14,
    ze = 15
};

//memory for general perpose registers
uint8_t regs[22];

//=======================================================================================functions for parsing instructions
static arg_type_t parse_arg1(instr_t instr)
{
    return (arg_type_t)((instr >> 12) & 0xF);
}

static arg_type_t parse_arg2(instr_t instr)
{
    return (arg_type_t)((instr >> 8) & 0xF);
}

static size_t arg_size(arg_type_t arg_type)
{
    if(arg_type == none) return 0;
    if(arg_type == l8 && arg_type == r16 && arg_type == r32) return 1;
    if(arg_type == l32) return 4;
    return 2;
}

//=======================================================================================function for executing next programm step
void cpu_clk(void)
{
    //fech instruction
    instr_t instr = mem_fech_16(regs[ip]);
}