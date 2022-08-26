#include "cpu.h"
#include "memory/mem_access.h"
#include <stdbool.h>
#include <math.h>
#include <stdio.h>

//print macro for debugging
#ifdef DEBUG
#define INSTR_PRINT(instr, arg1, arg2) printf(instr "\t%x\t%x\n", arg1, arg2)
#else
#define INSTR_PRINT
#endif

//bit value macro
#define BV(bit) (1 << bit)

//status register bits
enum
{
    ivtptr = 0,
    gpi5e = 8,
    gpi4e = 9,
    gpi3e = 10,
    gpi2e = 11,
    gpi1e = 12,
    gpi0e = 13,
    paie = 14,
    ie = 15,
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
    if(arg_type == l8 || arg_type == r16 || arg_type == r32 ||
       arg_type == rm8 || arg_type == rm16 || arg_type == rm32) return 1;
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
            INSTR_PRINT("none none nop", arg1, arg2);
            break;

        //move l8 into lower byte of r16
        case INSTR(l8, r16, vm_mov):
            INSTR_PRINT("l8 r16 mov", arg1, arg2);
            R16(arg2) = (uint8_t)arg1;
            break;

        //move lm8 into lower byte of r16
        case INSTR(lm8, r16, vm_mov):
            INSTR_PRINT("lm8 r16 mov", arg1, arg2);
            R16(arg2) = mem_fech_8((dtptr_t)arg1);
            break;
        
        //move rm8 into lower byte of r16
        case INSTR(rm8, r16, vm_mov):
            INSTR_PRINT("rm8 r16 mov", arg1, arg2);
            R16(arg2) = mem_fech_8((dtptr_t)R16(arg1));
            break;

        //move lower byte of r16 into lm8
        case INSTR(r16, lm8, vm_mov):
            INSTR_PRINT("r16 lm8 mov", arg1, arg2);
            mem_write_8((dtptr_t)arg2, (uint8_t)R16(arg1));
            break;

        //move lower byte of r16 into rm8
        case INSTR(r16, rm8, vm_mov):
            INSTR_PRINT("r16 rm8 mov", arg1, arg2);
            mem_write_8((dtptr_t)R16(arg2), (uint8_t)R16(arg1));
            break;

        //move l16 into r16
        case INSTR(l16, r16, vm_mov):
            INSTR_PRINT("l16 r16 mov", arg1, arg2);
            R16(arg2) = (uint16_t)arg1;
            break;

        //move lm16 into r16
        case INSTR(lm16, r16, vm_mov):
            INSTR_PRINT("lm16 r16 mov", arg1, arg2);
            R16(arg2) = mem_fech_16((dtptr_t)arg1);
            break;

        //move rm16 into r16
        case INSTR(rm16, r16, vm_mov):
            INSTR_PRINT("rm16 r16 mov", arg1, arg2);
            R16(arg2) = mem_fech_16((dtptr_t)R16(arg1));
            break;

        //move r16 into r16
        case INSTR(r16, r16, vm_mov):
            INSTR_PRINT("r16 r16 mov", arg1, arg2);
            R16(arg2) = R16(arg1);
            break;

        //move r16 into lm16
        case INSTR(r16, lm16, vm_mov):
            INSTR_PRINT("r16 lm16 mov", arg1, arg2);
            mem_write_16((dtptr_t)arg2, R16(arg1));
            break;
        
        //move r16 into rm16
        case INSTR(r16, rm16, vm_mov):
            INSTR_PRINT("r16 rm16 mov", arg1, arg2);
            mem_write_16((dtptr_t)R16(arg2), R16(arg1));
            break;

        //move l32 into r32
        case INSTR(l32, r32, vm_mov):
            INSTR_PRINT("l32 r32 mov", arg1, arg2);
            R32(arg2) = (uint32_t)arg1;
            break;

        //move lm32 into r32
        case INSTR(lm32, r32, vm_mov):
            INSTR_PRINT("lm32 r32 mov", arg1, arg2);
            R32(arg2) = mem_fech_32((dtptr_t)arg1);
            break;
        
        //move rm32 into r32
        case INSTR(rm32, r32, vm_mov):
            INSTR_PRINT("rm32 r32 mov", arg1, arg2);
            R32(arg2) = mem_fech_32((dtptr_t)R16(arg1));
            break;
        
        //move r32 into r32
        case INSTR(r32, r32, vm_mov):
            INSTR_PRINT("r32 r32 mov", arg1, arg2);
            R32(arg2) = R32(arg1);
            break;

        //move r32 into lm32
        case INSTR(r32, lm32, vm_mov):
            INSTR_PRINT("r32 lm32 mov", arg1, arg2);
            mem_write_32((dtptr_t)arg2, R32(arg1));
            break;
        
        //move r32 into rm32
        case INSTR(r32, rm32, vm_mov):
            INSTR_PRINT("r32 rm32 mov", arg1, arg2);
            mem_write_32((dtptr_t)R16(arg2), R32(arg1));
            break;

        //push r16 onto the stack
        case INSTR(r16, none, vm_psh):
            INSTR_PRINT("r16 none psh", arg1, arg2);
            mem_write_16((dtptr_t)R16(sp), R16(arg1));
            R16(sp) += 2;
            break;

        //push r32 onto the stack
        case INSTR(r32, none, vm_psh):
            INSTR_PRINT("r32 none psh", arg1, arg2);
            mem_write_32((dtptr_t)R16(sp), R32(arg1));
            R16(sp) += 4;
            break;

        //pop 2 bytes of the stack into r16
        case INSTR(r16, none, vm_pop):
            INSTR_PRINT("r16 none pop", arg1, arg2);
            R16(sp) -= 2;
            R16(arg1) = mem_fech_16((dtptr_t)R16(sp));
            break;

        //pop 4 bytes of the stack into r32
        case INSTR(r32, none, vm_pop):
            INSTR_PRINT("r32 none pop", arg1, arg2);
            R16(sp) -= 4;
            R32(arg1) = mem_fech_32((dtptr_t)R16(sp));
            break;

        //add r16 to r16
        case INSTR(r16, r16, vm_add):
            INSTR_PRINT("r16 r16 add", arg1, arg2);
            R16(arg2) += R16(arg1);
            break;

        //add l16 to r16
        case INSTR(l16, r16, vm_add):
            INSTR_PRINT("l16 r16 add", arg1, arg2);
            R16(arg2) += (uint16_t)arg1;
            break;

        //add r32 to r32
        case INSTR(r32, r32, vm_add):
            INSTR_PRINT("r32 r32 add", arg1, arg2);
            R32(arg2) += R32(arg1);
            break;

        //add l32 to r32
        case INSTR(l32, r32, vm_add):
            INSTR_PRINT("l32 r32 add", arg1, arg2);
            R32(arg2) += (uint32_t)arg1;
            break;

        //subtract r16 from r16
        case INSTR(r16, r16, vm_sub):
            INSTR_PRINT("r16 r16 sub", arg1, arg2);
            R16(arg2) -= R16(arg1);
            break;

        //subtract l16 from r16
        case INSTR(l16, r16, vm_sub):
            INSTR_PRINT("l16 r16 sub", arg1, arg2);
            R16(arg2) -= (uint16_t)arg1;
            break;

        //subtract r32 from r32
        case INSTR(r32, r32, vm_sub):
            INSTR_PRINT("r32 r32 sub", arg1, arg2);
            R32(arg2) -= R32(arg1);
            break;

        //subtract l32 from r32
        case INSTR(l32, r32, vm_sub):
            INSTR_PRINT("l32 r32 sub", arg1, arg2);
            R32(arg2) -= (uint32_t)arg1;
            break;
        
        //multiply r16 with r16
        case INSTR(r16, r16, vm_mul):
            INSTR_PRINT("r16 r16 mul", arg1, arg2);
            R16(arg2) *= R16(arg1);
            break;

        //multiply l16 with r16
        case INSTR(l16, r16, vm_mul):
            INSTR_PRINT("l16 r16 mul", arg1, arg2);
            R16(arg2) *= (uint16_t)arg1;
            break;

        //multiply r32 with r32
        case INSTR(r32, r32, vm_mul):
            INSTR_PRINT("r32 r32 mul", arg1, arg2);
            R32(arg2) *= R32(arg1);
            break;

        //multiply l32 with r32
        case INSTR(l32, r32, vm_mul):
            INSTR_PRINT("l32 r32 mul", arg1, arg2);
            R32(arg2) *= (uint32_t)arg1;
            break;

        //divide r16 by r16
        case INSTR(r16, r16, vm_div):
            INSTR_PRINT("r16 r16 div", arg1, arg2);
            R16(arg2) /= R16(arg1);
            break;

        //divide r16 by l16
        case INSTR(l16, r16, vm_div):
            INSTR_PRINT("l16 r16 div", arg1, arg2);
            R16(arg2) /= (uint16_t)arg1;
            break;

        //divide r32 by r32
        case INSTR(r32, r32, vm_div):
            INSTR_PRINT("r32 r32 div", arg1, arg2);
            R32(arg2) /= R32(arg1);
            break;

        //divide r32 by l32
        case INSTR(l32, r32, vm_div):
            INSTR_PRINT("l32 r32 div", arg1, arg2);
            R32(arg2) /= (uint32_t)arg1;
            break;

        //increment r16
        case INSTR(r16, none, vm_inc):
            INSTR_PRINT("r16 none inc", arg1, arg2);
            (R16(arg1))++;
            break;

        //increment r32
        case INSTR(r32, none, vm_inc):
            INSTR_PRINT("r32 none inc", arg1, arg2);
            (R32(arg1))++;
            break;

        //decrement r16
        case INSTR(r16, none, vm_dec):
            INSTR_PRINT("r16 none dec", arg1, arg2);
            (R16(arg1))--;
            break;

        //decrement r32
        case INSTR(r32, none, vm_dec):
            INSTR_PRINT("r32 none dec", arg1, arg2);
            (R32(arg1))--;
            break;

        //add r32 to r32 as floating point
        case INSTR(r32, r32, vm_fadd):
            INSTR_PRINT("r32 r32 fadd", arg1, arg2);
            RF(arg2) += RF(arg1);
            break;

        //subtract r32 from r32 as floating point
        case INSTR(r32, r32, vm_fsub):
            INSTR_PRINT("r32 r32 fsub", arg1, arg2);
            RF(arg2) -= RF(arg1);
            break;

        //multiply r32 with r32 as floating point
        case INSTR(r32, r32, vm_fmul):
            INSTR_PRINT("r32 r32 fmul", arg1, arg2);
            RF(arg2) *= RF(arg1);
            break;

        //divide r32 by r32 as floating point
        case INSTR(r32, r32, vm_fdiv):
            INSTR_PRINT("r32 r32 fdiv", arg1, arg2);
            RF(arg2) /= RF(arg1);
            break;

        //get square root of r32 as floating point
        case INSTR(r32, r32, vm_fsqrt):
            INSTR_PRINT("r32 r32 fsqrt", arg1, arg2);
            RF(arg2) = sqrt(RF(arg1));
            break;

        //shift r16 left by r16
        case INSTR(r16, r16, vm_shl):
            INSTR_PRINT("r16 r16 shl", arg1, arg2);
            R16(arg2) <<= R16(arg1);
            break;

        //shift r32 left by r16
        case INSTR(r32, r16, vm_shl):
            INSTR_PRINT("r32 r16 shl", arg1, arg2);
            R32(arg2) <<= R16(arg1);
            break;

        //shift r16 right by r16
        case INSTR(r16, r16, vm_shr):
            INSTR_PRINT("r16 r16 shr", arg1, arg2);
            R16(arg2) >>= R16(arg1);
            break;

        //shift r32 right by r16
        case INSTR(r32, r16, vm_shr):
            INSTR_PRINT("r32 r16 shr", arg1, arg2);
            R32(arg2) >>= R16(arg1);
            break;

        //bitwise-and r16 and r16
        case INSTR(r16, r16, vm_and):
            INSTR_PRINT("r16 r16 and", arg1, arg2);
            R16(arg2) &= R16(arg1);
            break;

        //bitwise-and r32 and r32
        case INSTR(r32, r32, vm_and):
            INSTR_PRINT("r32 r32 and", arg1, arg2);
            R32(arg2) &= R16(arg1);
            break;

        //bitwise-or r16 and r16
        case INSTR(r16, r16, vm_or):
            INSTR_PRINT("r16 r16 or", arg1, arg2);
            R16(arg2) |= R16(arg1);
            break;

        //bitwise-or r32 and r32
        case INSTR(r32, r32, vm_or):
            INSTR_PRINT("r32 r32 or", arg1, arg2);
            R32(arg2) |= R16(arg1);
            break;

        //bitwise-not r16
        case INSTR(r16, none, vm_not):
            INSTR_PRINT("r16 none not", arg1, arg2);
            R16(arg1) = ~R16(arg1);
            break;

        //bitwise-not r32
        case INSTR(r32, none, vm_not):
            INSTR_PRINT("r32 none not", arg1, arg2);
            R32(arg1) = ~R16(arg1);
            break;

        //bitwise-xor r16 and r16
        case INSTR(r16, r16, vm_xor):
            INSTR_PRINT("r16 r16 xor", arg1, arg2);
            R16(arg2) ^= R16(arg1);
            break;

        //bitwise-xor r32 and r32
        case INSTR(r32, r32, vm_xor):
            INSTR_PRINT("r32 r32 xor", arg1, arg2);
            R32(arg2) ^= R16(arg1);
            break;

        //unconditional jump to l16
        case INSTR(l16, none, vm_jmp):
            INSTR_PRINT("l16 none jmp", arg1, arg2);
            R16(ip) = (dtptr_t)arg1 - 3;
            break;

        //unconditional jump to r16
        case INSTR(r16, none, vm_jmp):
            INSTR_PRINT("r16 none jmp", arg1, arg2);
            R16(ip) = R16(arg1) - 4;
            break;

        //jump to l16 if r16 is zero
        case INSTR(l16, r16, vm_jze):
            INSTR_PRINT("l16 r16 jze", arg1, arg2);
            if(R16(arg2)) break;
            R16(ip) = (dtptr_t)arg1 - 5;
            break;

        //jump to r16 if r16 is zero
        case INSTR(r16, r16, vm_jze):
            INSTR_PRINT("r16 r16 jze", arg1, arg2);
            if(R16(arg2)) break;
            R16(ip) = R16(arg1) - 6;
            break;

        //jump to l16 if r32 is zero
        case INSTR(l16, r32, vm_jze):
            INSTR_PRINT("l16 r32 jze", arg1, arg2);
            if(R32(arg2)) break;
            R16(ip) = arg1 - 7;
            break;

        //jump to r16 if r32 is zero
        case INSTR(r16, r32, vm_jze):
            INSTR_PRINT("r16 r32 jze", arg1, arg2);
            if(R32(arg2)) break;
            R16(ip) = R16(arg1) - 8;
            break;

        //error, jump to panic interrupt
        default:
            cpu_cal_int(pai);
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
    printf("gpr0:\t%08X\ngpr1:\t%08X\ngpr2:\t%08X\ngpr3:\t%08X\nip:\t%04X\nsp:\t%04X\nstat:\t%04X\n",
           R32(gpr0), R32(gpr1), R32(gpr2), R32(gpr3), R16(ip), R16(sp), R16(stat));
}

//function for calling interrupt
void cpu_cal_int(intrpt_t interrupt)
{
    mem_write_16((dtptr_t)R16(sp), R16(sp));
    R16(sp) += 2;
    R16(ip) = (dtptr_t)(((uint8_t)R16(stat) << 8) + interrupt);
}