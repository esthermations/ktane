#include <stdint.h>
#include <stdio.h>
#include <string.h>

#include "../ktane.h"

void
complicated_wires(void)
{
	printf("Enter details about each wire.\n");
	printf("[r]ed, [b]lue, [s]tar, [l]ed. [q]uit.\n");

	for (int wire_number = 0; wire_number < 7; ++wire_number) {
		printf("Wire %d: ", wire_number);

		char wire[6] = {0};
		getl(wire, 5);

		if (strchr(wire, 'q')) return;
		bool const red  = strchr(wire, 'r');
		bool const blue = strchr(wire, 'b');
		bool const led  = strchr(wire, 'l');
		bool const star = strchr(wire, 's');

		uint8_t bitmask = 0;
		bitmask |= (uint8_t) red  << 0; // worth 1
		bitmask |= (uint8_t) blue << 1; // worth 2
		bitmask |= (uint8_t) led  << 2; // worth 4
		bitmask |= (uint8_t) star << 3; // worth 8

		/* These are ordered such that each logical possibility falls
		   through to a single case. */

		switch (bitmask) {
		case 0:
		case 8:
		case 9: puts("Cut."); break;
		case 1:
		case 2:
		case 3:
		case 7: puts(!serial_is_odd() ? "Cut." : "Don't cut."); break;
		case 4:
		case 10:
		case 15: puts("Don't cut."); break;
		case 5:
		case 12:
		case 13: puts(num_batteries() > 1 ? "Cut." : "Don't cut."); break;
		case 6:
		case 11:
		case 14: puts(have_parallel_port() ? "Cut." : "Don't cut."); break;
		}
	}
}
