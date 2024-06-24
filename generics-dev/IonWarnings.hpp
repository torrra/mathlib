/*

 _____                               _
|_   _|                             (_)
  | |  ___  _ __     ___ _ __   __ _ _ _ __   ___
  | | / _ \| '_ \   / _ \ '_ \ / _` | | '_ \ / _ \
 _| || (_) | | | | |  __/ | | | (_| | | | | |  __/
 \___/\___/|_| |_|  \___|_| |_|\__, |_|_| |_|\___|
                                __/ |
                               |___/


NAME: IonWarnings.hpp

DESCTIPTION: Macros to facilitate warning handling for both MSVC and GCC

AUTHOR: Noah de Pischof | @torrra on GitHub

STYLE:

ION_ prefix helps identify macros specicific to the project

()  empty parentheses are added after macros that reprsent an action, to
    differentiate them from macros that extend to simple values

*/


#ifndef __ION_WARNINGS_H__
#define __ION_WARNINGS_H__

// This macro helps dealing with quotation marks (# operator), as _Pragma
// expects a raw string, which may make the code unpleasant to read
#define ION_PRAGMA(_instruction)             _Pragma(#_instruction)

#ifdef _MSC_VER

// Microsoft-specific pragma warning directives

#define ION_PUSH_WARNINGS()                   ION_PRAGMA(warning(push))
#define ION_POP_WARNINGS()                    ION_PRAGMA(warning(pop))
#define ION_DISABLE_WARNING(_warning)         ION_PRAGMA(warning(disable: _warning))


// Only defined for MSVC.
// Unreachable code warning has been 
// removed from GCC as it was considered unreliable
#define ION_UNREACHABLE_CODE                    4702

#elif defined(__GNUC__)

// GCC pragma warning directives

#define ION_PUSH_WARNINGS()                   ION_PRAGMA(GCC diagnostic push)
#define ION_POP_WARNINGS()                    ION_PRAGMA(GCC diagnostic pop)
#define ION_DISABLE_WARNING(_warning)         ION_PRAGMA(GCC diagnostic ignored #_warning)


#else

// Compilers for which the source code was not designed nor tested.
// TODO: clang support ?
#error [ION ENGINE] Sorry, this compiler is not supported.

#endif

#endif