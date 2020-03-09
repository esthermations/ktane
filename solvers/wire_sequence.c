#include <stdio.h>
#include <string.h>
#include "../ktane.h"

/*
  Interface:

  Enter a two-character string, [colour][letter].
  Colour = [r]ed, [b]lue, blac[k].
  Letter = a, b, c.
*/

static bool   red_to(char l);
static bool  blue_to(char l);
static bool black_to(char l);

static int red   = 0;
static int blue  = 0;
static int black = 0;

void
wire_sequence(void)
{
	printf("Enter each wire as [colour][letter], e.g. \"rb\" means \"red to b\".\n");
	printf("[b]lue, blac[k], [r]ed; [a], [b], [c]. [q]uit.\n");
	while (true) {
		char wire[3] = {0};
		printf("Enter the next wire: ");
		getl(wire, 2);

		if (strchr(wire, 'q')) break;

		char colour = wire[0];
		char letter = wire[1];
		if (colour == 'r') puts(  red_to(letter) ? "Cut." : "Don't cut.");
		if (colour == 'b') puts( blue_to(letter) ? "Cut." : "Don't cut.");
		if (colour == 'k') puts(black_to(letter) ? "Cut." : "Don't cut.");
	}

	red = 0;
	blue = 0;
	black = 0;
}

static bool
red_to(char l)
{
	switch (red++) {
	case 0: return l == 'c';
	case 1: return l == 'b';
	case 2: return l == 'a';
	case 3: return l != 'b';
	case 4: return l == 'b';
	case 5: return l != 'b';
	case 6: return true;
	case 7: return l != 'c';
	case 8: return l == 'b';
	default: return false;
	}
}

static bool
blue_to(char l)
{
	switch (blue++) {
	case 0: return l == 'b';
	case 1: return l != 'b';
	case 2: return l == 'b';
	case 3: return l == 'a';
	case 4: return l == 'b';
	case 5: return l != 'a';
	case 6: return l == 'c';
	case 7: return l != 'b';
	case 8: return l == 'a';
	default: return false;
	}
}

static bool
black_to(char l)
{
	switch (black++) {
	case 0: return true;
	case 1: return l != 'b';
	case 2: return l == 'b';
	case 3: return l != 'b';
	case 4: return l == 'b';
	case 5: return l != 'a';
	case 6: return l == 'c';
	case 7: return l == 'c';
	case 8: return l == 'c';
	default: return false;
	}
}
