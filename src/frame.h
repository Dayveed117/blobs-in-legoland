/**
 * Frame.h
 * Header file for frame.c
 * Contains struct Frame definition and function headers
 */

#ifndef FRAME_H
#define FRAME_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "pixel.h"

typedef struct FRAME
{
    //  Frame information
    char title[50];
    int height, width, channels;

    //  Pointer to next frame
    struct FRAME *next;

    //  Pixel matrix
    Pixel **matrix;

} Frame;

Frame *createFrame(char *title, int height, int width, int channels, Pixel **matrix);
Frame *insertFrame(Frame *list, Frame *f);
Frame *resetFrames(Frame *list);

int printFrameHeader(Frame *f);
int printFrameList(Frame *list);

#endif
