#include "mem_access.h"
#include "mem_config.h"

static uint8_t memory[0xFFFF];

//=======================================================================================================fech memory functions
uint16_t mem_fech_16(dtptr_t addr)
{
    return *(uint16_t*)(memory + addr);
}

uint32_t mem_fech_32(dtptr_t addr)
{
    return *(uint32_t*)(memory + addr);
}

//=======================================================================================================write memory functions
void mem_write_16(dtptr_t addr, uint8_t data);
void mem_write_32(dtptr_t addr, uint8_t data);