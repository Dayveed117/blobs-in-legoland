#include "pixel.h"
#include "frame.h"
#include "blob.h"
#include "io.h"

#define MINITEST "../files/minitest.txt"
#define MINITEST2 "../files/minitest2.txt"
#define MINITEST3 "../files/minitest3.txt"
#define REALFILE "../files/imgs.txt"

int main(int argc, char *argv[])
{

    //  Variables
    char title[50];
    int lines, columns, channels;
    int *input;
    FILE *fp;

    //  Frame list
    Frame *f_list = NULL;
    //  Blob list
    Blob *b_list = NULL;

    //----------------------------------//
    //          FILE SELECTION          //
    //----------------------------------//

    int choice = chooseFile();

    switch (choice)
    {
    case 0:
        quit();
        break;

    case 1:
        fp = openFile(MINITEST);
        printf("Reading data from %s\n", MINITEST);
        break;

    case 2:
        fp = openFile(MINITEST2);
        printf("Reading data from %s\n", MINITEST2);
        break;

    case 3:
        fp = openFile(MINITEST3);
        printf("Reading data from %s\n", MINITEST3);
        break;

    case 4:
        fp = openFile(REALFILE);
        printf("Reading data from %s\n", REALFILE);
        break;

    default:
        printf("Invalid option, number 1 by default.\n");
        fp = openFile(MINITEST);
        printf("Reading data from %s\n", MINITEST);
        break;
    }

    //-----------------------------------//
    //          STORE FILE INFO          //
    //-----------------------------------//

    //  Read frame by frame
    while (fscanf(fp, " %s", title) != EOF)
    {
        //  Read first row from file
        fscanf(fp, " %d %d %d", &lines, &columns, &channels);

        //  Create an array of lists
        Pixel **p_list = (Pixel **)malloc(lines * sizeof(Pixel));

        //  Iterate over (frame height x frame width) pixels
        for (int y = 0; y < lines; y++)
        {
            Pixel *pixelabove = NULL;
            //  Find pixel directly above if not first line
            if (y > 0)
                pixelabove = p_list[y - 1];

            for (int x = 0; x < columns; x++)
            {
                //  Read rgb
                int rgb[3];
                fscanf(fp, " %d %d %d", &rgb[0], &rgb[1], &rgb[2]);

                //  Create new pixel structure
                Pixel *p = createPixel(rgb, x + 1, y + 1, pixelabove);

                //  Advance pixel above by one
                pixelabove = advanceRight(pixelabove);

                //  Insert pixel in row
                p_list[y] = insertPixel(p_list[y], p);

            } //  end of row y

        } //  end frame

        //  Frame creation and insertion
        Frame *f = createFrame(title, lines, columns, channels, p_list);
        f_list = insertFrame(f_list, f);

        printFrameHeader(f);
    }

    //----------------------------------//
    //          BLOB SEARCHING          //
    //----------------------------------//

    while (1)
    {
        int choice = menu();

        switch (choice)
        {
        case 0:
            quit();
            break;
        case 1:
            info();
            break;
        case 2:
            input = userPrompt(input);
            b_list = scanBlobs(f_list, input);
            f_list = resetFrames(f_list);
            printBlobResults(b_list);
            deleteBlobs(b_list);
            getchar();
            break;

        default:
            printf("\nInvalid option\n");
            break;
        }
    }

    return 0;
}
