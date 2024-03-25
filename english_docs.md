
# MIPS Emulator Documentation

## Overview
This document provides an overview and detailed documentation of the MIPS emulator implemented in C. The emulator simulates the MIPS (Microprocessor without Interlocked Pipeline Stages) architecture, commonly used in academic settings for teaching purposes.

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
