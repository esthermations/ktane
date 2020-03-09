#include <stdio.h>
#include <string.h>

#include "../ktane.h"


/* Took the liberty of sorting this. */
enum Morse_Words {
	BEATS = 0,
	BISTRO,
	BOMBS,
	BOXES,
	BREAK,
	BRICK,
	FLICK,
	HALLS,
	LEAKS,
	SHELL,
	SLICK,
	STEAK,
	STING,
	STROBE,
	TRICK,
	VECTOR,
	NUM_WORDS
};

static char const *words_as_morse[] = {
	[BEATS]  = "-... . .- - ...",
	[BISTRO] = "-... .. ... - .-. ---",
	[BOMBS]  = "-... --- -- -... ...",
	[BOXES]  = "-... --- -..- . ...",
	[BREAK]  = "-... .-. . .- -.-",
	[BRICK]  = "-... .-. .. -.-. -.-",
	[FLICK]  = "..-. .-.. .. -.-. -.-",
	[HALLS]  = ".... .- .-.. .-.. ...",
	[LEAKS]  = ".-.. . .- -.- ...",
	[SHELL]  = "... .... . .-.. .-..",
	[SLICK]  = "... .-.. .. -.-. -.-",
	[STEAK]  = "... - . .- -.-",
	[STING]  = "... - .. -. --.",
	[STROBE] = "... - .-. --- -... .",
	[TRICK]  = "- .-. .. -.-. -.-",
	[VECTOR] = "...- . -.-. - --- .-."
};

static float const frequencies[] = {
	[BEATS]  = 3.600,
	[BISTRO] = 3.522,
	[BOMBS]  = 3.565,
	[BOXES]  = 3.535,
	[BREAK]  = 3.572,
	[BRICK]  = 3.575,
	[FLICK]  = 3.555,
	[HALLS]  = 3.515,
	[LEAKS]  = 3.542,
	[SHELL]  = 3.505,
	[SLICK]  = 3.522,
	[STEAK]  = 3.582,
	[STING]  = 3.592,
	[STROBE] = 3.545,
	[TRICK]  = 3.532,
	[VECTOR] = 3.595,
};

void
morse_code(void)
{
	printf("Enter as much morse code as you can get, ACCURATELY.\n");
	printf("If you enter any incorrect morse, you may fail.\n");
	printf("Enter a 'd' to discard a string. Enter a 'q' to quit.\n");

	char const discard_char = 'd';
	char const exit_char = 'q';
	char attempts[10][20] = {{0}};
	int attempt = 0;

	while (attempt < 10) {
		char *morse = attempts[attempt];
		printf("Enter some morse: ");
		getl(morse, 20);

		if (strchr(morse, discard_char)) continue;
		if (strchr(morse,    exit_char)) return;

		++attempt;

		size_t answers[NUM_WORDS] = {0};
		size_t num_answers = 0;

		for (int w = 0; w < NUM_WORDS; ++w) {
			char const *word = words_as_morse[w];
			for (int i = 0; i < attempt; ++i) {
				if (strstr(word, attempts[i])) {
					answers[num_answers++] = w;
				}
			}
		}

		if (num_answers == 1) {
			printf("Respond at %.3f MHz.\n", frequencies[answers[0]]);
			return;
		} else if (num_answers == 0) {
			printf("NO ANSWER FOUND.");
			printf("You might have entered something wrong.\n");
			return;
		}
	}
}
