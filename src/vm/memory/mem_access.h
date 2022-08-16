#ifndef __MEMORY_ACCESS_H__
#define __MEMORY_ACCESS_H__

#include "mem_types.h"

//fech memory functions
uint8_t mem_fech_8(dtptr_t addr);
uint16_t mem_fech_16(dtptr_t addr);
uint32_t mem_fech_32(dtptr_t addr);
uint64_t mem_fech_64(dtptr_t addr);

//write memory functions
void mem_write_8(dtptr_t addr, uint8_t data);
void mem_write_16(dtptr_t addr, uint8_t data);
void mem_write_32(dtptr_t addr, uint8_t data);
void mem_write_64(dtptr_t addr, uint8_t data);

#endif //! __MEMORY_ACCESS_H__