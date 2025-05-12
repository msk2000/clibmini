/*
 * clibmini.c - Minimal C Library Implementation
 * ---------------------------------------------
 * This file provides implementations for a minimal custom standard library
 * used for formatting and outputting text without relying on full C stdlib support.
 * Functions here support:
 *  - Custom formatted printing with basic type support
 *  - String length and copy utilities
 *  - Integer, unsigned, float, hex, and string to ASCII conversion
 *
 * Developed for use in low-level environments or kernel-level applications
 * where standard C I/O functions are not available or desirable.
 *
 * NOTE: The example implementation uses printf for debugging and is not kernel-safe.
 */
#include "clibmini.h"
#include <stdio.h> // For debug prints only in development

/*
 * print - Custom formatted output function
 * ----------------------------------------
 * Mimics a simplified version of printf.
 * Supports format specifiers: %d, %u, %f, %s, %c, %x, %X.
 * Parses format string and variadic arguments, formats them into a buffer,
 * and outputs using printf for development debug purposes.
 */
void print(char* format_str, ...)
{
    //Find the number of chars in format_str
    int total_length = strlen2(format_str);


    //Now we retrieve the arguments based on the symbols used for them

    va_list args;
    va_start(args, format_str);
    int index = 0;
    char buffer[total_length*2];

    for(int i = 0; i < total_length; i++)
    {
        if(format_str[i] == '%')
        {
            char temp[32]; // holds converted value temporarily

            switch(format_str[i+1]) // we want the x in %x<F10>
            {
                case 'd': // handling ints
                    {
                        int d = va_arg(args,int);//reads the next argument of type int from args
                        int char_count = int_to_str(d,temp);
                        strncpy2(&buffer[index], temp, char_count);
                        index += char_count;
                        i++;
                        break;
                    }
                case 'u': // handling unsigned ints
                    {
                        unsigned int u = va_arg(args,unsigned int);
                        int char_count = uint_to_str(u,temp);
                        strncpy2(&buffer[index], temp, char_count);
                        index += char_count;
                        i++;
                        break;
                    }
                case 'f': //handling floats
                    {
                        double f = va_arg(args,double);
                        int char_count = double_to_str(f,temp,2);
                        strncpy2(&buffer[index],temp,char_count);
                        index += char_count;
                        i++;
                        break;
                    }
                case's': // handling strings 
                    {
                        char* s = va_arg(args,char*);
                        int char_count = string_to_str(s,temp);
                        strncpy2(&buffer[index],temp,char_count);
                        index += char_count;
                        i++;
                        break;
                    }
                case 'c': // handling chars 
                    {
                        char c = (char)va_arg(args, int); // variadic promotes cars to int
                        buffer[index] = c; // push c into buffer
                        index += 1;
                        i++;
                        break;
                    }
                case 'x': // handling lowercase hex
                    {
                        unsigned int x = va_arg(args, unsigned int);
                        int char_count = uint_to_hex_str(x, temp, 0); // 0 = lowercase
                        strncpy2(&buffer[index], temp, char_count);
                        index += char_count;
                        i++;
                        break;
                    }
                case 'X': // handling uppercase hex 
                    {
                        unsigned int X = va_arg(args, unsigned int);
                        int char_count = uint_to_hex_str(X, temp, 1); // 1 = uppercase
                        strncpy2(&buffer[index], temp, char_count);
                        index += char_count;
                        i++;
                        break;
                    }

                default:
                    break;

            }
        }
        else if(format_str[i] == '\n')// handling newline
        {
            buffer[index++] = '\r'; //For the damn carriage return bug
            buffer[index++] = '\n'; // plug in \n and increment counter
            // DO NOT i++; skips the next char after new line :P 
        }

        else // push the char to the buffer
        {
            buffer[index] = format_str[i];
            index++;

        }
    }

    buffer[index] = '\0';

    //Debug print
    printf("%s\n",buffer); // View the final output


}

/*
 * strlen2 - Calculates length of a null-terminated string
 * -------------------------------------------------------
 * Returns the number of characters before the null byte.
 * Replacement for standard strlen.
 */
int strlen2(char* string)
{
    int length = 0;
    while(*string != '\0') // As long as we don't see the null byte
    {
        length++; // count a hit
        string++; // advance to the next char
    }

    return length;
}

/*
 * strncpy2 - Copies a specified number of characters from source to destination
 * ---------------------------------------------------------------------------
 * Adds a null terminator to the destination buffer after copying.
 * Replacement for standard strncpy, simplified for controlled environments.
 */
void strncpy2 (char* destination, const char* source, int num )
{

    int index = 0;

    //Copy until end of source or max num
    while (index < num && source[index] != '\0')
    {
        destination[index] = source[index];
        index++;
    }


    // Add a null byte at the end
    destination[index] = '\0';

}

/*
 * uint_to_hex_str - Converts unsigned integer to hexadecimal string
 * ---------------------------------------------------------------
 * Supports both lowercase and uppercase output depending on flag.
 * Returns the number of characters written to the buffer.
 */
int uint_to_hex_str(unsigned int value, char* buffer, int uppercase)
{
    const char* digits;
    
    // Select the right set depending on uppercase == 0 or 1
    if (uppercase) 
    {
        digits = "0123456789ABCDEF";
    } 
    else 
    {
        digits = "0123456789abcdef";
    }
    
    char temp[16]; // enough for 32-bit hex
    int i = 0;

    // Handle zero value 
    if (value == 0) 
    {
        buffer[0] = '0';
        return 1;
    }
    
    // Convert the digits to hex in reverse order
    while (value > 0) 
    {
        temp[i] = digits[value % 16]; // mod 16 because hex is base 16 
        i++;
        value = value/16;
    }

    // reverse the result into buffer
    for (int j = 0; j < i; j++) 
    {
        buffer[j] = temp[i - j - 1];
    }

    return i; // length of hex string
}

/*
 * uint_to_str - Converts unsigned integer to string
 * ------------------------------------------------
 * Converts an unsigned integer to its ASCII decimal representation.
 * Returns the number of characters written to the string buffer.
 */
int uint_to_str(unsigned int value, char* str)
{
    char temp[12]; // max 32 bit uint: 4294967295 + null terminator 
    int i = 0;
    int count = 0;

    //Special case for 0 
    if(value == 0)
        {
            str[0] = '0';
            str[1] = '\0';

            return 1;
        }
    
    // Convert digits to string backwards
    while (value > 0)
    {
        temp[i++] = (value%10) + '0';
        value = value/10;

    }
    
    while(i>0)
    {
        str[count++] = temp[--i];
    }

    str[count] = '\0';


    return count;
}



/*
 * int_to_str - Converts signed integer to string
 * ----------------------------------------------
 * Handles negative numbers and converts to ASCII decimal representation.
 * Returns the number of characters written to the string buffer.
 */
int int_to_str(int value, char* str)
{
    char temp[12] ; // should hold 32 bit
    int i = 0;
    int is_negative = 0; // flag to detect sign
    unsigned int uvalue;
    int count = 0; // keeps count of how many elements have been added to str

    // if 0 is entered
    if(value == 0)
    {
        str[0] = '0';
        str[1] = '\0';

        return 1;
    }

    //is_negative
    if(value < 0)
    {
        is_negative = 1; // we acknowledge it is negative
        //avoiding overflow:
        uvalue = (unsigned int)(-((long)value));
    }
    else
    {
        uvalue = (unsigned int) value;

    }


    // Convert digits to string backwards
    while (uvalue > 0)
    {
        temp[i++] = (uvalue%10) + '0';
        uvalue = uvalue/10;

    }
    // Add the - sign if negative
    if(is_negative)
    {
        temp[i++] = '-';
    }


    // Flip the string
    int j = 0;
    while (i > 0)
    {
        str[j++] = temp[--i];
        count++;
    }

    // seal it withe null byte
    str[j] = '\0';

    return count;
}
/*
 * double_to_str - Converts double to string with fixed precision
 * --------------------------------------------------------------
 * Converts a double to string with specified number of digits after decimal.
 * Returns the number of characters written to the buffer.
 *
 * NOTE: Not safe for kernel mode without FPU.
 */

int double_to_str(double value, char* str, int precision)
{
    int count = 0; // tracks num of chars written to str

    // Negative values
    if (value < 0)
    {
        str[count++] = '-';
        value = - value; // no worries of overflow like in int case
    }

    // Lets get the integer portion
    int int_part = (int)value;
    // Lets get fractional part
    double fractional = value - (double)int_part;

    //Converting int part
    ////str + count ensures that the result is appended to the existing content of str starting at the correct position (count)

    count = count + int_to_str(int_part,str+count);
    str[count++] = '.'; // add the decimal point

    //Conver the fractional part
    for (int i = 0; i < precision; i++)
    {
        // x10 to shift the 1st digit to integer place
        fractional = fractional * 10;
        int digit = (int)fractional; // extract that int
        str[count++] = digit + '0'; // convert to ASCII and store as string
        fractional = fractional - digit; // ditch digit: update fractional part
    }

    //add the null byte
    str[count] = '\0';





    return count;
}

/*
 * string_to_str - Copies one string to another
 * --------------------------------------------
 * Copies a null-terminated string to a destination buffer.
 * Returns the number of characters copied (excluding null terminator).
 */
int string_to_str(char* source, char* destination)
{
    int count = strlen2(source);

    strncpy2(destination,source,count);

    destination[count] = '\0';

    return count;
}
