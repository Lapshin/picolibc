/*	$NetBSD: hsearchtest.c,v 1.4 2002/02/21 07:38:15 itojun Exp $	*/

/*
 * Copyright (c) 2001 Christopher G. Demetriou
 * All rights reserved.
 * 
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. The name of the author may not be used to endorse or promote products
 *    derived from this software without specific prior written permission.
 * 
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 * IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
 * NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
 * THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 * 
 * <<Id: LICENSE_GC,v 1.1 2001/10/01 23:24:05 cgd Exp>>
 */

/*
 * Test program for hsearch() et al.
 */

#include <search.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define	TEST(e)	((e) ? (void)0 : testfail(__FILE__, __LINE__, #e))

static void
testfail(const char *file, unsigned long line, const char *expression)
{

	fprintf(stderr, "TEST FAILED: %s: file %s, line %ld\n",
	    expression, file, line);
	exit(1);
}

int
main(void)
{
	ENTRY e, *ep, *ep2;
	int created_ok;
	char ch[2];
	int i;

	created_ok = hcreate(16);
	TEST(created_ok);

	/* ch[1] should be constant from here on down. */
	ch[1] = '\0';
	
	/* Basic insertions.  Check enough that there'll be collisions. */
	for (i = 0; i < 26; i++) {
		ch[0] = 'a' + i;
		e.key = strdup(ch);	/* ptr to provided key is kept! */
		TEST(e.key != NULL);
		e.data = (void *)(uintptr_t)i;
		ep = hsearch(e, ENTER);
		TEST(ep != NULL);
		TEST(strcmp(ep->key, ch) == 0);
		TEST((int) (uintptr_t)ep->data == i);
	}

	/* e.key should be constant from here on down. */
	e.key = ch;

	/* Basic lookups. */
	for (i = 0; i < 26; i++) {
		ch[0] = 'a' + i;
		ep = hsearch(e, FIND);
		TEST(ep != NULL);
		TEST(strcmp(ep->key, ch) == 0);
		TEST((int) (uintptr_t)ep->data == i);
	}

	/* Check duplicate entry.  Should _not_ overwrite existing data.  */
	ch[0] = 'a';
	e.data = (void *)(long)12345;
	ep = hsearch(e, FIND);
	TEST(ep != NULL);
	TEST(strcmp(ep->key, ch) == 0);
	TEST((uintptr_t)ep->data == 0);

	/* Check for something that's not there. */
	ch[0] = 'A';
	ep = hsearch(e, FIND);
	TEST(ep == NULL);

	/* Check two at once. */
	ch[0] = 'a';
	ep = hsearch(e, FIND);
	ch[0] = 'b';
	ep2 = hsearch(e, FIND);
	TEST(ep != NULL);
	TEST(strcmp(ep->key, "a") == 0 && (uintptr_t)ep->data == 0);
	TEST(ep2 != NULL);
	TEST(strcmp(ep2->key, "b") == 0 && (uintptr_t)ep2->data == 1);

	hdestroy();

	exit(0);
}
