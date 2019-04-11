#ifndef __LIB_DEBUG_H
#define __LIB_DEBUG_H
#include <stdio.h>

/* GCC lets us add "attributes" to functions, function
   parameters, etc. to indicate their properties.
   See the GCC manual for details. */
/* Halts the OS, printing the source file name, line number, and
   function name, plus a user-specific message. */
#define PANIC(line, argument) printf(line, argument)

#endif



/* This is outside the header guard so that debug.h may be
   included multiple times with different settings of NDEBUG. */
#undef ASSERT

#ifndef NDEBUG
#define ASSERT(CONDITION)                                       \
        if (CONDITION) { } else {                               \
                PANIC ("assertion `%s' failed.", #CONDITION);   \
        }
#else
#define ASSERT(CONDITION) ((void) 0)
#endif /* lib/debug.h */
