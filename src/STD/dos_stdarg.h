/**
 * @brief 8086 real mode, LARGE memory model (Open Watcom):
 * - Arguments pushed right-to-left on stack (SS segment)
 * - Stack addresses are near (16-bit offset); va_list tracks SS offset
 * - Far pointers occupy 4 bytes on stack: offset (low word), then segment (high word)
 * - Default promotions apply: char/short→int, float→double
 * - sizeof(type) correctly returns 2 for near ptr, 4 for far ptr/long, 8 for double
 */
#ifndef DOS_STDARG_H
#define DOS_STDARG_H

#ifdef USE_DOSLIBC

    /**
    * va_list is a NEAR pointer into the current stack frame (SS)
    */
    typedef unsigned char near* va_list;

    /**
    * va_arg: fetch value of 'type' from stack, advance ap
    * - sizeof(type) handles near(2)/far(4)/long(4)/double(8) correctly
    * - Comma operator ensures ap increments AFTER old value is used
    * - Cast to (type *) respects far/near qualifiers of the target type
    */
    #define va_arg(ap, type) (*(type *)((ap) += sizeof(type), (ap) - sizeof(type)))

    /**
    * va_start: similarly find the first value
    */
    #define va_start(ap, last) ((ap) = (va_list)&(last) + sizeof(last))

    /**
    * va_end: trivial void
    */
    #define va_end(ap) ((void)0)

#else

    #include <stdarg.h>

#endif //USE_DOSLIBC

#endif
