/**
 * Pixel.h
 * Header file for the pixel.c
 * Contains struct Pixel definition and function headers
 */

#ifndef PIXEL_H
#define PIXEL_H

#include <stdio.h>
#include <stdlib.h>

typedef struct PIXEL
{
    //  Color information
    int r, g, b;

    //  Coordinates
    int x, y;

    //  Flags
    int active;

    //  Adjacent pixels
    struct PIXEL *left;
    struct PIXEL *right;
    struct PIXEL *up;
    struct PIXEL *down;

} Pixel;

Pixel *createPixel(int *rgb, int x, int y, Pixel *pixelabove);
Pixel *insertPixel(Pixel *list, Pixel *p);
Pixel *advanceRight(Pixel *list);

int printPixelCoords(Pixel *p);
int printPixel(Pixel *p);
int printAdjacents(Pixel *p);
int printPixelList(Pixel *p);
int printPixelHugeList(Pixel **list, int num);

#endif
