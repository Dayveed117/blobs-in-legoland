/**
 * Blob.h
 * Header file for blob.c
 * Contains struct Blob definition and function headers
 */

#ifndef BLOB_H
#define BLOB_H

#include <stdio.h>
#include <stdlib.h>

#include "pixel.h"
#include "frame.h"

typedef struct BLOB
{
    //  Center coordinates
    long r, c;
    int tam;

    //  Frame designation corresponding to blob
    char title[50];

    //  Pointer to next Blob
    struct BLOB *next;

} Blob;

Blob *createBlob(char *title);
Blob *beforePlague(Blob *list, Frame *f, int *input);
Blob *plagueBlob(Blob *b, Pixel *p, int *input);
Blob *scanBlobs(Frame *frames, int *input);
Blob *deleteBlobs(Blob *list);

//  Utility
Blob *adjustCenter(Blob *b);
int compareRGBs(int *pixel, int *user);
int printBlobResults(Blob *list);

//  Special insertion
Blob *insertFirst(Blob *list, Blob *b);
Blob *insertLast(Blob *list, Blob *b);
Blob *insertOrder(Blob *list, Blob *b);

#endif
