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

    if(! mem_print(0x0, 30))
        printf("PRINT!");

    return EXIT_SUCCESS;
}