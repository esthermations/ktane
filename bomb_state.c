#include <stdio.h>
#include "ktane.h"

static int odd_ser = -1;
static int lit_frk = -1;
static int lit_car = -1;
static int num_bat = -1;

static int parallel_port = -1;

bool
have_parallel_port(void)
{
	while (parallel_port == -1) {
		char in_str[2] = {0};
		printf("Does the bomb have a parallel port? ");
		getl(in_str, 1);

		char in = in_str[0];
		if      (in == 'y' || in == 'Y') parallel_port = 1;
		else if (in == 'n' || in == 'N') parallel_port = 0;
	}
	return parallel_port == 1;
}

bool
serial_is_odd(void)
{
	while (odd_ser == -1) {
		printf("Enter last digit of serial no.: ");

		int in = -1;
		scanf("%d", &in);
		odd_ser = in % 2 == 1;
	}
	return odd_ser;
}

bool
have_lit_frk(void)
{
	while (lit_frk == -1) {
		char in_str[2];
		printf("Do you have a lit FRK indicator? ");
		getl(in_str, 1);

		char in = in_str[0];
		if      (in == 'y' || in == 'Y') lit_frk = 1;
		else if (in == 'n' || in == 'N') lit_frk = 0;
	}
	return lit_frk;
}

bool
have_lit_car(void)
{
	while (lit_car == -1) {
		char in_str[2];
		printf("Do you have a lit CAR indicator? ");
		getl(in_str, 1);

		char in = in_str[0];
		if      (in == 'y' || in == 'Y') lit_car = 1;
		else if (in == 'n' || in == 'N') lit_car = 0;
	}
	return lit_car;
}

int
num_batteries(void)
{
	while (num_bat == -1) {
		printf("How many batteries are on the bomb? ");
		scanf("%d", &num_bat);
	}
	return num_bat;
}
