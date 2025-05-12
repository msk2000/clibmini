# clibmini

**clibmini** is a minimal, self-contained replacement for parts of the C standard library, intended for use in low-level environments such as operating system kernels, bare-metal development, embedded systems, or educational OS projects. I wrote this as part of my kernel/OS development project targeting ARM64 architecture on Raspberry Pi hardware. Below is tiny demo clip demonstrating the code working in my kernel/OS dev project:



https://github.com/user-attachments/assets/808b2666-833c-4c41-bff4-86233a10eadf



## Features

- Custom `print` function supporting:
  - `%d`, `%u`, `%f`, `%s`, `%c`, `%x`, and `%X` format specifiers
- Lightweight implementations of:
  - `strlen`
  - `strncpy`
  - Integer and unsigned integer to string conversion
  - Floating point to string conversion
  - String copying utilities

## Goals

- Provide a minimal set of core functionality without requiring a full C standard library
- Avoid heap allocation and system-specific dependencies
- Be easy to understand and modify for low-level development

## Example Usage

```c
print("Integer: %d, Hex: %x, Float: %f\n", -42, 255, 3.1415);
```

## File Overview

- **clibmini.h** — Header file declaring all functions  
- **clibmini.c** — Implementation of string utilities and formatted output  
- *(Optional)* **main.c** or test file — Can be used to test functionality in userspace

## Limitations

- `print` uses `printf` internally for debug output. This will need to be replaced with a platform-specific output function (e.g., serial or framebuffer) for use in kernel mode or bare-metal applications.
- Floating point support is basic and controlled via fixed precision.
- No support for advanced formatting (padding, width, alignment, etc.)

## Future Work

- Implement more standard library functions (`memcpy`, `strcmp`, etc.)

## License

This project is released under the GNU General Public License v3.0. See `LICENSE` for details.



**Note:** This project is designed for learning and experimentation. Contributions and suggestions are welcome!

