#include <stdio.h>
#include <stdlib.h>
#include "vm/memory/mem_access.h"
#include "vm/memory/mem_config.h"

int main(void)
{
    if(! mem_print(0x0, 0xFF))
        printf("ERROR!");

    return EXIT_SUCCESS;
}