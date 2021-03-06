/* ---------------------------------------------------------------------------- */
/*                  Atmel Microcontroller Software Support                      */
/*                       SAM Software Package License                           */
/* ---------------------------------------------------------------------------- */
/* Copyright (c) 2015, Atmel Corporation                                        */
/*                                                                              */
/* All rights reserved.                                                         */
/*                                                                              */
/* Redistribution and use in source and binary forms, with or without           */
/* modification, are permitted provided that the following condition is met:    */
/*                                                                              */
/* - Redistributions of source code must retain the above copyright notice,     */
/* this list of conditions and the disclaimer below.                            */
/*                                                                              */
/* Atmel's name may not be used to endorse or promote products derived from     */
/* this software without specific prior written permission.                     */
/*                                                                              */
/* DISCLAIMER:  THIS SOFTWARE IS PROVIDED BY ATMEL "AS IS" AND ANY EXPRESS OR   */
/* IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF */
/* MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT ARE   */
/* DISCLAIMED. IN NO EVENT SHALL ATMEL BE LIABLE FOR ANY DIRECT, INDIRECT,      */
/* INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT */
/* LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA,  */
/* OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF    */
/* LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING         */
/* NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, */
/* EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.                           */
/* ---------------------------------------------------------------------------- */

#ifndef _COMPILER_H_
#define _COMPILER_H_

//#include "include/same70/same70.h"
/*
 * Peripherals registers definitions
 */
/*
#if defined(__SAMV71Q21__)
	#include "include/samv71/samv71.h"
#elif defined(__SAME70Q21__)
	#include "include/same70/same70.h"
#else
	#error "please define correct macro for the chip first!"
#endif
*/

//_____ D E C L A R A T I O N S ____________________________________________

#ifndef __ASSEMBLY__

#include <stddef.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include "sam.h"

/* Define WEAK attribute */
#if defined   (__CC_ARM)
	#define WEAK __attribute__ ((weak))
#elif defined (__ICCARM__)
	#define WEAK __weak
#elif defined (__GNUC__)
	#define WEAK __attribute__ ((weak))
#endif

/* Define Compiler name of tool chains */
#if defined   (__CC_ARM)
	#define COMPILER_NAME               "KEIL"
#elif defined (__ICCARM__)
	#define COMPILER_NAME               "IAR"
#elif defined (__GNUC__)
	#define COMPILER_NAME               "GCC"
#endif

/* Define NO_INIT attribute */
#if defined   (__CC_ARM)
	#define NO_INIT
#elif defined (__ICCARM__)
	#define NO_INIT __no_init
#elif defined (__GNUC__)
	#define NO_INIT
#endif


/* Define memory sync for tool chains */
#if defined   (__CC_ARM)
	#define memory_sync()        __dsb(15);__isb(15);
#elif defined (__ICCARM__)
	#define memory_sync()        __DSB();__ISB();
#elif defined (__GNUC__)
	#define memory_sync()        __DSB();__ISB();
#endif

/* Define memory barrier for tool chains */
#if defined   (__CC_ARM)
	#define memory_barrier()        __dmb(15);
#elif defined (__ICCARM__)
	#define memory_barrier()        __DMB();
#elif defined (__GNUC__)
	#define memory_barrier()        __DMB();
#endif

#if defined(__CC_ARM)
#   define __always_inline   __forceinline
#elif (defined __GNUC__)
#ifdef __always_inline
#	undef __always_inline
#endif
#	define __always_inline   inline __attribute__((__always_inline__))
#elif (defined __ICCARM__)
#	define __always_inline   _Pragma("inline=forced")
#endif

#if defined(_ASSERT_ENABLE_)
#  if defined(TEST_SUITE_DEFINE_ASSERT_MACRO)
// Assert() is defined in unit_test/suite.h
#    include "unit_test/suite.h"
#  else
#undef TEST_SUITE_DEFINE_ASSERT_MACRO
#    define Assert(expr) \
{\
	if (!(expr)) while (true);\
}
#  endif
#else
#  define Assert(expr) ((void) 0)
#endif

/*! \name Token Paste
 *
 * Paste N preprocessing tokens together, these tokens being allowed to be \#defined.
 *
 * May be used only within macros with the tokens passed as arguments if the tokens are \#defined.
 *
 * For example, writing TPASTE2(U, WIDTH) within a macro \#defined by
 * UTYPE(WIDTH) and invoked as UTYPE(UL_WIDTH) with UL_WIDTH \#defined as 32 is
 * equivalent to writing U32.
 */
//! @{
//#define TPASTE2(a, b)                            a##b
//#define TPASTE3(a, b, c)                         a##b##c
//! @}

#define Swap16(u16) ((U16)(((U16)(u16) >> 8) |\
((U16)(u16) << 8)))

#define Swap32(u32) ((U32)(((U32)Swap16((U32)(u32) >> 16)) |\
((U32)Swap16((U32)(u32)) << 16)))

#define Swap64(u64) ((U64)(((U64)Swap32((U64)(u64) >> 32)) |\
((U64)Swap32((U64)(u64)) << 32)))

#define swap16(u16) Swap16(u16)

#if (defined __GNUC__)
#   define swap32(u32) ((U32)__builtin_bswap32((U32)(u32)))
#else
#   define swap32(u32) Swap32(u32)
#endif

#if (defined __GNUC__)
#   define swap64(u64) ((U64)__builtin_bswap64((U64)(u64)))
#else
#   define swap64(u64) ((U64)(((U64)swap32((U64)(u64) >> 32)) |\
((U64)swap32((U64)(u64)) << 32)))
#endif



/*! \name MCU Endianism Handling
 * ARM is MCU little endianism.
 */
//! @{
#define  MSB(u16)       (((U8  *)&(u16))[1]) //!< Most significant byte of \a u16.
#define  LSB(u16)       (((U8  *)&(u16))[0]) //!< Least significant byte of \a u16.

#define  MSH(u32)       (((U16 *)&(u32))[1]) //!< Most significant half-word of \a u32.
#define  LSH(u32)       (((U16 *)&(u32))[0]) //!< Least significant half-word of \a u32.
#define  MSB0W(u32)     (((U8  *)&(u32))[3]) //!< Most significant byte of 1st rank of \a u32.
#define  MSB1W(u32)     (((U8  *)&(u32))[2]) //!< Most significant byte of 2nd rank of \a u32.
#define  MSB2W(u32)     (((U8  *)&(u32))[1]) //!< Most significant byte of 3rd rank of \a u32.
#define  MSB3W(u32)     (((U8  *)&(u32))[0]) //!< Most significant byte of 4th rank of \a u32.
#define  LSB3W(u32)     MSB0W(u32)           //!< Least significant byte of 4th rank of \a u32.
#define  LSB2W(u32)     MSB1W(u32)           //!< Least significant byte of 3rd rank of \a u32.
#define  LSB1W(u32)     MSB2W(u32)           //!< Least significant byte of 2nd rank of \a u32.
#define  LSB0W(u32)     MSB3W(u32)           //!< Least significant byte of 1st rank of \a u32.
        
#define  MSW(u64)       (((U32 *)&(u64))[1]) //!< Most significant word of \a u64.
#define  LSW(u64)       (((U32 *)&(u64))[0]) //!< Least significant word of \a u64.
#define  MSH0(u64)      (((U16 *)&(u64))[3]) //!< Most significant half-word of 1st rank of \a u64.
#define  MSH1(u64)      (((U16 *)&(u64))[2]) //!< Most significant half-word of 2nd rank of \a u64.
#define  MSH2(u64)      (((U16 *)&(u64))[1]) //!< Most significant half-word of 3rd rank of \a u64.
#define  MSH3(u64)      (((U16 *)&(u64))[0]) //!< Most significant half-word of 4th rank of \a u64.
#define  LSH3(u64)      MSH0(u64)            //!< Least significant half-word of 4th rank of \a u64.
#define  LSH2(u64)      MSH1(u64)            //!< Least significant half-word of 3rd rank of \a u64.
#define  LSH1(u64)      MSH2(u64)            //!< Least significant half-word of 2nd rank of \a u64.
#define  LSH0(u64)      MSH3(u64)            //!< Least significant half-word of 1st rank of \a u64.
#define  MSB0D(u64)     (((U8  *)&(u64))[7]) //!< Most significant byte of 1st rank of \a u64.
#define  MSB1D(u64)     (((U8  *)&(u64))[6]) //!< Most significant byte of 2nd rank of \a u64.
#define  MSB2D(u64)     (((U8  *)&(u64))[5]) //!< Most significant byte of 3rd rank of \a u64.
#define  MSB3D(u64)     (((U8  *)&(u64))[4]) //!< Most significant byte of 4th rank of \a u64.
#define  MSB4D(u64)     (((U8  *)&(u64))[3]) //!< Most significant byte of 5th rank of \a u64.
#define  MSB5D(u64)     (((U8  *)&(u64))[2]) //!< Most significant byte of 6th rank of \a u64.
#define  MSB6D(u64)     (((U8  *)&(u64))[1]) //!< Most significant byte of 7th rank of \a u64.
#define  MSB7D(u64)     (((U8  *)&(u64))[0]) //!< Most significant byte of 8th rank of \a u64.
#define  LSB7D(u64)     MSB0D(u64)           //!< Least significant byte of 8th rank of \a u64.
#define  LSB6D(u64)     MSB1D(u64)           //!< Least significant byte of 7th rank of \a u64.
#define  LSB5D(u64)     MSB2D(u64)           //!< Least significant byte of 6th rank of \a u64.
#define  LSB4D(u64)     MSB3D(u64)           //!< Least significant byte of 5th rank of \a u64.
#define  LSB3D(u64)     MSB4D(u64)           //!< Least significant byte of 4th rank of \a u64.
#define  LSB2D(u64)     MSB5D(u64)           //!< Least significant byte of 3rd rank of \a u64.
#define  LSB1D(u64)     MSB6D(u64)           //!< Least significant byte of 2nd rank of \a u64.
#define  LSB0D(u64)     MSB7D(u64)           //!< Least significant byte of 1st rank of \a u64.

#define  BE16(x)        swap16(x)
#define  LE16(x)        (x)

#define  le16_to_cpu(x) (x)
#define  cpu_to_le16(x) (x)
#define  LE16_TO_CPU(x) (x)
#define  CPU_TO_LE16(x) (x)

#define  be16_to_cpu(x) swap16(x)
#define  cpu_to_be16(x) swap16(x)
#define  BE16_TO_CPU(x) swap16(x)
#define  CPU_TO_BE16(x) swap16(x)

#define  le32_to_cpu(x) (x)
#define  cpu_to_le32(x) (x)
#define  LE32_TO_CPU(x) (x)
#define  CPU_TO_LE32(x) (x)

#define  be32_to_cpu(x) swap32(x)
#define  cpu_to_be32(x) swap32(x)
#define  CPU_TO_BE32(x) swap32(x)
#define  BE32_TO_CPU(x) swap32(x)

#define LSB0(u32)           LSB0W(u32)  //!< Least significant byte of 1st rank of \a u32.
#define LSB1(u32)           LSB1W(u32)  //!< Least significant byte of 2nd rank of \a u32.
#define LSB2(u32)           LSB2W(u32)  //!< Least significant byte of 3rd rank of \a u32.
#define LSB3(u32)           LSB3W(u32)  //!< Least significant byte of 4th rank of \a u32.
#define MSB3(u32)           MSB3W(u32)  //!< Most significant byte of 4th rank of \a u32.
#define MSB2(u32)           MSB2W(u32)  //!< Most significant byte of 3rd rank of \a u32.
#define MSB1(u32)           MSB1W(u32)  //!< Most significant byte of 2nd rank of \a u32.
#define MSB0(u32)           MSB0W(u32)  //!< Most significant byte of 1st rank of \a u32.


#if (defined __GNUC__) || (defined __CC_ARM)
#   define clz(u)              ((u) ? __builtin_clz(u) : 32)
#elif (defined __ICCARM__)
#   define clz(u)              ((u) ? __CLZ(u) : 32)
#else
#   define clz(u)              (((u) == 0)          ? 32 : \
((u) & (1ul << 31)) ?  0 : \
((u) & (1ul << 30)) ?  1 : \
((u) & (1ul << 29)) ?  2 : \
((u) & (1ul << 28)) ?  3 : \
((u) & (1ul << 27)) ?  4 : \
((u) & (1ul << 26)) ?  5 : \
((u) & (1ul << 25)) ?  6 : \
((u) & (1ul << 24)) ?  7 : \
((u) & (1ul << 23)) ?  8 : \
((u) & (1ul << 22)) ?  9 : \
((u) & (1ul << 21)) ? 10 : \
((u) & (1ul << 20)) ? 11 : \
((u) & (1ul << 19)) ? 12 : \
((u) & (1ul << 18)) ? 13 : \
((u) & (1ul << 17)) ? 14 : \
((u) & (1ul << 16)) ? 15 : \
((u) & (1ul << 15)) ? 16 : \
((u) & (1ul << 14)) ? 17 : \
((u) & (1ul << 13)) ? 18 : \
((u) & (1ul << 12)) ? 19 : \
((u) & (1ul << 11)) ? 20 : \
((u) & (1ul << 10)) ? 21 : \
((u) & (1ul <<  9)) ? 22 : \
((u) & (1ul <<  8)) ? 23 : \
((u) & (1ul <<  7)) ? 24 : \
((u) & (1ul <<  6)) ? 25 : \
((u) & (1ul <<  5)) ? 26 : \
((u) & (1ul <<  4)) ? 27 : \
((u) & (1ul <<  3)) ? 28 : \
((u) & (1ul <<  2)) ? 29 : \
((u) & (1ul <<  1)) ? 30 : \
31)
#endif

//! @}

/*! \brief Reads the bits of a value specified by a given bit-mask.
 *
 * \param value Value to read bits from.
 * \param mask  Bit-mask indicating bits to read.
 *
 * \return Read bits.
 */
#define Rd_bits( value, mask)        ((value) & (mask))

/*! \brief Writes the bits of a C lvalue specified by a given bit-mask.
 *
 * \param lvalue  C lvalue to write bits to.
 * \param mask    Bit-mask indicating bits to write.
 * \param bits    Bits to write.
 *
 * \return Resulting value with written bits.
 */
#define Wr_bits(lvalue, mask, bits)  ((lvalue) = ((lvalue) & ~(mask)) |\
                                                 ((bits  ) &  (mask)))

/*! \brief Tests the bits of a value specified by a given bit-mask.
 *
 * \param value Value of which to test bits.
 * \param mask  Bit-mask indicating bits to test.
 *
 * \return \c 1 if at least one of the tested bits is set, else \c 0.
 */
#define Tst_bits( value, mask)  (Rd_bits(value, mask) != 0)

/*! \brief Clears the bits of a C lvalue specified by a given bit-mask.
 *
 * \param lvalue  C lvalue of which to clear bits.
 * \param mask    Bit-mask indicating bits to clear.
 *
 * \return Resulting value with cleared bits.
 */
#define Clr_bits(lvalue, mask)  ((lvalue) &= ~(mask))

/*! \brief Sets the bits of a C lvalue specified by a given bit-mask.
 *
 * \param lvalue  C lvalue of which to set bits.
 * \param mask    Bit-mask indicating bits to set.
 *
 * \return Resulting value with set bits.
 */
#define Set_bits(lvalue, mask)  ((lvalue) |=  (mask))

/*! \brief Toggles the bits of a C lvalue specified by a given bit-mask.
 *
 * \param lvalue  C lvalue of which to toggle bits.
 * \param mask    Bit-mask indicating bits to toggle.
 *
 * \return Resulting value with toggled bits.
 */
#define Tgl_bits(lvalue, mask)  ((lvalue) ^=  (mask))

/*! \brief Reads the bit-field of a value specified by a given bit-mask.
 *
 * \param value Value to read a bit-field from.
 * \param mask  Bit-mask indicating the bit-field to read.
 *
 * \return Read bit-field.
 */
#define Rd_bitfield( value, mask)           (Rd_bits( value, mask) >> ctz(mask))

/*! \brief Writes the bit-field of a C lvalue specified by a given bit-mask.
 *
 * \param lvalue    C lvalue to write a bit-field to.
 * \param mask      Bit-mask indicating the bit-field to write.
 * \param bitfield  Bit-field to write.
 *
 * \return Resulting value with written bit-field.
 */
#define Wr_bitfield(lvalue, mask, bitfield) (Wr_bits(lvalue, mask, (U32)(bitfield) << ctz(mask)))

//! @}

typedef int8_t                  S8 ;  //!< 8-bit signed integer.
typedef uint8_t                 U8 ;  //!< 8-bit unsigned integer.
typedef int16_t                 S16;  //!< 16-bit signed integer.
typedef uint16_t                U16;  //!< 16-bit unsigned integer.
typedef uint16_t                le16_t;
typedef uint16_t                be16_t;
typedef int32_t                 S32;  //!< 32-bit signed integer.
typedef uint32_t                U32;  //!< 32-bit unsigned integer.
typedef uint32_t                le32_t;
typedef uint32_t                be32_t;
typedef int64_t                 S64;  //!< 64-bit signed integer.
typedef uint64_t                U64;  //!< 64-bit unsigned integer.
typedef float                   F32;  //!< 32-bit floating-point number.
typedef double                  F64;  //!< 64-bit floating-point number.
typedef uint32_t                iram_size_t;
/*! \name Absolute Token Paste
 *
 * Paste N preprocessing tokens together, these tokens being allowed to be \#defined.
 *
 * No restriction of use if the tokens are \#defined.
 *
 * For example, writing ATPASTE2(U, UL_WIDTH) anywhere with UL_WIDTH \#defined
 * as 32 is equivalent to writing U32.
 */
//! @{
//#define ATPASTE2(a, b)                           TPASTE2(a, b)
//#define ATPASTE3(a, b, c)                        TPASTE3(a, b, c)

#define TPASTE2( a, b)                            a##b
#define TPASTE3( a, b, c)                         a##b##c
#define TPASTE4( a, b, c, d)                      a##b##c##d
#define TPASTE5( a, b, c, d, e)                   a##b##c##d##e
#define TPASTE6( a, b, c, d, e, f)                a##b##c##d##e##f
#define TPASTE7( a, b, c, d, e, f, g)             a##b##c##d##e##f##g
#define TPASTE8( a, b, c, d, e, f, g, h)          a##b##c##d##e##f##g##h
#define TPASTE9( a, b, c, d, e, f, g, h, i)       a##b##c##d##e##f##g##h##i
#define TPASTE10(a, b, c, d, e, f, g, h, i, j)    a##b##c##d##e##f##g##h##i##j

#define ATPASTE2( a, b)                           TPASTE2( a, b)
#define ATPASTE3( a, b, c)                        TPASTE3( a, b, c)
#define ATPASTE4( a, b, c, d)                     TPASTE4( a, b, c, d)
#define ATPASTE5( a, b, c, d, e)                  TPASTE5( a, b, c, d, e)
#define ATPASTE6( a, b, c, d, e, f)               TPASTE6( a, b, c, d, e, f)
#define ATPASTE7( a, b, c, d, e, f, g)            TPASTE7( a, b, c, d, e, f, g)
#define ATPASTE8( a, b, c, d, e, f, g, h)         TPASTE8( a, b, c, d, e, f, g, h)
#define ATPASTE9( a, b, c, d, e, f, g, h, i)      TPASTE9( a, b, c, d, e, f, g, h, i)
#define ATPASTE10(a, b, c, d, e, f, g, h, i, j)   TPASTE10(a, b, c, d, e, f, g, h, i, j)

#define STRINGZ(x)                                #x
#define ASTRINGZ(x)                               STRINGZ(x)

/**
 * \brief Emit the compiler pragma \a arg.
 *
 * \param arg The pragma directive as it would appear after \e \#pragma
 * (i.e. not stringified).
 */
#define COMPILER_PRAGMA(arg)            _Pragma(#arg)

/**
 * \def COMPILER_PACK_SET(alignment)
 * \brief Set maximum alignment for subsequent structure and union
 * definitions to \a alignment.
 */
#define COMPILER_PACK_SET(alignment)   COMPILER_PRAGMA(pack(alignment))

/**
 * \def COMPILER_PACK_RESET()
 * \brief Set default alignment for subsequent structure and union
 * definitions.
 */
#define COMPILER_PACK_RESET()          COMPILER_PRAGMA(pack())

/**
 * \brief Set user-defined section.
 * Place a data object or a function in a user-defined section.
 */
#if defined   (__CC_ARM)
	#define COMPILER_SECTION(a)    __attribute__((__section__(a)))
#elif defined (__ICCARM__)
	#define COMPILER_SECTION(a)    COMPILER_PRAGMA(location = a)
#elif defined (__GNUC__)
	#define COMPILER_SECTION(a)    __attribute__((__section__(a)))
#endif

/**
 * \brief Set aligned boundary.
 */
#if defined   (__CC_ARM)
	#define COMPILER_ALIGNED(a)    __attribute__((__aligned__(a)))
#elif defined (__ICCARM__)
	#define COMPILER_ALIGNED(a)    COMPILER_PRAGMA(data_alignment = a)
#elif defined (__GNUC__)
	#define COMPILER_ALIGNED(a)    __attribute__((__aligned__(a)))
#endif

/**
 * \brief Set word-aligned boundary.
 */

#if defined   (__CC_ARM)
	#define COMPILER_WORD_ALIGNED    __attribute__((__aligned__(4)))
#elif defined (__ICCARM__)
	#define COMPILER_WORD_ALIGNED    COMPILER_PRAGMA(data_alignment = 4)
#elif defined (__GNUC__)
	#define COMPILER_WORD_ALIGNED    __attribute__((__aligned__(4)))
#endif



/*! \name Mathematics
 *
 * The same considerations as for clz and ctz apply here but GCC does not
 * provide built-in functions to access the assembly instructions abs, min and
 * max and it does not produce them by itself in most cases, so two sets of
 * macros are defined here:
 *   - Abs, Min and Max to apply to constant expressions (values known at
 *     compile time);
 *   - abs, min and max to apply to non-constant expressions (values unknown at
 *     compile time), abs is found in stdlib.h.
 */
//! @{

/*! \brief Takes the absolute value of \a a.
 *
 * \param a Input value.
 *
 * \return Absolute value of \a a.
 *
 * \note More optimized if only used with values known at compile time.
 */
#define Abs(a)              (((a) <  0) ? -(a) : (a))

/*! \brief Takes the minimal value of \a a and \a b.
 *
 * \param a Input value.
 * \param b Input value.
 *
 * \return Minimal value of \a a and \a b.
 *
 * \note More optimized if only used with values known at compile time.
 */
#define Min(a, b)           (((a) < (b)) ?  (a) : (b))

/*! \brief Takes the maximal value of \a a and \a b.
 *
 * \param a Input value.
 * \param b Input value.
 *
 * \return Maximal value of \a a and \a b.
 *
 * \note More optimized if only used with values known at compile time.
 */
#define Max(a, b)           (((a) > (b)) ?  (a) : (b))

// abs() is already defined by stdlib.h

/*! \brief Takes the minimal value of \a a and \a b.
 *
 * \param a Input value.
 * \param b Input value.
 *
 * \return Minimal value of \a a and \a b.
 *
 * \note More optimized if only used with values unknown at compile time.
 */
#define min(a, b)   Min(a, b)

/*! \brief Takes the maximal value of \a a and \a b.
 *
 * \param a Input value.
 * \param b Input value.
 *
 * \return Maximal value of \a a and \a b.
 *
 * \note More optimized if only used with values unknown at compile time.
 */
#define max(a, b)   Max(a, b)

//! @}

//#define  be32_to_cpu(x) __REV(x)
//#define  cpu_to_be32(x) __REV(x)
//#define  BE32_TO_CPU(x) __REV(x)
//#define  CPU_TO_BE32(x) __REV(x)

/**
 * \def UNUSED
 * \brief Marking \a v as a unused parameter or value.
 */
#define UNUSED(v)          (void)(v)

/**
 * \weakgroup interrupt_group
 *
 * @{
 */

/**
 * \name Interrupt Service Routine definition
 *
 * @{
 */

/**
 * \brief Initialize interrupt vectors
 *
 * For NVIC the interrupt vectors are put in vector table. So nothing
 * to do to initialize them, except defined the vector function with
 * right name.
 *
 * This must be called prior to \ref irq_register_handler.
 */
/*
#  define irq_initialize_vectors()   \
	do {                             \
	} while (0)
*/
/**
 * \brief Register handler for interrupt
 *
 * For NVIC the interrupt vectors are put in vector table. So nothing
 * to do to register them, except defined the vector function with
 * right name.
 *
 * Usage:
 * \code
    irq_initialize_vectors();
    irq_register_handler(foo_irq_handler);
\endcode
 *
 * \note The function \a func must be defined with the \ref ISR macro.
 * \note The functions prototypes can be found in the device exception header
 *       files (exceptions.h).
 */
/*
#  define irq_register_handler(int_num, int_prio)                      \
	NVIC_ClearPendingIRQ((IRQn_Type)int_num);                      \
	NVIC_SetPriority((IRQn_Type)int_num, int_prio);                \
	NVIC_EnableIRQ((IRQn_Type)int_num);                          \
*/
	//@}

/*
#  define cpu_irq_enable()                     \
	do {                                       \
		//g_interrupt_enabled = true;            \
		__DMB();                               \
		__enable_irq();                        \
	} while (0)
*/
/*		
#  define cpu_irq_disable()                    \
	do {                                       \
		__disable_irq();                       \
		__DMB();                               \
		//g_interrupt_enabled = false;          \
	} while (0)
*/
//	typedef uint32_t irqflags_t;

#if !defined(__DOXYGEN__)
	extern volatile bool g_interrupt_enabled;
#endif

#define cpu_irq_is_enabled()    (__get_PRIMASK() == 0)

	static volatile uint32_t cpu_irq_critical_section_counter;
	static volatile bool     cpu_irq_prev_interrupt_state;
/*
	static inline irqflags_t cpu_irq_save(void)
	{
		irqflags_t flags = cpu_irq_is_enabled();
		cpu_irq_disable();
		return flags;
	}
*/
/*
	static inline bool cpu_irq_is_enabled_flags(irqflags_t flags)
	{
		return (flags);
	}
*/
/*
	static inline void cpu_irq_restore(irqflags_t flags)
	{
		if (cpu_irq_is_enabled_flags(flags))
			cpu_irq_enable();
	}
*/
	/*
	void cpu_irq_enter_critical(void);
	void cpu_irq_leave_critical(void);*/

	/**
	 * \weakgroup interrupt_deprecated_group
	 * @{
	 */

#define Enable_global_interrupt()            cpu_irq_enable()
#define Disable_global_interrupt()           cpu_irq_disable()
#define Is_global_interrupt_enabled()        cpu_irq_is_enabled()


	//_____ M A C R O S ________________________________________________________

	/*! \name Usual Constants
	 */
	//! @{
#define DISABLE   0
#define ENABLE    1
#define DISABLED  0
#define ENABLED   1
#define OFF       0
#define ON        1
#define FALSE     0
#define TRUE      1
#ifndef __cplusplus
	#if !defined(__bool_true_false_are_defined)
		#define false     FALSE
		#define true      TRUE
	#endif
#endif
#define KO        0
#define OK        1
#define PASS      0
#define FAIL      1
#define LOW       0
#define HIGH      1
#define CLR       0
#define SET       1
	//! @}

	/*! \brief Counts the trailing zero bits of the given value considered as a 32-bit integer.
	 *
	 * \param u Value of which to count the trailing zero bits.
	 *
	 * \return The count of trailing zero bits in \a u.
	 */
#define ctz(u)              ((u) & (1ul <<  0) ?  0 : \
							 (u) & (1ul <<  1) ?  1 : \
							 (u) & (1ul <<  2) ?  2 : \
							 (u) & (1ul <<  3) ?  3 : \
							 (u) & (1ul <<  4) ?  4 : \
							 (u) & (1ul <<  5) ?  5 : \
							 (u) & (1ul <<  6) ?  6 : \
							 (u) & (1ul <<  7) ?  7 : \
							 (u) & (1ul <<  8) ?  8 : \
							 (u) & (1ul <<  9) ?  9 : \
							 (u) & (1ul << 10) ? 10 : \
							 (u) & (1ul << 11) ? 11 : \
							 (u) & (1ul << 12) ? 12 : \
							 (u) & (1ul << 13) ? 13 : \
							 (u) & (1ul << 14) ? 14 : \
							 (u) & (1ul << 15) ? 15 : \
							 (u) & (1ul << 16) ? 16 : \
							 (u) & (1ul << 17) ? 17 : \
							 (u) & (1ul << 18) ? 18 : \
							 (u) & (1ul << 19) ? 19 : \
							 (u) & (1ul << 20) ? 20 : \
							 (u) & (1ul << 21) ? 21 : \
							 (u) & (1ul << 22) ? 22 : \
							 (u) & (1ul << 23) ? 23 : \
							 (u) & (1ul << 24) ? 24 : \
							 (u) & (1ul << 25) ? 25 : \
							 (u) & (1ul << 26) ? 26 : \
							 (u) & (1ul << 27) ? 27 : \
							 (u) & (1ul << 28) ? 28 : \
							 (u) & (1ul << 29) ? 29 : \
							 (u) & (1ul << 30) ? 30 : \
							 (u) & (1ul << 31) ? 31 : \
							 32)

#endif // __ASSEMBLY__

#endif  // _COMPILER_H_
