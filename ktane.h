#ifndef _KTANE_H_
#define _KTANE_H_

#include <stdbool.h>

/* repl.c */

void sigint_handler(int UNUSED);

/* util.c */


/** Returns the number of times c appears in char array arr. */
int occurrences(char const arr[], int len, char c);

/** My own solution for being able to get a line from stdin, including spaces,
 * without a trailing newline, without allocating on the heap. 
 *
 * This can't read more than 50 chars (set in util.c), but I don't expect I'll
 * ever need that in this program. 
 * 
 * Usage: getl(some_buffer_youve_allocated, size_of_that_buffer). */
void getl(char *out, int num);

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
