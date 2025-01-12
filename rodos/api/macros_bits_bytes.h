
#pragma once


/**
* @file Macros.h
* @date 2008/11/21 11:46
* @author Sergio Montenegro
*
* Copyright 2008 DLR
*
*/


/* WARNING:
 * THis file is not included in rodos.h or rodos-api.h
 * some drivers from chip provide has different meaning for SET_BIT and GET_BIT! (eg. a mask)
 * to avoid conflicts you shall include this file by your self.
 */

#ifndef NO_RODOS_NAMESPACE
namespace RODOS {
#endif

/** Bit Operations for CCSDS Formtas: Bit 0 = most significant!! **/

#define SET_BIT(_target, _position, _value)  { _target &= ~(1<<(7-(_position))); _target |= (((_value)&0x1)<<(7-(_position))); }

#define GET_BIT(_source, _position)  ( ((_source)  >> (7 - (_position))) & 0x1 )

#define STRING(a) (a? a : "--NUL--")

#define MAX(_a, _b) ( (_a) > (_b) ? (_a) : (_b) )
#define MIN(_a, _b) ( (_a) < (_b) ? (_a) : (_b) )

#define ABS(_a) ( (_a) >= 0 ? (_a) : -(_a) )

/// exchange values of char variables (a) and (b)
#define SWAPCHARS(_a, _b) {char _tempswap = _a;   _a = _b;   _b = _tempswap; }

/** Macro to create a short id from two chars use eg. CHARS2SHORT('a', 'b') **/
#define CHARS2SHORT(a,b) (((a)<<8) + (b))

#define ROTATE_RIGHT(c) { if ((c) & 01) (c) = ((c) >>1) | 0x8000; else (c) >>= 1; }

#define ONES(n) ((1 <<(n))-1) ///< creates a sequence of n 1 bits (max 31 bits)


#ifndef NO_RODOS_NAMESPACE
}
#endif

