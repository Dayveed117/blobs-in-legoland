#include "blob.c"

int main()
{
    Blob *b1 = createBlob("blob1");
    b1->r = 1;
    b1->c = 1;
    b1->tam = 1;

    Blob *b2 = createBlob("blob2");
    b2->r = 2;
    b2->c = 2;
    b2->tam = 2;

    Blob *b3 = createBlob("blob3");
    b3->r = 3;
    b3->c = 3;
    b3->tam = 3;

    Blob *b4 = createBlob("blob4");
    b4->r = 4;
    b4->c = 4;
    b4->tam = 4;

    Blob *b5 = createBlob("blob5");
    b5->r = 5;
    b5->c = 5;
    b5->tam = 5;

    Blob *b6 = createBlob("blob6");
    b6->r = 6;
    b6->c = 6;
    b6->tam = 6;

    Blob *b62 = createBlob("blob6_2");
    b62->r = 6;
    b62->c = 6;
    b62->tam = 6;

    Blob *b7 = createBlob("blob7");
    b7->r = 7;
    b7->c = 7;
    b7->tam = 7;

    Blob *list = NULL;

    list = insertOrder(list, b2);
    list = insertOrder(list, b7);
    list = insertOrder(list, b6);
    list = insertOrder(list, b1);
    list = insertOrder(list, b62);
    list = insertOrder(list, b3);
    list = insertOrder(list, b4);
    list = insertOrder(list, b5);

    printBlobResults(list);
}
