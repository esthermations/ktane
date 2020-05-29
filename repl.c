#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>

#include "ktane.h"

enum Solver {
	PASSWORD,
	SIMPLE_WIRES,
	BUTTON,
	WHOS_ON_FIRST,
	COMPLICATED_WIRES,
	WIRE_SEQUENCE,
	MORSE_CODE,
	_NUM_SOLVERS
};

static const 
struct Option {
	char command[3];
	void (*handler_function)();
	char const *readable_name;
} options[] = {
	[PASSWORD]          = {"pw", &password,          "Password"},
	[SIMPLE_WIRES]      = {"sw", &simple_wires,      "Simple Wires"},
	[BUTTON]            = {"bt", &button,            "Button"},
	[WHOS_ON_FIRST]     = {"wo", &whos_on_first,     "Who's on First"},
	[COMPLICATED_WIRES] = {"cw", &complicated_wires, "Complicated Wires"},
	[WIRE_SEQUENCE]     = {"ws", &wire_sequence,     "Wire Sequence"},
	[MORSE_CODE]        = {"mc", &morse_code,        "Morse Code"}
};

int
main(void)
{
	signal(SIGINT, sigint_handler);
	printf("\nPress Ctrl-C or enter 'q' to exit.\n\n");

	puts("Available solvers:");

	for (int i = 0; i < _NUM_SOLVERS; ++i) {
		printf("%s -> %s\n", options[i].command, options[i].readable_name);
	}

	/* Main loop */

	while (true) {
		char cmd[3] = {0};
		printf("--> ");
		getl(cmd, 2); /* <- this blocks waiting for user input */
		cmd[2] = 0;

		/* Player quits */
		if (!strcmp(cmd, "q")) return 0;

		for (int i = 0; i < _NUM_SOLVERS; ++i) {
			if (!strcmp(cmd, options[i].command)) {
				options[i].handler_function();
			}
		}
	}
}


void 
quit(void)
{
	printf("\n\nBye!\n");
	exit(EXIT_SUCCESS);
}

void sigint_handler(int UNUSED) { quit(); }
