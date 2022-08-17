#ifndef __MEMORY_CONFIG_H__
#define __MEMORY_CONFIG_H__

#include "mem_types.h"

//function type for actions to be taken when acessing mapped memory
typedef void (*memacc_act_t)(uint8_t* mem, dtptr_t addr);

//function for configuring maped memory
void mem_map(pgptr_t page, memacc_act_t on_fech, memacc_act_t on_write);

//function for loading data into memory
bool mem_load(dtptr_t addr, size_t size, uint8_t* data);

#endif __MEMORY_CONFIG_H__