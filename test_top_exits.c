#include <stdio.h>
#include <stdint.h>

#if defined(__i386__) || defined(__x86_64__)
#include <cpuid.h>
#else
#error "Unsupported architecture. Only x86 and x86_64 are supported."
#endif

#define MAX_EXIT_TYPES 76

void query_cpuid(uint32_t eax_val, uint32_t ecx_val, uint32_t* eax, uint32_t* ebx, uint32_t* ecx, uint32_t* edx) {
    __cpuid_count(eax_val, ecx_val, *eax, *ebx, *ecx, *edx);
}

int main() {
    uint32_t eax, ebx, ecx, edx;
    uint32_t exit_counts[MAX_EXIT_TYPES] = {0};

    // Call cpuid for each exit type and store the results
    for (uint32_t i = 0; i < MAX_EXIT_TYPES; ++i) {
        query_cpuid(0x4FFFFFFD, i, &eax, &ebx, &ecx, &edx);
        exit_counts[i] = eax;
        printf("Exit number: %u, Exits count: %u\n", i, eax);
    }

    // Find the top 5 exit types
    printf("\nTop 5 Exit Types:\n");
    for (int j = 0; j < 5; ++j) {
        uint32_t max_count = 0;
        uint32_t max_index = 0;
        for (uint32_t i = 0; i < MAX_EXIT_TYPES; ++i) {
            if (exit_counts[i] > max_count) {
                max_count = exit_counts[i];
                max_index = i;
            }
        }
        // Print and zero out the max count to find the next highest
        printf("Exit number: %u, Exits count: %u\n", max_index, max_count);
        exit_counts[max_index] = 0;
    }

    return 0;
}
