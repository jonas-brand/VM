#ifndef __MEMORY_CONFIG_H__
#define __MEMORY_CONFIG_H__

#include "mem_types.h"

//function type for actions to be taken when acessing mapped memory
typedef void (*memacc_act_t)(dtptr_t addr);

//function for configuring maped memory
void mem_map(pgptr_t page, memacc_act_t on_fech, memacc_act_t on_write);

#endif __MEMORY_CONFIG_H__