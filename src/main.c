#include <stdio.h>
#include <stdlib.h>
#include "vm/memory/mem_access.h"
#include "vm/memory/mem_config.h"

int main(void)
{
    if(! mem_load(0x0, 14, "Hello, World!"))
        printf("LOAD!");

    mem_write_16(0xF, 0x1234);
    mem_write_32(0x12, 0x87654321);

    printf("fech_16 at 0xF: %x\n", mem_fech_16(0xF));
    printf("fech_16 at 0x14: %x\n", mem_fech_16(0x14));
    printf("fech_32 at 0x12: %x\n", mem_fech_32(0x12));
    printf("fech_32 at 0xF: %x\n", mem_fech_32(0xF));

    if(! mem_print(0x0, 30))
        printf("PRINT!");

    return EXIT_SUCCESS;
}