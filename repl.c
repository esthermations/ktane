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

struct Option {
	char command[3];
	void (*handler_function)();
};

static const 
struct Option options[] = {
	[PASSWORD]          = {"pw", &password},
	[SIMPLE_WIRES]      = {"sw", &simple_wires},
	[BUTTON]            = {"bt", &button},
	[WHOS_ON_FIRST]     = {"wo", &whos_on_first},
	[COMPLICATED_WIRES] = {"cw", &complicated_wires},
	[WIRE_SEQUENCE]     = {"ws", &wire_sequence},
	[MORSE_CODE]        = {"mc", &morse_code}
};

static char const *const readable_solver_name[_NUM_SOLVERS] = {
	[PASSWORD]          = "Password",
	[SIMPLE_WIRES]      = "Simple Wires",
	[BUTTON]            = "Button",
	[WHOS_ON_FIRST]     = "Who's on First",
	[COMPLICATED_WIRES] = "Complicated Wires",
	[WIRE_SEQUENCE]     = "Wire Sequence",
	[MORSE_CODE]        = "Morse Code"
};

int
main(void)
{
	signal(SIGINT, sigint_handler);
	printf("\nPress Ctrl-C or enter 'q' to exit.\n\n");

	puts("Available solvers:");

	for (int i = 0; i < _NUM_SOLVERS; ++i) {
		printf("%s -> %s\n", options[i].command, readable_solver_name[i]);
	}


	while (true) {
		char cmd[3] = {0};
		printf("--> ");
		getl(cmd, 2);
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
