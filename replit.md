# Auto Szerviz - Car Service Management System

## Overview
This is a C-based terminal application for managing a car service shop (auto repair shop). It's a BME-VIK university project (nagyházi).

## Purpose
The application allows users to:
- Add clients
- Add cars
- Add repairs
- Search by client name
- Search by car license plate
- Delete cars
- View car service history
- List cars with expiring inspections

## Project Architecture
- **Language**: C
- **Compiler**: GCC (via c-clang module)
- **Type**: Terminal-based console application
- **Build System**: Direct GCC compilation

### File Structure
- `main.c` - Main entry point with menu system
- `car.c/car.h` - Car management functionality
- `javitas.c/javitas.h` - Repair management functionality
- `ugyfel.c/ugyfel.h` - Client management functionality
- `structs.h` - Data structures
- `functions.c` - Utility functions
- `debugmalloc.h` - Memory debugging utilities

## Build & Run
The application is configured to automatically compile and run via the workflow:
```bash
gcc -o autoszerviz main.c car.c javitas.c ugyfel.c && ./autoszerviz
```

## Recent Changes
- November 15, 2025: Initial setup in Replit environment
  - Installed c-clang toolchain
  - Configured build workflow
  - Verified compilation and execution
