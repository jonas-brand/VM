#include "cpu.h"
#include "memory/mem_access.h"
#include <stdbool.h>

//type for pointers to general perpose registers
typedef uint16_t regptr_t;

//struct for holding cpu information
static struct
{
    uint8_t gp_regs[16];    //memory for general perpose registers

    //inecies of general perpose registers
    enum
    {
        GPR1 = 0,
        GPR1L = 0,
        GPR1H = 2,
        GPR2 = 4,
        GPR2L = 4,
        GPR2H = 6,
        GPR3 = 8,
        GPR3L = 8,
        GPR3H = 10,
        GPR4 = 12,
        GPR4L = 12,
        GPR4H = 14
    }gpr;

    uint16_t status;    //status register
    uint16_t ip;  //instruction pointer
    uint16_t sp;   //stack pointer
    uint16_t ivtp;   //pointer to interrupt vector table
}cpu;