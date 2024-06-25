/*
(C) Copyright IBM Corp. 2006

All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:

    * Redistributions of source code must retain the above copyright notice,
this list of conditions and the following disclaimer.
    * Redistributions in binary form must reproduce the above copyright
notice, this list of conditions and the following disclaimer in the
documentation and/or other materials provided with the distribution.
    * Neither the name of IBM nor the names of its contributors may be
used to endorse or promote products derived from this software without
specific prior written permission.

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

Author: Joel Schopp <jschopp@austin.ibm.com>
*/

#include <picolibc.h>

#include <_ansi.h>
#include <stdio.h>

#include "c99ppe.h"

typedef struct
{
  const char* file;
  unsigned int pad0[ 3 ];
  const char* mode;
  unsigned int pad1[ 3 ];
} c99_fopen_t;

#ifndef _REENT_ONLY
FILE *
fopen (const char *__restrict file,
	const char *__restrict mode)
{
  int ret;
  c99_fopen_t args;
  FILE *fp;
  struct _reent *ptr = _REENT;

  CHECK_INIT(ptr);

  fp = __sfp(ptr);
  if (!fp) {
    return NULL;
  }

  args.file = file;
  args.mode = mode;

  ret = __send_to_ppe(SPE_C99_SIGNALCODE, SPE_C99_FOPEN, &args);

  if (ret) {
    fp->_fp = ret;
    return fp;
  }
  else {
    __sfp_free(fp);
    return NULL;
  }
}
#endif /* ! _REENT_ONLY */
