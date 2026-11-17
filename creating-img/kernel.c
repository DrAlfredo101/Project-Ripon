#include "kernel_structs.h"

// Recieve the memory locations for where bss
// starts and ends to 0 out later. They are
// stored as chars so that memory can be 
// advanced one byte at a time and no header
// files are needed for data types.
extern char _bss_start[];
extern char _bss_end[];

__attribute__((sysv_abi))
__attribute__((section(".text.kernel_entry")))
__attribute__((noreturn))
void kernelMain(BootParams *boot_params) {
    // First thing we need to do is 0 out the
    // bss section. This is because of some
    // c standard where all uninitialised
    // variables must be 0 and that is where
    // they are stored.
    for (char *p = _bss_start; p < _bss_end; p++) {
        *p = 0;
    }

    // Big fucky wucky control.
    // If the kernel loop ever breaks, it is
    // ideal for the kernel not to exit, so 
    // instead we loop it forever and ever,
    // until the heat death of the universe
    // (or the pc turns off whichever is first).
    while(1) {
        __asm__ volatile("hlt");
    }
}