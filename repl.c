#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>

#include "ktane.h"

int
main(void)
{
	signal(SIGINT, sigint_handler);
	printf("\nPress Ctrl-C to exit.\n\n");

	while (true) {
		char cmd[3] = {0};
		printf("--> ");
		getl(cmd, 2);
		cmd[2] = 0;

		if (!strcmp(cmd, "q"))
			return 0;
		else if (!strcmp(cmd, "pw"))
			printf("Password: %s\n", password());
		else if (!strcmp(cmd, "sw"))
			printf("Cut the %s wire.\n", simple_wires());
		else if (!strcmp(cmd, "bt"))
			puts(button());
		else if (!strcmp(cmd, "wo"))
			whos_on_first();
		else if (!strcmp(cmd, "cw"))
			complicated_wires();
		else if (!strcmp(cmd, "ws"))
			wire_sequence();
		else if (!strcmp(cmd, "mc"))
			morse_code();
	}
}


void
sigint_handler(int UNUSED)
{
	exit(EXIT_SUCCESS);
}
