/*
Copyright (c) 1994 Cygnus Support.
All rights reserved.

Redistribution and use in source and binary forms are permitted
provided that the above copyright notice and this paragraph are
duplicated in all such forms and that any documentation,
and/or other materials related to such
distribution and use acknowledge that the software was developed
at Cygnus Support, Inc.  Cygnus Support, Inc. may not be used to
endorse or promote products derived from this software without
specific prior written permission.
THIS SOFTWARE IS PROVIDED ``AS IS'' AND WITHOUT ANY EXPRESS OR
IMPLIED WARRANTIES, INCLUDING, WITHOUT LIMITATION, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
 */
/*
 * localtime.c
 */

/*
FUNCTION
<<localtime>>---convert time to local representation

INDEX
	localtime
INDEX
	localtime_r

SYNOPSIS
	#include <time.h>
	struct tm *localtime(time_t *<[clock]>);
	struct tm *localtime_r(time_t *<[clock]>, struct tm *<[res]>);

DESCRIPTION
<<localtime>> converts the time at <[clock]> into local time, then
converts its representation from the arithmetic representation to the
traditional representation defined by <<struct tm>>.

<<localtime>> constructs the traditional time representation in static
storage; each call to <<gmtime>> or <<localtime>> will overwrite the
information generated by previous calls to either function.

<<mktime>> is the inverse of <<localtime>>.

RETURNS
A pointer to the traditional time representation (<<struct tm>>).

PORTABILITY
ANSI C requires <<localtime>>.

<<localtime>> requires no supporting OS subroutines.
*/

#define _DEFAULT_SOURCE
#include <stdlib.h>
#include <time.h>

extern NEWLIB_THREAD_LOCAL struct tm _localtime_buf;

struct tm *
localtime (const time_t * tim_p)
{
  return localtime_r (tim_p, &_localtime_buf);
}
