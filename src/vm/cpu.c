#include "cpu.h"
#include "memory/mem_access.h"
#include <stdbool.h>
#include <math.h>
#include <stdio.h>

//bit value macro
#define BV(bit) (1 << bit)

//status register bits
enum
{
    ivtptr = 0,
    paie = 13,
    ie = 14,
    ca = 15,
};

//interrupt vector table layout
enum
{
    pai = 0
};

//memory for general perpose registers
uint8_t regs[22];

//macros for accessing registers
#define R16(reg) *(uint16_t*)(regs + (r16ptr_t)(uint8_t)reg)
#define R32(reg) *(uint32_t*)(regs + (r32ptr_t)(uint8_t)reg)
#define RF(reg) *(float*)(regs + (r32ptr_t)(uint8_t)reg)

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

//=======================================================================================function for executing instruction
void instr_exec(instr_t instr, uint32_t arg1, uint32_t arg2)
{
    switch(instr)
    {
        //no operation
        case INSTR(none, none, vm_nop):
            break;

        //move l8 into lower byte of r16
        case INSTR(l8, r16, vm_mov):
            R16(arg2) = (uint8_t)arg1;
            break;

        //move m8 into lower byte of r16
        case INSTR(m8, r16, vm_mov):
            R16(arg2) = mem_fech_8((dtptr_t)arg1);
            break;

        //move lower byte of r16 into m8
        case INSTR(r16, m8, vm_mov):
            mem_write_8((dtptr_t)arg2, (uint8_t)R16(arg1));
            break;

        //move l16 into r16
        case INSTR(l16, r16, vm_mov):
            R16(arg2) = (uint16_t)arg1;
            break;

        //move m16 into r16
        case INSTR(m16, r16, vm_mov):
            R16(arg2) = mem_fech_16((dtptr_t)arg1);
            break;

        //move r16 into m16
        case INSTR(r16, m16, vm_mov):
            mem_write_16((dtptr_t)arg2, R16(arg1));
            break;

        //move l32 into r32
        case INSTR(l32, r32, vm_mov):
            R32(arg2) = (uint32_t)arg1;
            break;

        //move m32 into r32
        case INSTR(m32, r32, vm_mov):
            R32(arg2) = mem_fech_32((dtptr_t)arg1);
            break;

        //move r32 into m32
        case INSTR(r32, m32, vm_mov):
            mem_write_32((dtptr_t)arg2, R32(arg1));
            break;

        //push r16 onto the stack
        case INSTR(r16, none, vm_psh):
            mem_write_16((dtptr_t)R16(ip), R16(arg1));
            break;

        //push r32 onto the stack
        case INSTR(r32, none, vm_psh):
            mem_write_32((dtptr_t)R16(ip), R32(arg1));
            break;

        //pop 2 bytes of the stack into r16
        case INSTR(r16, none, vm_pop):
            R16(arg1) = mem_fech_16((dtptr_t)R16(ip));
            break;

        //pop 4 bytes of the stack into r32
        case INSTR(r32, none, vm_pop):
            R32(arg1) = mem_fech_32((dtptr_t)R16(ip));
            break;

        //add r16 to r16
        case INSTR(r16, r16, vm_add):
            R16(arg2) += R16(arg1);
            break;

        //add r32 to r32
        case INSTR(r32, r32, vm_add):
            R32(arg2) += R32(arg1);
            break;

        //subtract r16 from r16
        case INSTR(r16, r16, vm_sub):
            R16(arg2) -= R16(arg1);
            break;

        //subtract r32 from r32
        case INSTR(r32, r32, vm_sub):
            R32(arg2) -= R32(arg1);
            break;
        
        //multiply r16 with r16
        case INSTR(r16, r16, vm_mul):
            R16(arg2) *= R16(arg1);
            break;

        //multiply r32 with r32
        case INSTR(r32, r32, vm_mul):
            R32(arg2) *= R32(arg1);
            break;

        //divide r16 by r16
        case INSTR(r16, r16, vm_div):
            R16(arg2) /= R16(arg1);
            break;

        //divide r32 by r32
        case INSTR(r32, r32, vm_div):
            R32(arg2) /= R32(arg1);
            break;

        //increment r16
        case INSTR(r16, none, vm_inc):
            (R16(arg1))++;
            break;

        //increment r32
        case INSTR(r32, none, vm_inc):
            (R32(arg1))++;
            break;

        //decrement r16
        case INSTR(r16, none, vm_dec):
            (R16(arg1))--;
            break;

        //decrement r32
        case INSTR(r32, none, vm_dec):
            (R32(arg1))--;
            break;

        //add r32 to r32 as floating point
        case INSTR(r32, r32, vm_fadd):
            RF(arg2) += RF(arg1);
            break;

        //subtract r32 from r32 as floating point
        case INSTR(r32, r32, vm_fsub):
            RF(arg2) -= RF(arg1);
            break;

        //multiply r32 with r32 as floating point
        case INSTR(r32, r32, vm_fmul):
            RF(arg2) *= RF(arg1);
            break;

        //divide r32 by r32 as floating point
        case INSTR(r32, r32, vm_fdiv):
            RF(arg2) /= RF(arg1);
            break;

        //get square root of r32 as floating point
        case INSTR(r32, r32, vm_fsqrt):
            RF(arg2) = sqrt(RF(arg1));
            break;

        //shift r16 left by r16
        case INSTR(r16, r16, vm_shl):
            R16(arg2) <<= R16(arg1);
            break;

        //shift r32 left by r16
        case INSTR(r32, r16, vm_shl):
            R32(arg2) <<= R16(arg1);
            break;

        //shift r16 right by r16
        case INSTR(r16, r16, vm_shr):
            R16(arg2) >>= R16(arg1);
            break;

        //shift r32 right by r16
        case INSTR(r32, r16, vm_shr):
            R32(arg2) >>= R16(arg1);
            break;

        //bitwise-and r16 and r16
        case INSTR(r16, r16, vm_and):
            R16(arg2) &= R16(arg1);
            break;

        //bitwise-and r32 and r32
        case INSTR(r32, r32, vm_and):
            R32(arg2) &= R16(arg1);
            break;

        //bitwise-or r16 and r16
        case INSTR(r16, r16, vm_or):
            R16(arg2) |= R16(arg1);
            break;

        //bitwise-or r32 and r32
        case INSTR(r32, r32, vm_or):
            R32(arg2) |= R16(arg1);
            break;

        //bitwise-not r16
        case INSTR(r16, none, vm_not):
            R16(arg1) = ~R16(arg1);
            break;

        //bitwise-not r32
        case INSTR(r32, none, vm_not):
            R32(arg1) = ~R16(arg1);
            break;

        //bitwise-xor r16 and r16
        case INSTR(r16, r16, vm_xor):
            R16(arg2) ^= R16(arg1);
            break;

        //bitwise-xor r32 and r32
        case INSTR(r32, r32, vm_xor):
            R32(arg2) ^= R16(arg1);
            break;

        //unconditional jump to l16
        case INSTR(l16, none, vm_jmp):
            R16(ip) = (dtptr_t)arg1;
            break;

        //unconditional jump to r16
        case INSTR(r16, none, vm_jmp):
            R16(ip) = R16(arg1);
            break;

        //jump to l16 if r16 is zero
        case INSTR(l16, r16, vm_jze):
            if(R16(arg2)) break;
            R16(ip) = arg1;
            break;

        //jump to r16 if r16 is zero
        case INSTR(r16, r16, vm_jze):
            if(R16(arg2)) break;
            R16(ip) = R16(arg1);
            break;

        //jump to l16 if r32 is zero
        case INSTR(l16, r32, vm_jze):
            if(R32(arg2)) break;
            R16(ip) = arg1;
            break;

        //jump to r16 if r32 is zero
        case INSTR(r16, r32, vm_jze):
            if(R32(arg2)) break;
            R16(ip) = R16(arg1);
            break;

        //error, jump to panic interrupt
        default:
            R16(ip) = (R16(stat) << 8) + pai;
            break;
    }
}

//=======================================================================================function for executing next programm step
void cpu_clk(void)
{
    //fech instruction
    instr_t instr = mem_fech_16(regs[ip]);

    //get size of arguments
    size_t arg1_size = arg_size(parse_arg1(instr));
    size_t arg2_size = arg_size(parse_arg2(instr));

    //fech arguments
    uint32_t arg1 = arg1_size ? mem_fech_32(regs[ip] + 2) : 0;
    uint32_t arg2 = arg2_size ? mem_fech_32(regs[ip] + 2 + arg1_size) : 0;

    //execute instruction
    instr_exec(instr, arg1, arg2);

    //increment instruction pointer
    regs[ip] += 2 + arg1_size + arg2_size;
}

//=======================================================================================function for printing out cpu state
void cpu_print(void)
{
    printf("gpr0:\t%04X\ngpr1:\t%04X\ngpr2:\t%04X\ngpr3:\t%04X\nip:\t%02X\nsp:\t%02X\nstat:\t%02X",
           R32(gpr0), R32(gpr1), R32(gpr2), R32(gpr3), R16(ip), R16(sp), R16(stat));
}