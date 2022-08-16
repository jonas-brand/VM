#ifndef __MEMORY__
#define __MEMORY__

#include <stdint.h>

//type to store memory adresses of vm
typedef uint16_t dtptr_t;

//type to store memory page address of vm
typedef uint8_t pgptr_t;

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

//function type for actions to be taken when acessing mapped memory
typedef void (*memacc_act_t)(dtptr_t addr);

//function for configuring maped memory
void mem_map(pgptr_t page, memacc_act_t on_fech, memacc_act_t on_write);

#endif //! __MEMORY__