
# MIPS Emulator Documentation

## Overview
This document provides an overview and detailed documentation of the MIPS emulator implemented in C. The emulator simulates the MIPS (Microprocessor without Interlocked Pipeline Stages) architecture, commonly used in academic settings for educational purposes.

We have successfully coded all the necessary functions for our MIPS emulator and have tested them with our test files. Our emulator works well with these tests. However, it is necessary to be aware of certain important points regarding our syntax:

- **Management of Register Mnemonics**: We have implemented support for register mnemonics, allowing for the use of `$zero` instead of `$0`. (See the `checkRegisters` function in the `Utility` module).

- **Instructions Requiring an Offset or a Target**: For instructions that require an offset or a target, such as `JAL target`, `SW $2,offset($8)`, it is necessary for `offset` and `target` to be multiples of 4.

- **Robustness to Spaces in MIPS Instructions**: Our code is robust to spaces in MIPS instructions; therefore, `ADD    $4,$2   ,$5` is treated the same as `ADD $4,$2,$5`. (See the `checkRegisters` function in the `Utility` module).

- **Displaying Register States**: We have not stored the states of the registers in a text file; we display them in the console.

- **Handling White Characters**: We have accounted for white characters that we are able to identify and ignore, with the exception of one that poses a problem for us. We do not know it, but it causes deletions on the line where it is placed. We have conducted research and sought help from a teaching assistant, but we have not been able to manage this bug.

- **Displaying the Content of a Register in Hexadecimal**: We display the content of a register in hexadecimal and have adhered to the Big Endian convention of the MIPS processor.

## Modules Documentation

### `main.c`
- **Description**: Initializes the MIPS emulator, including memory and registry setups. Parses command-line arguments and launches the instruction execution process.
- **Key Functions**:
  - `main`: The main entry point. It may handle initialization procedures and loop through the instruction execution cycle.

### `Function.c` and `Function.h`
- **Description**: Implements core MIPS instruction functionalities, such as arithmetic operations, logic operations, and control flow changes.
- **Key Functions**:
  - `executeInstruction`: Executes a given MIPS instruction.
  - `arithmeticOp`: Performs arithmetic operations based on opcode.
  - `logicOp`: Handles logical operations.

### `HexaConverte.c` and `HexaConverte.h`
- **Description**: Facilitates conversion between hexadecimal strings and numerical values, essential for memory address and data manipulation.
- **Key Functions**:
  - `hexToString`: Converts a hexadecimal value to a string representation.
  - `stringToHex`: Converts a string representation of a hexadecimal number into its numerical value.

### `MemoryManagement.c` and `MemoryManagement.h`
- **Description**: Manages the simulated memory of the MIPS environment, including allocation, access, and deallocation.
- **Key Functions**:
  - `allocateMemory`: Allocates memory for the MIPS simulation.
  - `freeMemory`: Frees allocated memory.
  - `readMemory`: Reads a value from a specified memory address.
  - `writeMemory`: Writes a value to a specified memory address.

### `RegistryManagement.c` and `RegistryManagement.h`
- **Description**: Manages the MIPS registers, including reading and writing operations to general and special-purpose registers.
- **Key Functions**:
  - `readRegister`: Reads a value from a specified register.
  - `writeRegister`: Writes a value to a specified register.

### `Utility.c` and `Utility.h`
- **Description**: Provides miscellaneous utility functions that support the emulator's operation.
- **Key Functions**:
  - `logError`: Logs an error message to the console or a file.
  - `bitwiseOperations`: Performs bitwise operations required by MIPS instructions.
