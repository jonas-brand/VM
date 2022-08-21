#include <stdio.h>
#include <stdlib.h>
#include "vm/cpu.h"
#include "vm/memory/mem_config.h"

#define PRGM_SIZE 30

#define DT16(dt) (uint8_t)dt, (uint8_t)(dt >> 8)
#define DT32(dt) (uint8_t)dt, (uint8_t)(dt >> 8), (uint8_t)(dt >> 16), (uint8_t)(dt >> 24)

static uint8_t prgm[PRGM_SIZE] =
{
    DT16(INSTR(l16, r16, vm_mov)), DT16(5), gpr0l,          //gpr01 = 5
    DT16(INSTR(l16, r16, vm_mov)), DT16(3), gpr0h,          //gpr0h = 3
    DT16(INSTR(r16, r16, vm_mul)), gpr0h, gpr0l,            //gpr0l *= gpr0h  
    DT16(INSTR(l32, r32, vm_mov)), DT32(0xFFFFFFFF), gpr1,  //gpr1 = 0xFFFFFFFF
    DT16(INSTR(r32, r32, vm_sub)), gpr0, gpr1,              //gpr1 -= gpr0
    DT16(INSTR(r32, m32, vm_mov)), gpr1, DT16(0xFF00)       //%ff00 = gpr1
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

    printf("\n");
    mem_print(0xFF00, 10);

    return EXIT_SUCCESS;
}