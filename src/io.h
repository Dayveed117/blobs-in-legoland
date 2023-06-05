#ifndef IO_H
#define IO_H

#include <stdio.h>
#include <stdlib.h>

/**
 * Helper functions for main program
 * Namely input and output functions
 */

int chooseFile();
int quit();
int info();
int menu();
int *userPrompt(int *vec);
int *readInput(int argc, char *argv[]);
FILE *openFile(char *filename);

#endif
