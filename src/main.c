#include <stdio.h>
#include <stdlib.h>
#include "vm/cpu.h"
#include "vm/memory/mem_config.h"

#define PRGM_SIZE 30

#define DT16(dt) (uint8_t)dt, (uint8_t)(dt >> 8)
#define DT16(dt) (uint8_t)dt, (uint8_t)(dt >> 8), (uint8_t)(dt >> 16), (uint8_t)(dt >> 24)

static uint8_t prgm[PRGM_SIZE] =
{
    
};

int main(void)
{
    return EXIT_SUCCESS;
}