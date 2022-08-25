#include <stdio.h>
#include <stdlib.h>
#include "vm/cpu.h"
#include "vm/memory/mem_config.h"

#define PRGM_SIZE 30

#define DT16(dt) (uint8_t)dt, (uint8_t)(dt >> 8)
#define DT32(dt) (uint8_t)dt, (uint8_t)(dt >> 8), (uint8_t)(dt >> 16), (uint8_t)(dt >> 24)

static uint8_t prgm[PRGM_SIZE] =
{
    DT16(INSTR(l16, r16, vm_mov)), DT16(0xFF), sp,
    DT16(INSTR(l32, none, vm_psh)), DT32(5),
    DT16(INSTR(l32, none, vm_psh)), DT32(6),
    DT16(INSTR(none, none, vm_nop)),
    DT16(INSTR(none, none, vm_nop)),
    DT16(INSTR(none, none, vm_nop)),
    DT16(INSTR(r16, none, vm_psh)), sp,
    DT16(INSTR(r16, none, vm_pop)), gpr2l,
    DT16(INSTR(l16, r16, vm_sub)), 2, gpr2l,
    
};

int main(void)
{
    mem_load(0x0000, PRGM_SIZE, prgm);

    cpu_print();

    for(uint8_t i = 0; i < 8; i++)
    {
        printf("\n");
        cpu_clk();
        cpu_print();
    }
}