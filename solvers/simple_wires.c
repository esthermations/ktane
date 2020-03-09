#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include "../ktane.h"

/*
  Returns a string wire_to_cut, meant to fit into a sentence like this:

  "Cut the [wire_to_cut] wire.".

  So "second", "last blue", "third yellow", whatever.

  That doesn't leave much room for error messages, so if this can't solve your
  wire problem it'll return "LIFE SUPPORT".
*/
char const *
simple_wires(void)
{
	char wires[7] = {0};

	printf("[r]ed, [w]hite, [y]ellow, blac[k], [b]lue.\n");
	printf("Enter wire colours, in order: ");
	getl(wires, 6);

	size_t const num_wires = strlen(wires);
	char const last_wire = wires[num_wires-1];

	/* This is some ugly logic, but you can blame the manual for that. */

	switch(num_wires) {
	case 3: {
		if (!occurrences(wires, num_wires, 'r'))
			return "second";
		if (last_wire == 'w')
			return "last";
		if (occurrences(wires, num_wires, 'b') > 1)
			return "last blue";
		return "last";
	}

	case 4: {
		if (occurrences(wires, num_wires, 'r') > 1 && serial_is_odd())
			return "last red";
		if (   last_wire == 'y'
		    && occurrences(wires, num_wires, 'r') == 0)
			return "first";
		if (occurrences(wires, num_wires, 'b') == 1)
			return "first";
		if (occurrences(wires, num_wires, 'y') > 1)
			return "last";
		return "second";
	}

	case 5: {
		if (last_wire == 'k' && serial_is_odd())
			return "fourth";
		if (   occurrences(wires, num_wires, 'r') == 1
		    && occurrences(wires, num_wires, 'y') > 1)
			return "last";
		if (occurrences(wires, num_wires, 'k') == 0)
			return "second";
		return "first";
	}

	case 6: {
		if (occurrences(wires, num_wires, 'y') == 0 && serial_is_odd())
			return "third";
		if (   occurrences(wires, num_wires, 'y') == 1
		    && occurrences(wires, num_wires, 'w') > 1)
			return "fourth";
		if (occurrences(wires, num_wires, 'r') == 0)
			return "last";
		return "fourth";
	}

	default: {
		return "LIFE SUPPORT";
	}
	}
}
