#include <stdint.h>
#include <stddef.h>

#if defined(__x86_64__) && !defined(_WIN32)
    #define EFIAPI __attribute__((ms_abi))
#else
    #define EFIAPI
#endif

typedef uint64_t EFI_STATUS;
typedef void* EFI_HANDLE;
typedef uint16_t CHAR16;

struct _EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL;

typedef EFI_STATUS (EFIAPI *EFI_TEXT_CLEAR_SCREEN)(
    struct _EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL *This
);

typedef EFI_STATUS (EFIAPI *EFI_TEXT_STRING)(
    struct _EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL *This,
    CHAR16                                   *String
);

typedef struct _EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL {
    void* _pad0;
    EFI_TEXT_STRING OutputString;
    void* _pad1[4];
    EFI_TEXT_CLEAR_SCREEN ClearScreen;
} EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL;

typedef struct { 
    uint8_t _pad[64];
    EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL *ConOut;
} EFI_SYSTEM_TABLE;

EFI_STATUS EFIAPI efi_main(EFI_HANDLE ImageHandle, EFI_SYSTEM_TABLE *SystemTable) {
    (void)ImageHandle;

    SystemTable->ConOut->ClearScreen(SystemTable->ConOut);
    SystemTable->ConOut->OutputString(SystemTable->ConOut, u"hello from c");

    while (1) {
        __asm__ __volatile__("hlt");
    }

    return 0;
}