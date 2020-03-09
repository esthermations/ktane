CC=gcc
CFLAGS=-std=c99 -Wpedantic -Wall -Wunused-function

outfile=ktane

solvers=$(wildcard solvers/*.c)
sources=$(wildcard *.c)
headers=$(wildcard *.h)

all_files=$(solvers) $(sources) $(headers)

all: $(all_files)
	$(CC) $(CFLAGS) $(all_files) -o $(outfile)

debug: $(all_files)
	$(CC) $(CFLAGS) $(all_files) -o $(outfile) -g
