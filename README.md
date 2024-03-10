# RISC-V Assembler

The project contains a program that assembles a **RISC-V code to machine code**. It is a part of the CS204 - Computer Architecture course being taught under Prof. T.V. Kalyan and Prof. Neeraj Goyal at IIT Ropar. The language used in the program is **C++ version 20**

## Authors

-  Sagar Singh (2022CSB1115)
-  Pratishtha Pandey (2022CSB1105)
-  Saaransh Sharma (2022CSB1114)

## Usage Instructions

- Input is taken from "example.asm" file only.
- Output is obtained in "output.mc" file only.
- The code must be basic RISC-V code.
- The program does not support all pseudocodes but supports the use of labels in .text segment.
- comments are not allowed in the risc v code
- **Immediate** values must only be given in **Decimal format** and no other format like hexadecimal.

## Compiling and running the program

The program can be run by using the following commands.

For Compiling the program, use the following command in the terminal in the folder where the files are stored.

```bash
g++ assembler.cpp
```

To run the program, run the following command.

```bash
<!-- for Linux/Mac -->
./a.out

<!-- For windows -->
./a.exe
```
