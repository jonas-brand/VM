#include <stdio.h>
#include <stdlib.h>
#include "vm/memory/mem_access.h"
#include "vm/memory/mem_config.h"

int main(void)
{
    mem_print(0xFF, 10);

    return EXIT_SUCCESS;
}