/**
 * Complement for blob.h
 * Functions for the Blob structure
 */

#include "blob.h"

Blob *createBlob(char *title)
{
    //  Blob pointer
    Blob *b = (Blob *)malloc(sizeof(Blob));

    strcpy(b->title, title);
    b->r = 0;
    b->c = 0;
    b->tam = 0;

    //  Attibute pointers
    b->next = NULL;

    return b;
}

Blob *plagueBlob(Blob *b, Pixel *p, int *input)
{

    //  The rgb of the pixel
    int rgbs[3] = {p->r, p->g, p->b};

    //  Check if pixel inbetween parameters
    if ((p->active == -1) && (compareRGBs(rgbs, input) == 0))
    {
        //  Mark pixel as visited
        p->active = 0;

        //  Sum parameters for further calculations
        b->r += p->y;
        b->c += p->x;
        b->tam += 1;

        //  Go up
        if ((p->up != NULL) && (p->up->active == -1))
        {
            b = plagueBlob(b, p->up, input);
        }
        //  Go left
        if ((p->left != NULL) && (p->left->active == -1))
        {
            b = plagueBlob(b, p->left, input);
        }
        //  Go down
        if ((p->down != NULL) && (p->down->active == -1))
        {
            b = plagueBlob(b, p->down, input);
        }
        //  Go right
        if ((p->right != NULL) && (p->right->active == -1))
        {
            b = plagueBlob(b, p->right, input);
        }
    }

    return b;
}

Blob *beforePlague(Blob *list, Frame *f, int *input)
{
    //  Cycle between all rows of pixels
    for (int i = 0; i < f->height; i++)
    {
        //  Ensure we save the head of the list
        Pixel *head = f->matrix[i];

        //  Cycle throguh each pixel in row
        while (f->matrix[i] != NULL)
        {
            //  Creates a new blob for every pixel
            Blob *newblob = createBlob(f->title);

            //  Start search for blobs in a frame
            newblob = plagueBlob(newblob, f->matrix[i], input);

            //  Attempts to expand blob list with new blob explored from current pixel
            if (newblob->tam <= 1)
                //  Free space if no length
                free(newblob);
            else
            {
                //  Calculate "average" center
                newblob = adjustCenter(newblob);
                //  Insert newly aquired blob to list from highest to lowest
                list = insertOrder(list, newblob);
            }

            //  Advance to next pixel
            f->matrix[i] = f->matrix[i]->right;
        }

        f->matrix[i] = head;
    }

    return list;
}

Blob *scanBlobs(Frame *list, int *input)
{
    //  No frames
    if (list == NULL)
        return NULL;

    //  All blobs in all frames
    Blob *blob_list = NULL;

    //  Find Blobs for each frame
    while (list != NULL)
    {
        printf("Analysing on %s...\n", list->title);
        blob_list = beforePlague(blob_list, list, input);

        //  Find in next frame
        list = list->next;
    }

    return blob_list;
}

Blob *deleteBlobs(Blob *list)
{
    if (list == NULL)
        return NULL;

    while (list != NULL)
    {
        //  Save current so it may be freed
        Blob *ant = list;
        //  Advance to next one
        list = list->next;
        //  Free element
        free(ant);
    }

    return NULL;
}

//-------------------------------------//
//          UTILITY FUNCTIONS          //
//-------------------------------------//

int compareRGBs(int *pixel, int *user)
{
    for (int i = 0; i < 3; i++)
    {
        int min = user[i] - user[3];
        int max = user[i] + user[3];

        //  If it is out of desired range
        if (pixel[i] < min || pixel[i] > max)
            return 1;
    }

    return 0;
}

int printBlobResults(Blob *list)
{
    if (list == NULL)
    {
        printf("No results to be shown\n");
        return 1;
    }

    while (list != NULL)
    {

        printf("\n%s\n(%li, %li) : %d pixels\n", list->title, list->r, list->c, list->tam);
        list = list->next;
    }

    return 0;
}

Blob *adjustCenter(Blob *b)
{
    b->r = b->r / b->tam;
    b->c = b->c / b->tam;

    return b;
}

//-----------------------------------//
//          ORDER FUNCTIONS          //
//-----------------------------------//

Blob *insertFirst(Blob *list, Blob *b)
{
    if (list == NULL)
        return b;
    if (b == NULL)
        return list;

    b->next = list;

    return b;
}

Blob *insertLast(Blob *list, Blob *b)
{
    if (list == NULL)
        return b;
    if (b == NULL)
        return list;

    Blob *head = list;

    while (list != NULL)
    {
        if (list->next == NULL)
        {
            list->next = b;
            break;
        }

        list = list->next;
    }

    return head;
}

Blob *insertOrder(Blob *list, Blob *b)
{
    if (list == NULL)
        return b;
    if (b == NULL)
        return list;

    Blob *head = list;
    Blob *ant = NULL;

    while (list != NULL)
    {
        //  Search for first biggest
        if (b->tam >= list->tam)
            break;

        //  Save element before head
        ant = list;
        list = list->next;
    }

    //  If list reached the end
    if (list == NULL)
        return insertLast(head, b);
    //  If list didnt move
    if (list == head)
        return insertFirst(head, b);

    //  List is somewhere in the middle
    ant->next = b;
    b->next = list;

    return head;
}
