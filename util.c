#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "ktane.h"

/* Returns the number of times c appears in char array arr. */
int
occurrences(char const arr[], size_t len, char c)
{
	int count = 0;
	for (int i = 0; i < len; ++i)
		if (arr[i] == c) ++count;
	return count;
}


/*
  My own solution for being able to get a line from stdin, including spaces,
  without a trailing newline, without allocating on the heap.

  Obviously can't read more than 50 chars, but I don't expect I'll ever need
  that in this program.

  Usage: getl(some_buffer_youve_allocated, size_of_that_buffer).
*/

static char getl_buffer[50] = {0};
static size_t const getl_buffer_size = 50;

void
getl(char *out, size_t num)
{
	fgets(getl_buffer, getl_buffer_size, stdin);
	char *nl = strrchr(getl_buffer, '\n');
	if (nl) *nl = 0;

	for (int i = 0; i < num; ++i)
		out[i] = getl_buffer[i];

	memset(getl_buffer, 0, getl_buffer_size);
}
