#include <stdio.h>

//initialize the functions 

unsigned int SetBit(unsigned int value, int position);
unsigned int ClearBit(unsigned int value, int position);
unsigned int ToggleBit(unsigned int value, int position);
int          GetBit(unsigned int value, int position);
int          CountBits(unsigned int value);
unsigned int ShiftLeft(unsigned int value, int positions);
unsigned int ShiftRight(unsigned int value, int positions);
void         PrintBinary(unsigned int value);
void         PrintHex(unsigned int value);


unsigned int SetBit(unsigned int value, int position) {
    if (position < 0 || position >= 32) return value;
    return value | (1u << position);
}
unsigned int ClearBit(unsigned int value, int position) {
    if (position < 0 || position >= 32) return value;
    return value & ~(1u << position);
}
unsigned int ToggleBit(unsigned int value, int position) {
    if (position < 0 || position >= 32) return value;
    return value ^ (1u << position);
}
int GetBit(unsigned int value, int position) {
    if (position < 0 || position >= 32) return 0;
    return (value >> position) & 1u;
}
int CountBits(unsigned int value) {
    int c = 0;
    while (value) { c += value & 1u; value >>= 1u; }
    return c;
}
unsigned int ShiftLeft(unsigned int value, int positions) {
    if (positions < 0) return ShiftRight(value, -positions);
    if (positions >= 32) return 0;
    return value << positions;
}
unsigned int ShiftRight(unsigned int value, int positions) {
    if (positions < 0) return ShiftLeft(value, -positions);
    if (positions >= 32) return 0;
    return value >> positions;
}
void PrintBinary(unsigned int value) {
    for (int i = 31; i >= 0; --i) {
        putchar(((value >> i) & 1u) ? '1' : '0');
        if (i % 4 == 0 && i) putchar(' ');
    }
    putchar('\n');
}
void PrintHex(unsigned int value) {
    printf("0x%X\n", value);
}

// Test Driver
int main(void) {
    unsigned int val = 0;

    printf("=== Phase 1: Bit Manipulation Test ===\n\n");

    printf("Initial value:\n");
    PrintBinary(val);
    PrintHex(val);
    printf("\n");

    printf("Set bits 1, 3, and 5:\n");
    val = SetBit(val, 1);
    val = SetBit(val, 3);
    val = SetBit(val, 5);
    PrintBinary(val);
    PrintHex(val);
    printf("\n");

    printf("GetBit at position 3: %d\n", GetBit(val, 3));
    printf("GetBit at position 4: %d\n\n", GetBit(val, 4));

    printf("CountBits: %d\n\n", CountBits(val));

    printf("Toggle bit 3:\n");
    val = ToggleBit(val, 3);
    PrintBinary(val);
    PrintHex(val);
    printf("\n");

    printf("Clear bit 5:\n");
    val = ClearBit(val, 5);
    PrintBinary(val);
    PrintHex(val);
    printf("\n");

    printf("ShiftLeft by 2:\n");
    val = ShiftLeft(val, 2);
    PrintBinary(val);
    PrintHex(val);
    printf("\n");

    printf("ShiftRight by 1:\n");
    val = ShiftRight(val, 1);
    PrintBinary(val);
    PrintHex(val);
    printf("\n");

    printf("End of Test\n");
    return 0;
}