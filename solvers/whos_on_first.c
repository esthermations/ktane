#include <ctype.h>
#include <stdio.h>
#include <string.h>

#include "../ktane.h"

/*
  As I'm sure any experienced player has figured out at this point, when reading
  something for Who's On First, the bomb-defuser and manual-reader should speak
  letter-by-letter to remove any ambiguity.

  However, to make things even faster, this solver will ask the bomb-defuser to
  read the display AND all six button labels, allowing the program to solve for
  which button to press instantly, with no back-and-forth.

  This makes it harder on the bomb-defuser, but you've gotta save those frames.
  (The time saved is probably in the order of 10 seconds.)
*/

/*
  Process looks like this:
  1. Get DISPLAY. 10 chars, from page 9.
  2. Get button_position. Enum.
  3. Get button_text. 10 chars, from page 10.
  4. Search buttons[] for string from table[]. Return first result.
*/

/*
  Test case:
  display -- SAYS
  1 -- FIRST
  2 -- NOTHING
  3 -- YES
  4 -- NO
  5 -- PRESS
  6 -- RIGHT
*/

enum Button_Positions {
	TOP_LEFT = 0,
	TOP_RIGHT,
	MID_LEFT,
	MID_RIGHT,
	BOT_LEFT,
	BOT_RIGHT,
	NUM_BUTTONS
};

void
whos_on_first(void)
{
	printf("When prompted, enter buttons left-to-right, top-to-bottom.\n");
	printf("Top-left is first, bottom-right is last.\n");

	/* Who's on First always has three rounds. */
	for (int wof_round = 0; wof_round < 3; ++wof_round) {
		char display[10] = {0};
		printf("What's on the display? ");
		getl(display, 10);

		char buttons[6][10] = {{0}};
		size_t button_number = 0;

		/* Grab button text */

		while (button_number < NUM_BUTTONS) {
			printf("What's on button %lu? ", button_number + 1);
			getl(buttons[button_number++], 10);
		}

		/* Ensure all given text is uppercase */
		for (int i = 0; i < 10; ++i)
			display[i] = toupper(display[i]);

		for (int i = 0; i < NUM_BUTTONS; ++i)
			for (int l = 0; buttons[i][l]; ++l)
				buttons[i][l] = toupper(buttons[i][l]);



		char const *display_options[6][10] = {
			[TOP_LEFT]  = {"UR", 0 },
			[TOP_RIGHT] = {"FIRST", "OKAY", "C", 0 },
			[MID_LEFT]  = {"NOTHING", "LED", "THEY ARE", 0 },
			[MID_RIGHT] = {"BLANK", "READ", "RED", "YOU", "YOUR", "YOU'RE", "THEIR", 0 },
			[BOT_LEFT]  = {"", "REED", "LEED", "THEY'RE", 0 },
			[BOT_RIGHT] = {"DISPLAY", "SAYS", "NO", "LEAD", "HOLD ON", "YOU ARE", "THERE", "SEE", "CEE", 0 },
		};

		int button_position = -1;
		for (int i = 0; i < NUM_BUTTONS && button_position == -1; ++i)
			for (int s = 0; s < 10 && display_options[i][s]; ++s)
				if (!strcmp(display_options[i][s], display))
					button_position = i;

		char const *button_label = buttons[button_position];

		/**
		   Query button_label against an enormous, disgusting list.

		   The first string in each row is button_label. We search all
		   strings after that for a string we have in buttons[], and the
		   first match is button_to_push.

		   Note that every row actually contains its first element again,
		   making it impossible to get a row with no matches.

		   For example, the "UH HUH" row has "UH HUH" as its first
		   element. That means you're guaranteed to press it right away,
		   so every other entry is redundant.

		   This means that each row in push_options should start and end
		   with the same string.

		   Nonetheless, this table is ridiculous. No, I didn't type them
		   by hand, I copied them from the PDF then formatted them with
		   some keyboard macros.

		   I've also taken the liberty of sorting them, which probably
		   makes this easier to read than the manual. Go figure.
		*/

		char const *push_options[28][16] = {
			{"BLANK", "WAIT", "RIGHT", "OKAY", "MIDDLE", "BLANK", 0 },
			{"DONE", "SURE", "UH HUH", "NEXT", "WHAT?", "YOUR", "UR", "YOU'RE", "HOLD", "LIKE", "YOU", "U", "YOU ARE", "UH UH", "DONE", 0 },
			{"FIRST", "LEFT", "OKAY", "YES", "MIDDLE", "NO", "RIGHT", "NOTHING", "UHHH", "WAIT", "READY", "BLANK", "WHAT", "PRESS", "FIRST", 0 },
			{"HOLD", "YOU ARE", "U", "DONE", "UH UH", "YOU", "UR", "SURE", "WHAT?", "YOU'RE", "NEXT", "HOLD", 0 },
			{"LEFT", "RIGHT", "LEFT", 0 },
			{"LIKE", "YOU'RE", "NEXT", "U", "UR", "HOLD", "DONE", "UH UH", "WHAT?", "UH HUH", "YOU", "LIKE", 0 },
			{"MIDDLE", "BLANK", "READY", "OKAY", "WHAT", "NOTHING", "PRESS", "NO", "WAIT", "LEFT", "MIDDLE", 0 },
			{"NEXT", "WHAT?", "UH HUH", "UH UH", "YOUR", "HOLD", "SURE", "NEXT", 0 },
			{"NO", "BLANK", "UHHH", "WAIT", "FIRST", "WHAT", "READY", "RIGHT", "YES", "NOTHING", "LEFT", "PRESS", "OKAY", "NO", 0 },
			{"NOTHING", "UHHH", "RIGHT", "OKAY", "MIDDLE", "YES", "BLANK", "NO", "PRESS", "LEFT", "WHAT", "WAIT", "FIRST", "NOTHING", 0 },
			{"OKAY", "MIDDLE", "NO", "FIRST", "YES", "UHHH", "NOTHING", "WAIT", "OKAY", 0 },
			{"PRESS", "RIGHT", "MIDDLE", "YES", "READY", "PRESS", 0 },
			{"READY", "YES", "OKAY", "WHAT", "MIDDLE", "LEFT", "PRESS", "RIGHT", "BLANK", "READY", 0 },
			{"RIGHT", "YES", "NOTHING", "READY", "PRESS", "NO", "WAIT", "WHAT", "RIGHT", 0 },
			{"SURE", "YOU ARE", "DONE", "LIKE", "YOU'RE", "YOU", "HOLD", "UH HUH", "UR", "SURE", 0 },
			{"U", "UH HUH", "SURE", "NEXT", "WHAT?", "YOU'RE", "UR", "UH UH", "DONE", "U", 0 },
			{"UH HUH", "UH HUH", 0 },
			{"UH UH", "UR", "U", "YOU ARE", "YOU'RE", "NEXT", "UH UH", 0 },
			{"UHHH", "READY", "NOTHING", "LEFT", "WHAT", "OKAY", "YES", "RIGHT", "NO", "PRESS", "BLANK", "UHHH", 0 },
			{"UR", "DONE", "U", "UR", 0 },
			{"WAIT", "UHHH", "NO", "BLANK", "OKAY", "YES", "LEFT", "FIRST", "PRESS", "WHAT", "WAIT", 0 },
			{"WHAT", "UHHH", "WHAT", 0 },
			{"WHAT?", "YOU", "HOLD", "YOU'RE", "YOUR", "U", "DONE", "UH UH", "LIKE", "YOU ARE", "UH HUH", "UR", "NEXT", "WHAT?", 0 },
			{"YES", "OKAY", "RIGHT", "UHHH", "MIDDLE", "FIRST", "WHAT", "PRESS", "READY", "NOTHING", "YES", 0 },
			{"YOU ARE", "YOUR", "NEXT", "LIKE", "UH HUH", "WHAT?", "DONE", "UH UH", "HOLD", "YOU", "U", "YOU'RE", "SURE", "UR", "YOU ARE", 0 },
			{"YOU", "SURE", "YOU ARE", "YOUR", "YOU'RE", "NEXT", "UH HUH", "UR", "HOLD", "WHAT?", "YOU", 0 },
			{"YOU'RE", "YOU", "YOU'RE", 0 },
			{"YOUR", "UH UH", "YOU ARE", "UH HUH", "YOUR", 0 },
		};

		size_t row = 0;

		for (int i = 0; i < 28; ++i) {
			if (!strcmp(button_label, push_options[i][0])) {
				row = i;
				break;
			}
		}

		bool found_button_to_press = false;
		for (int i = 1; i < 16 && !found_button_to_press; ++i) {
			char const *push_option = push_options[row][i];
			if (!push_option) break;

			for (int b = 0; b < NUM_BUTTONS; ++b) {
				if (!strcmp(buttons[b], push_option)) {
					printf("Press button %d (%s).\n", b, buttons[b]);
					found_button_to_press = true;
					break;
				}
			}
		}



	}
}
