#ifndef _KTANE_H_
#define _KTANE_H_

#include <unistd.h>
#include <stdbool.h>

/* repl.c */
void sigint_handler(int UNUSED);

/* util.c */
int occurrences(char const arr[], size_t len, char c);
void getl(char *out, size_t num);

/* solvers */
char const *password(void);
char const *simple_wires(void);
char const *button(void);
void whos_on_first(void);
void complicated_wires(void);
void wire_sequence(void);
void morse_code(void);

/* bomb_state.c */
bool serial_is_odd(void);
bool have_lit_frk(void);
bool have_lit_car(void);
bool have_parallel_port(void);
int num_batteries(void);

#endif // ktane.h
