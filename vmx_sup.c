#include <stdio.h>

int main() {
	int get_vmx_support, vmx_bit;
    	__asm__("mov $1, %eax");
		  __asm__("mov $0, %ecx");
    	__asm__("cpuid");
    	__asm__("mov %%ecx, %0\n\t":"=r" (get_vmx_support));
    	vmx_bit = (get_vmx_support >> 5) & 1;
    	if (vmx_bit == 1) {
        	printf("VMX is supported\n");
    	} else {
        	printf("VMX is NOT supported!\n");
    	}
	return 0;
}
