#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ktane.h"

int
occurrences(char const arr[], int len, char c)
{
	int count = 0;
	for (int i = 0; i < len; ++i)
		if (arr[i] == c) ++count;
	return count;
}

static char getl_buffer[50] = {0};
static int const getl_buffer_size = 50;

void
getl(char *out, int num)
{
	fgets(getl_buffer, getl_buffer_size, stdin);
	char *nl = strrchr(getl_buffer, '\n');
	if (nl) *nl = 0;

	for (int i = 0; i < num; ++i)
		out[i] = getl_buffer[i];

	memset(getl_buffer, 0, getl_buffer_size);
}
