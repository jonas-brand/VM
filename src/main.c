#include <stdio.h>
#include <stdlib.h>
#include "vm/cpu.h"
#include "vm/memory/mem_config.h"

#define PRGM_SIZE 30

#define DT16(dt) (uint8_t)dt, (uint8_t)(dt >> 8)
#define DT32(dt) (uint8_t)dt, (uint8_t)(dt >> 8), (uint8_t)(dt >> 16), (uint8_t)(dt >> 24)

static uint8_t prgm[PRGM_SIZE] =
{
    DT16(INSTR(l16, r16, vm_mov)), DT16(3), gpr0l,  //gpr01 = 3
    DT16(INSTR(r16, none, vm_dec)), gpr0l,          //gpr0l--
    DT16(INSTR(l16, r16, vm_jze)), DT16(20), gpr0l,  //jump 20 if gpr0l == 0
    DT16(INSTR(l16, none, vm_jmp)), DT16(5)         //jump to 5
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
}