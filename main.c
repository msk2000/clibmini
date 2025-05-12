/*
 * test_main.c - Test Suite for clibmini (Minimal C Library for Kernel/OS Development)
 *
 * Author: M Safat Khan
 * License: GPL
 *
 * Description:
 * This file contains a standalone test harness for verifying the functionality of
 * the `clibmini` library — a minimal, self-contained C library intended for use
 * in kernel or low-level OS development where the standard C library is unavailable.
 *
 * The test cases demonstrate:
 *  - Formatted printing of strings, integers, unsigned integers, characters, and floats
 *  - Hexadecimal output in both lowercase and uppercase
 *  - Handling of special characters and escape sequences
 *  - Mixed-type formatted output using custom `print` function
 *
 * Usage:
 *  Compile this test alongside `clibmini.c` and run it in an appropriate bare-metal,
 *  embedded, or emulated environment to validate the custom print and utility routines.
 *
 * Note:
 *  This test assumes the presence of a working output mechanism (e.g., serial port
 *  or framebuffer) hooked up to the `print` function. It should just work like usual
 *  printf() on a standard PC.
 */


#include <stdarg.h>
#include "clibmini.h" // The custom c library



int main()
{
    char* name = "Random";
    int age = -99;
    unsigned int score = 1500;
    float accuracy = 69.69;
    char grade = 'A';
    char* subject = "Underwater Basket Weaving";
    unsigned int hex_value = 420420420;


    // Run test cases
    print("Test 1: Name: %s\n", name);                  // Expect: Test 1: Name: Random
    print("Test 2: Age: %d\n", age);                    // Expect: Test 2: Age: -99
    print("Test 3: Score: %u\n", score);                // Expect: Test 3: Score: 1500
    print("Test 4: Grade: %c\n", grade);                // Expect: Test 4: Grade: A
    print("Test 5: Info: %s %d %u %c %s\n", name, age, score, grade, subject);
    // Expect: Test 5: Info: Alice 30 1500 A Underwater Basket Weaving
    print("Test 6: Hex lowercase: %x\n", hex_value);    // Expect: Test 6: Hex lowercase: 190f1b44
    print("Test 7: Hex UPPERCASE: %X\n", hex_value);    // Expect: Test 7: Hex UPPERCASE: 190F1B44
    print("Test 8: Special chars:\nLine 1\nLine 2\nBackslash: \\\n");
    // Expect: Test 8: Special chars: [line break] Line 1 [line break] Line 2 [line break] Backslash: '\'
    print("Test 9: Accuracy = %f\n",accuracy);          //Expect: Test 9: Accuracy = 69.69

    return 0;
}

