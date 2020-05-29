#ifndef _KTANE_H_
#define _KTANE_H_

#include <stdbool.h>

/* repl.c */

void sigint_handler(int UNUSED);

/* util.c */


/** Returns the number of times c appears in char array arr. */
int occurrences(char const arr[], int len, char c);

/** 
 * Gets a line from stdin and puts it into out_buffer, without the trailing
 * newline. This blocks until the user enters something and presses enter. 
 *
 * The buffer you give will be memset to 0, but if the user input is too long,
 * out_buffer won't end up with a terminating zero. Make sure your buffer is big
 * enough.
 *
 * This uses a static internal buffer in util.c, so it can only get as much text
 * as will fit in that buffer. (At time of writing, it's 50 chars.)
 */
void getl(char *out_buffer, int out_buffer_size);

/* solvers */

void password(void);
void simple_wires(void);
void button(void);
void whos_on_first(void);
void complicated_wires(void);
void wire_sequence(void);
void morse_code(void);

/* bomb_state.c */

/** Is the serial number odd? */
bool serial_is_odd(void);

/** Is the FRK indicator lit? */
bool have_lit_frk(void);

/** Is the CAR indicator lit? */
bool have_lit_car(void);

/** Does the bomb have a parallel port? */
bool have_parallel_port(void);

/** How many batteries does the bomb have? */
int num_batteries(void);

#endif // ktane.h
