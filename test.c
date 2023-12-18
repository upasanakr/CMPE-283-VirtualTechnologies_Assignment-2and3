#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <cpuid.h>

void print_cpuid(uint32_t eax, uint32_t ecx) {
    uint32_t reg_eax, reg_ebx, reg_ecx, reg_edx;
    __cpuid_count(eax, ecx, reg_eax, reg_ebx, reg_ecx, reg_edx);

    // Print all return values in hex
    //printf("Return values - EAX: 0x%08x, EBX: 0x%08x, ECX: 0x%08x, EDX: 0x%08x\n", reg_eax, reg_ebx, reg_ecx, reg_edx);

    if (eax == 0x4FFFFFFF) {
        printf("CPUID(0x4FFFFFFF) Return values - EAX: 0x%08x, EBX: 0x%08x, ECX: 0x%08x, EDX: 0x%08x\n", reg_eax, reg_ebx, reg_ecx, reg_edx);
        printf("CPUID(0x4FFFFFFF) Total exits is: %u\n", reg_eax);
    } else if (eax == 0x4FFFFFFE) {
        uint64_t total_time = ((uint64_t)reg_ebx << 32) | reg_ecx;
        printf("CPUID(0x4FFFFFFE) Return values - EAX: 0x%08x, EBX: 0x%08x, ECX: 0x%08x, EDX: 0x%08x\n", reg_eax, reg_ebx, reg_ecx, reg_edx);
        printf("CPUID(0x4FFFFFFE) Total time in VMM cycles: %llu\n", total_time);
    } else if (eax == 0x4FFFFFFD) {
        printf("CPUID(0x4FFFFFFD) Return values - EAX: 0x%08x, EBX: 0x%08x, ECX: 0x%08x, EDX: 0x%08x\n", reg_eax, reg_ebx, reg_ecx, reg_edx);
        printf("CPUID(0x4FFFFFFD) For exit type %u, total exits: %u\n", ecx, reg_eax);
    }
    else if(eax == 0x4FFFFFFC){
        uint64_t time_for_exit = ((uint64_t)reg_ebx << 32) | reg_ecx;
        printf("CPUID(0x4FFFFFFC) Return values - EAX: 0x%08x, EBX: 0x%08x, ECX: 0x%08x, EDX: 0x%08x\n", reg_eax, reg_ebx, reg_ecx, reg_edx);
        printf("CPUID(0x4FFFFFFC) Time for exit type %u in VMM cycles: %llu\n", ecx, time_for_exit);
    }
}

int main(int argc, char *argv[]) {
    if (argc == 1) {
        // No arguments: Query for 0x4FFFFFFF and 0x4FFFFFFE
        print_cpuid(0x4FFFFFFF, 0);
        printf("\n");
        print_cpuid(0x4FFFFFFE, 0);
    } else {
        // Argument provided: Query for 0x4FFFFFFD and 0x4FFFFFFC with the given exit type
        uint32_t exit_type = (uint32_t)atoi(argv[1]);
        print_cpuid(0x4FFFFFFD, exit_type);
        printf("\n");
        print_cpuid(0x4FFFFFFC, exit_type);
    }
    return 0;
}
