# DOSLIBC
A &lt;3KB freestanding C library for 8086 DOS.

## Motivation: 
Memory footprint reduction compared to Watcom C Compiler libc for DOS programs - 70-80% smaller than Watcom libc.

Comparing the code size impact of using **DOSLIBC** versus the standard **Open Watcom `clibl.lib` + `math87l.lib`**.

| Module | Feature Set | Stock Watcom (Bytes) | DOSLIBC (Bytes) | Savings |
| :--- | :--- | :---: | :---: | :---: |
| **Core** | Assert, Errno, Stdlib, String | ~3,839 | **867** | **~77%** |
| **Stdio** | Integers + File I/O | ~5,800 | **1,465** | **~75%** |
| **Stdio** | **+ Floating Point** (`%f`, `%e`, `%E`) | ~9,200 | **1,827** | **~80%** |
| **TOTAL** | **Full Feature Set** | **~13,039** | **2,694** | **~79%** |
| **TOTAL** | **Integer/File Only** | **~9,639** | **2,332** | **~76%** |

## Replacements:

| Standard Watcom Header | DOSLIBC Equivalent |
| :--- | :--- |
| `<assert.h>` | `dos_assert.h` |
| `<errno.h>` | `dos_errno.h` |
| `<limits.h>` | `dos_limits.h` |
| `<stdarg.h>` | `dos_stdarg.h` |
| `<stdbool.h>` | `dos_stdbool.h` |
| `<stddef.h>` | `dos_stddef.h` |
| `<stdint.h>` | `dos_stdint.h` |
| `<stdio.h>` | `dos_stdio.h` |
| `<stdlib.h>` | `dos_stdlib.h` |
| `<string.h>` | `dos_string.h` |

## Configuration:
Control the binary size with three preprocessor defines. 

### 1. Enable the Library
```c
USE_DOSLIBC
```

### 2. Enable Floating Point Printf
```c
USE_DOSLIBC_FLOAT_PRINTF
```
Enables support for %f, %e, and %E in printf/fprintf.

Cost: +~360 bytes.

Default: Disabled (Integer-only printing).

### 3. Enable File I/O
```c
USE_DOSLIBC_FILE_IO
```
Enables fopen, fclose, fread, fwrite, and stream buffering.

Cost: +~865 bytes.

Default:

## Example:
(Look at the test harness files for more examples)
``` C
/**
* @note Define switches BEFORE including headers, or pass via compiler flags
*/
#ifdef USE_DOSLIBC
    #include "dos_stdio.h"
    #include "dos_stdlib.h"
    #include "dos_string.h"
#else
    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
#endif

int main(void) {
    printf("Hello from DOSLIBC!\n");
    
    #ifdef USE_DOSLIBC_FLOAT_PRINTF
    printf("Pi approx: %f\n", 3.14159);
    #endif
    
    return 0;
}
```
