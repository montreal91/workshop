//---------------------------------------------------------------------------
// #include <iostream.h>
// #include <vcl.h>
#pragma hdrstop
#include <stdio.h>
// #include <windows.h>
#include <time.h>
#include <stdlib.h>
#include <math.h>
// #include <list>
// #include <typeinfo>
// #include <conio>
// #include <clocale>
//---------------------------------------------------------------------------

#pragma argsused
#define NINTS 25
#define WRAP 10

struct Int {
    int data;
    struct Int *next;
};



/* intNodePtr initializeList(const int * string); */
// /
typedef struct Int intNode;
typedef intNode *intNodePtr;

void insert(intNodePtr *s, int x)
{

    intNodePtr neww;
    intNodePtr previous;
    intNodePtr current;

    neww = (struct Int*)malloc(sizeof(intNode));
    if (neww != NULL) {

    neww->data = x;
    neww->next = NULL;
    previous = NULL;
    current = *s;


    while (current != NULL && x > current->data) {
        previous = current;
        current = current->next;
    }

    if (previous == NULL) {
        neww->next = *s;    /* *s is NULL */
        *s = neww;      /* set head to point to new */
    } else {
        previous->next = neww;
        neww->next = current;
    }

    } else {
    printf("%d not inserted. No memory available.\n", x);
    }

}

int doSum(intNodePtr head)
{
    intNodePtr current = head;
    int sum = 0;

    while (current->next != NULL) {
    sum += current->data;
    current = current->next;
    }
    /* add the last element */
    sum += current->data;

    return sum;
}

void printList(intNodePtr head)
{

    intNodePtr current = head;
    int i = 1;
    printf("Number list:\n");
    while (current != NULL) {
    printf("%3d%s", current->data, i % WRAP == 0 ? "\n" : " ");
    current = current->next;
    i++;
    }
    printf("\n");

}

int dice(void)
{
    return (rand() % 101);
}


int main()
{
    int integers[NINTS] = { 0 };
    intNodePtr list1 = NULL;
    int i, sum = 0;

    srand(time(NULL));

    printf("Unsorted data:\n");
    /* initializing the array */
    for (i = 0; i < NINTS; i++) {
    printf("%3d%s", integers[i] =
           dice(), (i + 1) % WRAP == 0 ? "\n" : " ");
    }
    printf("\n");

    /* initialize the list */
    for (i = 0; i < NINTS; i++) {
    insert(&list1, integers[i]);
    }
    printList(list1);

    /* stats */
    sum = doSum(list1);
    printf("Sum = %d\nMean = %.2f\n", sum, ((float) sum) / NINTS);

    return 0;
}



