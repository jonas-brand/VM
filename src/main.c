#include <stdio.h>
#include <stdlib.h>
#include "vm/cpu.h"
#include "vm/memory/mem_config.h"

#define PRGM_SIZE 50

#define DT16(dt) (uint8_t)dt, (uint8_t)(dt >> 8)
#define DT32(dt) (uint8_t)dt, (uint8_t)(dt >> 8), (uint8_t)(dt >> 16), (uint8_t)(dt >> 24)

static uint8_t prgm[PRGM_SIZE] =
{
    DT16(INSTR(l16, r16, vm_mov)), DT16(0xFF), sp,
    DT16(INSTR(l16, r16, vm_mov)), DT16(37), gpr0l,
    DT16(INSTR(r16, none, vm_psh)), gpr0l,
    DT16(INSTR(l32, r32, vm_mov)), DT32(5), gpr0,
    DT16(INSTR(r32, none, vm_psh)), gpr0,
    DT16(INSTR(l32, r32, vm_mov)), DT32(6), gpr0,
    DT16(INSTR(r32, none, vm_psh)), gpr0,
    DT16(INSTR(l16, none, vm_jmp)), DT16(PRGM_SIZE),
    DT16(INSTR(l16, none, vm_jmp)), DT16(37)
};

static uint8_t subrtn_mul[PRGM_SIZE] =
{
    DT16(INSTR(r32, none, vm_pop)), gpr0,
    DT16(INSTR(r32, none, vm_pop)), gpr1,
    DT16(INSTR(r32, r32, vm_mul)), gpr1, gpr0,
    DT16(INSTR(r16, none, vm_pop)), gpr1l,
    DT16(INSTR(r16, none, vm_jmp)), gpr1l
};

int main(void)
{
    mem_load(0x0000, PRGM_SIZE, prgm);
    mem_load(PRGM_SIZE, PRGM_SIZE, subrtn_mul);

    cpu_print();

    for(uint8_t i = 0; i < 20; i++)
    {
        printf("\n");
        cpu_clk();
        cpu_print();
    }
}