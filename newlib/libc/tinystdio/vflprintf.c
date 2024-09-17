/* Copyright © 2018 Keith Packard
   All rights reserved.

   Redistribution and use in source and binary forms, with or without
   modification, are permitted provided that the following conditions are met:

   * Redistributions of source code must retain the above copyright
     notice, this list of conditions and the following disclaimer.

   * Redistributions in binary form must reproduce the above copyright
     notice, this list of conditions and the following disclaimer in
     the documentation and/or other materials provided with the
     distribution.

   * Neither the name of the copyright holders nor the names of
     contributors may be used to endorse or promote products derived
     from this software without specific prior written permission.

  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
  ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
  LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
  CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
  SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
  INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
  CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
  ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
  POSSIBILITY OF SUCH DAMAGE.

*/

#include "stdio_private.h"

#define PICOLIBC_LONG_LONG_PRINTF_SCANF
#define PRINTF_LEVEL PRINTF_LLONG
#ifndef _FORMAT_DEFAULT_LONG_LONG
#define vfprintf __l_vfprintf
#endif

#include "vfprintf.c"

#ifdef _FORMAT_DEFAULT_LONG_LONG
#ifdef _HAVE_ALIAS_ATTRIBUTE
__strong_reference(vfprintf, __l_vfprintf);
#ifdef _WANT_FLOCKFILE
__strong_reference(FILE_FN_UNLOCKED(vfprintf), FILE_FN_UNLOCKED(__l_vfprintf));
#endif
#else
int __l_vfprintf (FILE * stream, const char *fmt, va_list ap) { return vfprintf(stream, fmt, ap); }
#ifdef _WANT_FLOCKFILE
int FILE_FN_UNLOCKED(__l_vfprintf) (FILE * stream, const char *fmt, va_list ap) { return FILE_FN_UNLOCKED(vfprintf)(stream, fmt, ap); }
#endif
#endif
#endif
