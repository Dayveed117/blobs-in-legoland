/**
 * Complement for frame.h
 * Functions for the Frame structure
 */

#include "frame.h"

Frame *createFrame(char *title, int height, int width, int channels, Pixel **matrix)
{
    //  Initialize frame pointer
    Frame *f = (Frame *)malloc(sizeof(Frame));

    //  Store information
    strcpy(f->title, title);
    f->height = height;
    f->width = width;
    f->channels = channels;

    //  Initialize pointers to null
    f->next = NULL;
    f->matrix = matrix;

    return f;
}

Frame *insertFrame(Frame *list, Frame *f)
{
    //  Frame becomes head list
    if (list == NULL)
        return f;
    else if (f == NULL)
        return list;

    //  Save head list
    Frame *head = list;

    //  Frame is inserted at the end of existing list
    while (list != NULL)
    {
        if (list->next == NULL)
        {
            list->next = f;
            break;
        }

        list = list->next;
    }

    return head;
}

Frame *resetFrames(Frame *list)
{
    if (list == NULL)
        return NULL;

    Frame *head = list;

    //  Go through all frames
    while (list != NULL)
    {
        for (int i = 0; i < list->height; i++)
        {
            //  Save head of row
            Pixel *head = list->matrix[i];

            while (list->matrix[i] != NULL)
            {
                //  Reset active to -1
                list->matrix[i]->active = -1;
                //  Proceed to next pixel
                list->matrix[i] = list->matrix[i]->right;
            }

            list->matrix[i] = head;
        }

        list = list->next;
    }

    return head;
}

//-----------------------------------//
//          PRINT FUNCTIONS          //
//-----------------------------------//

int printFrameHeader(Frame *f)
{
    if (f == NULL)
    {
        printf("\nNone\n");
        return 1;
    }

    printf("\n\nTitle    : %s\n", f->title);
    printf("Height   : %d\n", f->height);
    printf("Width    : %d\n", f->width);
    printf("Channels : %d\n\n", f->channels);

    return 0;
}

int printFrameList(Frame *list)
{
    if (list == NULL)
    {
        return 1;
    }

    while (list != NULL)
    {
        printFrameHeader(list);
        list = list->next;
    }

    return 0;
}
