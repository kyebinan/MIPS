# MIPS Emulator in C

![mips](https://github.com/kyebinan/MIPS/assets/155234248/37cbf0dc-79c5-4ded-88b7-cb0e6156feca)

## Overview

MIPS, which stands for Microprocessor without Interlocked Pipeline Stages, is a 32-bit Reduced Instruction Set Computer (RISC) microprocessor. As a RISC architecture, MIPS features a streamlined set of instructions, enabling the execution of most instructions in a single clock cycle. MIPS processors are widely used in workstations (e.g., Silicon Graphics, DEC), embedded systems (e.g., Palm devices, modems), consumer electronics (e.g., TVs, HiFi systems, gaming consoles like Nintendo 64 and Sony PlayStation 2), routers, and automotive applications.

This project is a MIPS emulator implemented in C. The emulator converts MIPS assembly instructions into hexadecimal format but does not currently use the hexadecimal instructions for execution. This functionality is under development as part of an ongoing refactoring effort.

### Background

This project was created during my engineering studies in France as part of a semester-end assignment to deepen my understanding of the C programming language and computer architecture. Developing this emulator has been an enjoyable and educational experience, as it combined my passion for programming in C with the challenge of understanding MIPS assembly language.

---

## Features

- Converts MIPS assembly instructions into hexadecimal.
- Supports basic R-type, I-type, and J-type MIPS instructions.
- Provides two execution modes:
  1. **Step-by-Step Execution**: Executes the program interactively, allowing the user to proceed through instructions manually.
  2. **Batch Execution**: Executes the entire program without user interaction.

---

## How to Run

### Prerequisites

- A C compiler (e.g., GCC).
- A terminal or command-line interface.
- The source code files included in this project.

### Compilation

Compile the program using a C compiler:
```bash
make all
```

### Execution Modes

The program supports two modes of execution, which are controlled by the third command-line argument:

1. **Step-by-Step Execution Mode**:
   - This mode allows interactive execution, where the user is prompted to proceed with the next instruction.
   - To run in this mode, use the `-p` flag:
     ```bash
     ./mips_emulator <source_file> <destination_file> -p
     ```
   - Example:
     ```bash
     ./mips_emulator program.asm output.hex -p
     ```

2. **Batch Execution Mode**:
   - Executes the program without user interaction.
   - To run in this mode, use the `-n` flag:
     ```bash
     ./mips_emulator <source_file> <destination_file> -n
     ```
   - Example:
     ```bash
     ./mips_emulator program.asm output.hex -n
     ```

---

## Current Limitations

- The emulator **converts MIPS assembly code to hexadecimal but does not use the hexadecimal instructions for execution**. This feature is planned for future development.
- Syntax handling in the current implementation is rigid. Any deviation from the expected syntax may result in errors.

---

## Future Improvements

I am actively working on refactoring the code to:

1. **Adopt proficient C programming practices**:
   - Enhance code readability and maintainability.
   - Optimize performance.

2. **Improve syntax resilience**:
   - Allow flexible assembly syntax.
   - Support additional features such as labels and tags in the assembly code.

3. **Align with the principles of an emulator**:
   - Implement execution directly from hexadecimal instructions.
   - Accurately mimic the behavior of a MIPS microprocessor.

---

## Acknowledgments

This project has been a stepping stone in my engineering journey and a testament to my passion for computer architecture and programming in C. I hope it serves as a foundation for exploring more advanced emulation techniques in the future.

---

Feel free to reach out for questions or suggestions to improve this emulator!







