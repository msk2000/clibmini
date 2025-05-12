/*
 * clibmini.h - A Minimal C Library for Kernel/OS Development
 *
 * Author: M Safat Khan
 * License: GPL
 * 
 * Description:
 * This header defines a lightweight set of utility functions designed to support 
 * kernel or bare-metal OS development, where full standard C libraries are typically 
 * unavailable or unsuitable. It includes essential routines for formatted printing, 
 * string manipulation, and data conversion (e.g., integers, floating points, and hex).
 * 
 * Key Features:
 *  - Basic printf-style formatted output via `print`
 *  - Custom string length and copy functions
 *  - Integer and floating-point to string conversions
 *  - Hexadecimal conversion with optional uppercase output
 *
 * Intended Use:
 *  Use in low-level environments where dependencies must be minimal and reliable.
 *  These functions are self-contained and do not rely on libc or dynamic memory.
 *
 * Notes:
 *  This header is C and C++ compatible via `extern "C"`.
 */
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
