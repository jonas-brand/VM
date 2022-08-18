#ifndef __MEMORY_CONFIG_H__
#define __MEMORY_CONFIG_H__

#include "mem_types.h"
#include "stdbool.h"

//function types for actions to be taken when acessing mapped memory
typedef void (*memwrite_act_t)(uint8_t* mem, dtptr_t addr, uint32_t data);
typedef uint32_t (*memfech_act_t)(uint8_t* mem, dtptr_t addr);

//function for configuring maped memory
void mem_map(pgptr_t page, memfech_act_t on_fech, memwrite_act_t on_write);

//function for loading data into memory
bool mem_load(dtptr_t addr, size_t size, uint8_t* data);

//function for printing out memory
bool mem_print(dtptr_t addr, size_t size);

#endif //! __MEMORY_CONFIG_H__