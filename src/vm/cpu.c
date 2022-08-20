#include "cpu.h"
#include "memory/mem_access.h"
#include <stdbool.h>

//types for pointers to general perpose registers
typedef enum
{
    gpr0 = 0,
    gpr1 = 4,
    gpr2 = 8,
    gpr3 = 12
}gpr32ptr_t;

typedef enum
{
    gpr0l = gpr0,
    gpr0h = gpr0 + 2,
    gpr1l = gpr1,
    gpr1h = gpr1 + 2,
    gpr2l = gpr2,
    gpr2h = gpr2 + 2,
    gpr3l = gpr3,
    gpr3h = gpr3 + 2
}gpr16ptr_t;

//type for representing instruction argument
typedef union
{
    uint16_t l16;
    uint32_t l32;
    dtptr_t m16;
    dtptr_t m32;
    gpr16ptr_t r16;
    gpr32ptr_t r32;
}arg_t;

//struct for holding cpu information
static struct
{
    uint8_t gp_regs[16];    //memory for general perpose registers

    uint16_t status;    //status register
    uint16_t ip;  //instruction pointer
    uint16_t sp;   //stack pointer
    uint16_t ivtp;   //pointer to interrupt vector table
}cpu;