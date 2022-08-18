#include <stdio.h>
#include <stdlib.h>
#include "vm/memory/mem_access.h"
#include "vm/memory/mem_config.h"

int main(void)
{
    if(! mem_load(0x0, 14, "Hello, World!"))
        printf("LOAD!");

    if(! mem_print(0x0, 0xFF))
        printf("PRINT!");

    return EXIT_SUCCESS;
}