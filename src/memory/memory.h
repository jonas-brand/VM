#ifndef __MEMORY__
#define __MEMORY__

#include <stdint.h>

//type to store momory adresses of vm
typedef uint16_t addr_t;

//fech memory functions
uint8_t mem_fech_8(addr_t addr);
uint16_t mem_fech_16(addr_t addr);
uint32_t mem_fech_32(addr_t addr);
uint64_t mem_fech_64(addr_t addr);

//write memory functions
void mem_write_8(addr_t addr, uint8_t data);
void mem_write_16(addr_t addr, uint8_t data);
void mem_write_32(addr_t addr, uint8_t data);
void mem_write_64(addr_t addr, uint8_t data);

#endif //! __MEMORY__