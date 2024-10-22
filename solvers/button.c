#include <stdio.h>
#include <string.h>

#include "../ktane.h"

/* Call this when the defuser needs to hold the button. It will print some
 * questions for you to answer, then return a string saying when to release. */
static char const *hold_the_button(void);

void
button(void)
{
	printf("[b]lue, [r]ed, [w]hite, [y]ellow.\n");
	printf("What colour is the button?\n");
	printf("Enter a colour: ");
	char colour_str[2] = {0};
	getl(colour_str, 1);

	printf("[a]bort, [d]etonate, [h]old.\n");
	printf("What text is on the button?\n");
	printf("Enter text: ");
	char text_str[2] = {0};
	getl(text_str, 1);

	char const colour = colour_str[0];
	char const   text =   text_str[0];

	if (colour == 'b' && text == 'a') {
		puts(hold_the_button());
		return;
	}

	if (text == 'd' && num_batteries() > 1) {
		puts("Press and release.");
		return;
	}

	if (colour == 'w' && have_lit_car()) {
		puts(hold_the_button());
		return;
	}

	if (num_batteries() > 2 && have_lit_frk()) {
		puts("Press and release.");
		return;
	}

	if (colour == 'y') {
		puts(hold_the_button());
		return;
	}

	if (colour == 'r' && text == 'h') {
		puts("Press and release.");
		return;
	}

	/* Else */
	puts(hold_the_button());
	return;
}

static char const *
hold_the_button(void)
{
	printf("\nHold the button.\n\n");
	printf("[b]lue, [w]hite, [y]ellow, [o]ther.\n");
	printf("What colour is the strip? ");
	char strip_colour_str[2] = {0};
	getl(strip_colour_str, 1);

	char const strip_colour = strip_colour_str[0];
	if (strip_colour == 'b') return "Release on a 4.";
	if (strip_colour == 'w') return "Release on a 1.";
	if (strip_colour == 'y') return "Release on a 5.";
	return "Release on a 1.";
}
