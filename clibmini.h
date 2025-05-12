// clibmini.h
// In the absense of a lot of useful c functions to print and manipulate data
// I wrote these functions to help the kernel get some work done
#ifndef CLIBMINI_H
#define CLIBMINI_H

#include <stdarg.h>

// A lightweight mini C library for kernel projects

#ifdef __cplusplus
extern "C" {
#endif

// Core print function (printf-style formatting)
void print(char* format_str, ...);

// String manipulation
int strlen2(char* string);
void strncpy2(char* destination, const char* source, int num);

// Integer to string conversion
int int_to_str(int value, char* str);
// Function to convert uint to str
int uint_to_str(unsigned int value, char* str);
// Double to string conversion with precision
int double_to_str(double value, char* str, int precision);
// Copies a string from source to destination and returns character count
int string_to_str(char* source, char* destination);
// Function to convert uint to hex str
int uint_to_hex_str(unsigned int value, char* buffer, int uppercase);


#ifdef __cplusplus
}
#endif

#endif // CLIBMINI_H
