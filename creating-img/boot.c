#include "EFI_TYPES.h"
#include "kernel_structs.h"

typedef (__attribute((sysv_abi)) *K_Main) (
    BootParams boot_params
);

EFI_STATUS EFIAPI efi_main(EFI_HANDLE ImageHandle, EFI_SYSTEM_TABLE *SystemTable) {
    (void)ImageHandle;

    SystemTable->ConOut->ClearScreen(SystemTable->ConOut);
    SystemTable->ConOut->OutputString(SystemTable->ConOut, u"hello from c");

    BootParams *toKernel;
    UINTN *MapKey;
    UINTN *DescriptorSize;
    UINT32 *DescriptorVersion;

    SystemTable->BootServices->GetMemoryMap(
        toKernel->MemoryMapSize,
        toKernel->MemoryMap,
        MapKey,
        DescriptorSize,
        DescriptorVersion
    );

    while (1) {
        __asm__ __volatile__("hlt");
    }

    return 0;
}