#include <stdio.h>
#include <string.h>

#include "../ktane.h"

void
simple_wires(void)
{
	char wires[7] = {0};

	printf("[r]ed, [w]hite, [y]ellow, blac[k], [b]lue.\n");
	printf("Enter wire colours, in order: ");
	getl(wires, 6);

	int const num_wires = strlen(wires);
	char const last_wire = wires[num_wires-1];

	/* This is some ugly logic, but you can blame the manual for that. */

	switch(num_wires) {
	case 3: {

		if (!occurrences(wires, num_wires, 'r')) {
			puts("Cut the second wire.");
			return;
		}

		if (last_wire == 'w') {
			puts("Cut the last wire.");
			return;
		}

		if (occurrences(wires, num_wires, 'b') > 1) {
			puts("Cut the last blue wire.");
			return;
		}

		/* Else */
		puts("Cut the last wire.");
		return;
	}

	case 4: {
		if (occurrences(wires, num_wires, 'r') > 1 && serial_is_odd()) {
			puts("Cut the last red wire.");
			return;
		}

		if (last_wire == 'y' && occurrences(wires, num_wires, 'r') == 0) {
			puts("Cut the first wire.");
			return;
		}

		if (occurrences(wires, num_wires, 'b') == 1) {
			puts("Cut the first wire.");
			return;
		}
		if (occurrences(wires, num_wires, 'y') > 1) {
			puts("Cut the last wire.");
			return;
		}

		/* Else */
		puts("Cut the second wire.");
		return;
	}

	case 5: {
		if (last_wire == 'k' && serial_is_odd()) {
			puts("Cut the fourth wire.");
			return;
		}

		if (occurrences(wires, num_wires, 'r') == 1 && 
		    occurrences(wires, num_wires, 'y') > 1) 
		{
			puts("Cut the last wire.");
			return;
		}

		if (occurrences(wires, num_wires, 'k') == 0) {
			puts("Cut the second wire.");
			return;
		}

		/* Else */
		puts("Cut the first wire.");
		return;
	}

	case 6: {
		if (occurrences(wires, num_wires, 'y') == 0 && serial_is_odd()) {
			puts("Cut the third wire.");
			return;
		}

		if (occurrences(wires, num_wires, 'y') == 1 && 
			occurrences(wires, num_wires, 'w') > 1)
		{
			puts("Cut the fourth wire.");
			return;
		}

		if (occurrences(wires, num_wires, 'r') == 0) {
			puts("Cut the last wire.");
			return;
		}

		/* Else */
		puts("Cut the fourth wire.");
		return;
	}

	default: {
		puts("ERROR: I don't know which wire you should cut. Did you enter something wrong?");
		puts("       (This could also be a bug in the program. Yell at Esther.)");
		return;
	}
	}
}
