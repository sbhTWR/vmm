#include <linux/module.h>

int vmx_support(void);

static int vmx_init(void) {
    printk(KERN_INFO "[VMX] Starting...\n");
    /* Check for VMX support */

    if (vmx_support()) {
        printk(KERN_INFO "[VMX] vmx is supported.\n");
    } else {
        printk(KERN_INFO "[Vmx] vmx is not supported.\n");
    }
    return 0;
}

/* Checks for vmx support. Uses inline assembly 
    set eax = 1 and call cpuid. Bit 5 in ecx shows 
    whether vmx is supported or not! */

int vmx_support(void) {
    int get_vmx_support, vmx_bit;
    asm volatile ("mov $1, %eax");
    asm volatile ("mov $0, %ecx");
    asm volatile ("cpuid");
    asm volatile ("mov %%ecx, %0\n\t":"=r" (get_vmx_support): : "memory"); 

    vmx_bit = (get_vmx_support >> 5) & 1;
    if (vmx_bit == 1) {
        return 1;
    } else {
        return 0;
    }

    /* unsigned int eax, ebx, ecx, edx;
    eax = 1;
    ecx = 0;
    asm volatile("cpuid"
	    : "=a" (eax),
	      "=b" (ebx),
	      "=c" (ecx),
	      "=d" (edx)
	    : "0" (eax), "2" (ecx)
	    : "memory");

    vmx_bit = (ecx >> 5) & 1;
    if (vmx_bit == 1) {
        return 1;
    } else {
        return 0;
    } */
}

static void vmx_exit(void) {
    printk(KERN_INFO "[VMX] Exiting...\n");
    return;
}

module_init(vmx_init);
module_exit(vmx_exit);
