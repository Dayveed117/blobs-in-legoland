/**
 * Complement for pixel.h
 * Functions for the Pixel structure
 */

#include "pixel.h"

Pixel *createPixel(int *rgb, int x, int y, Pixel *pixelabove)
{
    //  Create pixel pointer
    Pixel *p;
    p = (Pixel *)malloc(sizeof(Pixel));

    //  Store information
    p->r = rgb[0];
    p->g = rgb[1];
    p->b = rgb[2];
    p->x = x;
    p->y = y;
    p->active = -1;

    //  Pointers to adjacent pixels
    p->up = NULL;
    p->left = NULL;
    p->down = NULL;
    p->right = NULL;

    //  Establish up and down connection
    if (pixelabove != NULL)
    {
        pixelabove->down = p;
        p->up = pixelabove;
    }

    return p;
}

Pixel *insertPixel(Pixel *list, Pixel *p)
{
    //  Pixel becomes head list
    if (list == NULL)
        return p;
    else if (p == NULL)
        return list;

    //  Save head list
    Pixel *head = list;

    //  Pixel is inserted at the end of existing list
    while (list != NULL)
    {
        if (list->right == NULL)
        {
            //  Establish right and left connection
            list->right = p;
            p->left = list;

            break;
        }

        list = list->right;
    }

    return head;
}

Pixel *advanceRight(Pixel *list)
{
    if (list == NULL || list->right == NULL)
        return NULL;

    //  Move to next element to the right
    return list->right;
}

//-----------------------------------//
//          PRINT FUNCTIONS          //
//-----------------------------------//

int printPixelCoords(Pixel *p)
{
    if (p == NULL)
    {
        printf("Empty\n");
        return 1;
    }

    printf("(y, x) = (%d, %d)\n", p->y, p->x);

    return 0;
}

int printPixel(Pixel *p)
{
    if (p == NULL)
    {
        printf("\nNone\n");
        return 1;
    }

    printf("\nX      : %d\n", p->x);
    printf("Y      : %d\n", p->y);
    printf("Red    : %d\n", p->r);
    printf("Green  : %d\n", p->g);
    printf("Blue   : %d\n", p->b);
    printf("Active : %d\n", p->active);

    return 0;
}

int printAdjacents(Pixel *p)
{
    if (p == NULL)
        return 1;

    printf("\nUP\n");
    printPixelCoords(p->up);
    printf("\nLEFT\n");
    printPixelCoords(p->left);
    printf("\nDOWN\n");
    printPixelCoords(p->down);
    printf("\nRIGHT\n");
    printPixelCoords(p->right);

    return 0;
}

int printPixelList(Pixel *list)
{
    if (list == NULL)
        return 1;

    while (list != NULL)
    {
        printPixel(list);
        list = list->right;
    }

    return 0;
}

int printPixelHugeList(Pixel **list, int num)
{
    for (int i = 0; i < num; i++)
    {
        printf("\n\nList %d :\n\n", i + 1);
        printPixelList(list[i]);
    }

    return 0;
}
