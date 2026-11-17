#ifndef KERNEL_STRUCTS_H
#define KERNEL_STRUCTS_H

#include "EFI_TYPES.h"

typedef struct {
    EFI_MEMORY_DESCRIPTOR *MemoryMap;
    UINTN *MemoryMapSize;
    void *RuntimeServices;
} BootParams;

#endif