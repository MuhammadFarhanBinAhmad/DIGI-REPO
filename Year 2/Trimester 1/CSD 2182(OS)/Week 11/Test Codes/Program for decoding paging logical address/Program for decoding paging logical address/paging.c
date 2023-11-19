#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdint.h> // Include the stdint.h library for uintptr_t

void printBinary(uintptr_t value, int numBits) {
    for (int i = numBits - 1; i >= 0; i--) {
        printf("%zu", (value >> i) & 1);
        if (i % 4 == 0) {
            printf(" "); // Add a space for better readability
        }
    }
}

void oneLevelPaging(uintptr_t address) {
    uintptr_t offset = address & 0xFFF;
    uintptr_t page = (address >> 12) & 0xFFFFF;
    
    printf("Under 1-level paging....\n");
    printf("Offset: in Hexadecimal = %zx ",offset);
    printf(", in Binary = "); printBinary(offset, 12);
    printf("\nPage Number: in Hexadecimal = %zx ",page);
    printf(", in Binary = "); printBinary(page, 20);
    printf("\n\n");
}

void twoLevelPaging(uintptr_t address) {
    uintptr_t offset = address & 0xFFF;
    uintptr_t page2 = (address >> 12) & 0x3FF;
    uintptr_t page1 = (address >> 22) & 0x3FF;
    
    printf("Under 2-level paging....\n");
    printf("Offset: in Hexadecimal = %zx ",offset);
    printf(", in Binary = "); printBinary(offset, 12);
    printf("\nPage Number (Level 2): in Hexadecimal = %zx ",page2);
    printf(", in Binary = "); printBinary(page2, 10);
    printf("\nPage Directory Number (Level 1): in Hexadecimal = %zx ",page1);
    printf(", in Binary = "); printBinary(page1, 10);
    printf("\n\n");
}

uintptr_t generateRandomAddress() {
    // Generate a random 32-bit address (hexadecimal)
    return ((uintptr_t)rand() & 0xFFFFFFF);
}

int main() {
    srand((unsigned int)time(NULL)); // Seed the random number generator
    uintptr_t address = generateRandomAddress();
    //address = 0x18818f34;

    printf("\n\nAddress in Hexadecimal is: %p ", (void*)address);
    printf(", Binary is: "); 
    printBinary(address, 32);
    printf("\n\n");
    printf("###############################################################################\n");    
    oneLevelPaging(address);
    printf("###############################################################################\n");
    twoLevelPaging(address);
    printf("###############################################################################\n");

    return 0;
}
