#ifndef IO_H
#define IO_H

#include <stdio.h>
#include <stdlib.h>

#endif

/**
 * Helper functions for main program
 * Namely input and output functions
 */

int chooseFile()
{
    printf("\nA file must be chosen to proceed :\n");
    printf("0 - Exit\n");
    printf("1 - TEST FILE 1\n");
    printf("2 - TEST FILE 2\n");
    printf("3 - TEST FILE 3\n");
    printf("4 - REAL FILE\n");

    int choice = -1;

    do
    {
        printf("\nOption : ");
        scanf(" %d", &choice);
    } while (choice < 0 || choice > 4);

    return choice;
}

int quit()
{
    printf("\nSee you next time!\n");
    exit(0);
}

int info()
{
    printf("\nFinding Blobs in legoland :\n");
    printf("A file must be loaded in a specified format\n");
    printf("The file holds raw RGB values of an image (pixels)\n");
    printf("The user may specify RGB values and a margin\n");
    printf("The program will search for pixels whose values are within specified range\n");
    printf("A chain of adjacent pixels, with length > 1, is considered a blob\n");
    printf("The program will find all blobs within range, specified by the user, in the file loaded.\n\n");

    return 0;
}

int menu()
{
    printf("-----------------------------\n");
    printf("- Finding Blobs in LegoLand -\n");
    printf("-----------------------------\n");
    printf("\n0 - Exit\n");
    printf("1 - Info\n");
    printf("2 - Find Blobs\n");

    int choice = -1;

    do
    {
        printf("\nValue : ");
        scanf(" %d", &choice);
    } while (choice < 0 || choice > 2);

    return choice;
}

int *userPrompt(int *vec)
{
    vec = (int *)malloc(4 * sizeof(int));

    printf("\nValues above 255 or below 0 will be normalized to 255 or 0, respectively\n");

    printf("Red = ");
    scanf("%d", &vec[0]);

    printf("Green = ");
    scanf("%d", &vec[1]);

    printf("Blue = ");
    scanf("%d", &vec[2]);

    printf("Diff = ");
    scanf("%d", &vec[3]);

    //  Normalize values
    for (int i = 0; i < 4; i++)
    {
        if (vec[i] < 0)
            vec[i] = 0;
        else if (vec[i] > 255)
            vec[i] = 255;
    }

    return vec;
}

int *readInput(int argc, char *argv[])
{
    int *input = NULL;

    //  User input from cmd
    if (argc >= 5)
    {
        input = (int *)malloc(4 * sizeof(int));

        for (int i = 1; i <= 4; i++)
            input[i - 1] = atoi(argv[i]);
    }
    //  User input when not giving necessary arguments
    else
        input = userPrompt(input);

    return input;
}

FILE *openFile(char *filename)
{
    //  Open file
    FILE *fp = fopen(filename, "r");

    if (fp == NULL)
    {
        perror("Unable to open file");
        exit(0);
    }

    return fp;
}
