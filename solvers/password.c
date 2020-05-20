#include <stdio.h>
#include <string.h>

#include "../ktane.h"

/*
  Notes on data:

  Words are always 5 letters long, so use a 6-char array for a terminating 0.
  Columns are always 6 letters long. 7-char array for terminating 0.

  Note that we have a bunch of arrays on the stack here, so they're liable to be
  initialised to garbage. Explicitly initialise.
*/

/*
  Test case:
  In : "gkbdwy" "dcmihg" "gcsjev"
  Out: "where"
*/

void
password(void)
{
	static char const words[][6] = {
		"about", "after", "again", "below", "could", "every", "first",
		"found", "great", "house", "large", "learn", "never", "other",
		"place", "plant", "point", "right", "small", "sound", "spell",
		"still", "study", "their", "there", "these", "thing", "think",
		"three", "water", "where", "which", "world", "would", "write"
	};

	int const num_words = sizeof(words)/sizeof(*words);

	char columns[5][7] = {{ 0 }};
	int const column_len = 6;
	int num_columns = 0;

	while (num_columns != 5) {
		printf("Enter column %d: ", num_columns + 1);
		getl(columns[num_columns], 6);
		++num_columns;

		/* Stores indexes for words[]. */
		int answers[35] = {0};
		int num_answers = 0;

		for (int w = 0; w < num_words; ++w) {
			char const *word = words[w];
			for (int l = 0; l < num_columns; ++l) {
				char const  this_letter = word[l];
				char const *this_column = columns[l];
				int const last_column = num_columns - 1;

				if (!occurrences(this_column, column_len, this_letter))
					break;
				else if (l == last_column)
					answers[num_answers++] = w;
			}
		}

		if (num_answers == 0) {
			goto no_password_found;
		}
		else if (num_answers == 1) {
			printf("The password is: %s\n", words[answers[0]]);
			return;
		}
		else continue;
	}

	/* Using a goto so this can be at the end of the function, handling the case
	   where num_answersr is somehow not 0 or 1 at the end. */
no_password_found:
	puts("NO PASSWORD FOUND. Did you enter something wrong?");
	return;
}
