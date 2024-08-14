/* Copyright (c) 2002, Joerg Wunsch
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

/* $Id: fgets.c 1944 2009-04-01 23:12:20Z arcanum $ */

#include "stdio_private.h"

FILE_FN_UNLOCKED_SPECIFIER
char *
FILE_FN_UNLOCKED(fgets)(char *str, int size, FILE *stream)
{
	char *cp;
	int c;

	if ((stream->flags & __SRD) == 0 || size <= 0)
		return NULL;

	size--;
	for (c = 0, cp = str; c != '\n' && size > 0; size--, cp++) {
		if ((c = FILE_FN_UNLOCKED(fgetc)(stream)) == EOF)
			return NULL;
		*cp = (char)c;
	}
	*cp = '\0';

	return str;
}

#ifdef _WANT_FLOCKFILE
char *
fgets(char *str, int size, FILE *stream)
{
    char * ret;
    __flockfile(stream);
    ret = FILE_FN_UNLOCKED(fgets)(str, size, stream);
    __funlockfile(stream);
    return ret;
}
#endif
