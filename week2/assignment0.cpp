#include <iostream>
#include <cstdio>   // For printf
using namespace std;

int main() {
    int integer_value = 42;
    float float_value = 3.14159265f;
    double double_value = 3.14159265;
    char char_value = 'X';
    const char* string_value = "Hello, World!";

    printf("Format Specifier Practice\n");
    printf("------------------------\n\n");

    // Integer formats
    printf("Integer formats:\n");
    printf("Decimal: %d\n", integer_value);               // %d for standard decimal
    printf("Hexadecimal: 0x%x\n", integer_value);         // %x for lowercase hex
    printf("Octal: 0%o\n", integer_value);                // %o for octal
    printf("With width (5): |%5d|\n", integer_value);     // %5d pads with spaces to 5 chars
    printf("Left-aligned:   |%-5d|\n\n", integer_value);  // %-5d aligns to the left

    // Float formats
    printf("Float formats:\n");
    printf("Default: %f\n", float_value);                 // %f for fixed-point decimal
    printf("With precision (2): %.2f\n", float_value);    // %.2f rounds to 2 decimal places
    printf("Scientific: %e\n", float_value);              // %e for scientific notation
    printf("Fixed with precision (4): %.4f\n\n", float_value);

    // Character and String formats
    printf("Character and String formats:\n");
    printf("Character: %c\n", char_value);                // %c for a single character
    printf("String: %s\n", string_value);                 // %s for a null-terminated string
    printf("String with width (20): |%20s|\n", string_value); // %20s pads string to 20 chars

    return 0;
}
