#include "mem_access.h"
#include "mem_config.h"
#include <memory.h>
#include <stdio.h>

//page mapping configuration
static struct
{
    bool mapped;
    memacc_act_t on_fech;
    memacc_act_t on_write;
}pgconfig[0xFF];

//main memory
static uint8_t memory[0xFFFF];

//===========================================================================================fech memory functions
uint16_t mem_fech_16(dtptr_t addr)
{
    return *(uint16_t*)(memory + addr);
}

uint32_t mem_fech_32(dtptr_t addr)
{
    return *(uint32_t*)(memory + addr);
}

//===========================================================================================write memory functions
void mem_write_16(dtptr_t addr, uint16_t data)
{
    *(uint16_t*)(memory + addr) = data;
}

void mem_write_32(dtptr_t addr, uint32_t data)
{
    *(uint32_t*)(memory + addr) = data;
}

//===========================================================================================function for configuring maped memory
void mem_map(pgptr_t page, memacc_act_t on_fech, memacc_act_t on_write)
{
    pgconfig[page].mapped = true;
    pgconfig[page].on_fech = on_fech;
    pgconfig[page].on_write = on_write;
}

//===========================================================================================function for loading data into memory
bool mem_load(dtptr_t addr, size_t size, uint8_t* data)
{
    if(((uint32_t)addr + size) > 0xFF) return false;

    memcpy(memory + addr, data, size);
}

//===========================================================================================function for printing out memory
bool mem_print(dtptr_t addr, size_t size)
{
    if(((uint32_t)addr + size) > 0xFF) return false;

    for(addr; addr < (addr + size); addr++)
        printf("%x/t%x", addr, memory[addr]);
}