/* Copyright (c) 2002 Red Hat Incorporated.
   All rights reserved.
   Modified (m) 2017 Thomas Wolff to refer to generated Unicode data tables.

   Redistribution and use in source and binary forms, with or without
   modification, are permitted provided that the following conditions are met:

     Redistributions of source code must retain the above copyright
     notice, this list of conditions and the following disclaimer.

     Redistributions in binary form must reproduce the above copyright
     notice, this list of conditions and the following disclaimer in the
     documentation and/or other materials provided with the distribution.

     The name of Red Hat Incorporated may not be used to endorse
     or promote products derived from this software without specific
     prior written permission.

   THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
   AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
   IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
   ARE DISCLAIMED.  IN NO EVENT SHALL RED HAT INCORPORATED BE LIABLE FOR ANY
   DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
   (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
   LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
   ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
   (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS   
   SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

/*
FUNCTION
	<<towctrans>>, <<towctrans_l>>---extensible wide-character translation

INDEX
	towctrans

INDEX
	towctrans_l

SYNOPSIS
	#include <wctype.h>
	wint_t towctrans(wint_t <[c]>, wctrans_t <[w]>);

	#include <wctype.h>
	wint_t towctrans_l(wint_t <[c]>, wctrans_t <[w]>, locale_t <[locale]>);


DESCRIPTION
<<towctrans>> is a function which converts wide characters based on
a specified translation type <[w]>.  If the translation type is
invalid or cannot be applied to the current character, no change
to the character is made.

<<towctrans_l>> is like <<towctrans>> but performs the function based on the
locale specified by the locale object locale.  If <[locale]> is
LC_GLOBAL_LOCALE or not a valid locale object, the behaviour is undefined.

RETURNS
<<towctrans>>, <<towctrans_l>> return the translated equivalent of <[c]>
when it is a valid for the given translation, otherwise, it returns the
input character.  When the translation type is invalid, <<errno>> is
set to <<EINVAL>>.

PORTABILITY
<<towctrans>> is C99.
<<towctrans_l>> is POSIX-1.2008.

No supporting OS subroutines are required.
*/

#define _DEFAULT_SOURCE
#include <sys/cdefs.h>
#include <wctype.h>
//#include <errno.h>
#include "local.h"

#ifndef _REENT_ONLY
wint_t
towctrans (wint_t c,
	wctrans_t w)
{
  if (w == WCT_TOLOWER || w == WCT_TOUPPER)
    return towctrans_l (c, w, 0);
  else
    {
      // skipping this because it was causing trouble (cygwin crash)
      // and there is no errno specified for towctrans
      //__errno_r(r) = EINVAL;
      return c;
    }
}
#endif /* !_REENT_ONLY */
