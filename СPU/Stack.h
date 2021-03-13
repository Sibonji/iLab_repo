//TODO:
// - сделать класс Stack вместо структуры
// - сделать переменные стэка "приватными"
// - переписать обьявления функций для таких переменых

#include <stdio.h>
#include <stdlib.h>

typedef int Canary;

#define CAT(x, y) x##_##y
#define TEMPLATE(x, y) CAT(x, y)

struct TEMPLATE (Stack, TYPE) {
    int hash;

    int capacity;             //Вместимость стэка (в функции recalloc_stack спользуется, как нынешнее
    int ptr;                  //количество переменных типа Data

    Canary * canary_start;

    TYPE * data;

    Canary * canary_end;
};

//////////////////////////////////////////////////////////////////////////////////////////


int    pop               (TEMPLATE (Stack, TYPE) * my_st);
int    dump              (TEMPLATE (Stack, TYPE) * my_st);
void   destroy           (TEMPLATE (Stack, TYPE) * my_st);
void * calloc_stack      (TEMPLATE (Stack, TYPE) * my_st);
void * recalloc_stack    (TEMPLATE (Stack, TYPE) * my_st);
int    isok_adr          (TEMPLATE (Stack, TYPE) * my_st);
int    check_stack       (TEMPLATE (Stack, TYPE) * my_st);
int    count_hash        (TEMPLATE (Stack, TYPE) * my_st);
int    push              (TEMPLATE (Stack, TYPE) * my_st, int num);
int    construct         (TEMPLATE (Stack, TYPE) * my_st, int num);
int    cmpneq            (TEMPLATE (Stack, TYPE) * my_st, int current, int standart);
int    cmpeq             (TEMPLATE (Stack, TYPE) * my_st, int current, int standart);

//////////////////////////////////////////////////////////////////////////////////////////

int construct         (TEMPLATE (Stack, TYPE) * my_st, int num) {
    my_st -> ptr          = 0;
    my_st -> hash         = 0;
    my_st -> capacity     = num;
    my_st -> canary_start = nullptr;
    my_st -> canary_end   = nullptr;
    my_st -> data         = (TYPE *) calloc_stack (my_st);

    if (my_st -> data == nullptr)
    {
        printf ("A critical programm error has occured.\nFile:%s\nLine: %d\n", __FILE__, __LINE__);

        exit (3);
    }

    int  i = 0;
    for (i = 0; i < my_st -> capacity; i++)
    {
        my_st -> data[i] = 5051;
    }

    my_st -> hash = count_hash (my_st);

    if (check_stack (my_st) == 1)
    {
        printf ("A critical programm error has occured.\nFile:%s\nLine: %d\n", __FILE__, __LINE__);

        destroy (my_st);

        exit (3);
    }

    return 0;
}

//////////////////////////////////////////////////////////////////////////////////////////

int push              (TEMPLATE (Stack, TYPE) * my_st, int num) {

    if (check_stack (my_st) == 1)
    {
        printf ("A critical programm error has occured.\nFile:%s\nLine: %d\n", __FILE__, __LINE__);

        destroy (my_st);

        exit (3);
    }

    if (my_st -> ptr + 1 > my_st -> capacity)
    {
        if ((my_st -> data = (TYPE *) recalloc_stack (my_st)) == nullptr)
        {
            exit (3);
        }
    }

    my_st -> data[my_st -> ptr++] = num;

    my_st -> hash = count_hash (my_st);

    if (check_stack (my_st) == 1)
    {
        printf ("A critical programm error has occured.\nFile:%s\nLine: %d\n", __FILE__, __LINE__);

        destroy (my_st);

        exit (3);
    }

    return 0;
}

//////////////////////////////////////////////////////////////////////////////////////////

int dump              (TEMPLATE (Stack, TYPE) * my_st) {

    if (check_stack (my_st) == 1)
    {
        printf ("A critical programm error has occured.\nFile:%s\nLine: %d\n", __FILE__, __LINE__);

        destroy (my_st);

        exit (3);
    }

    int i   = 0;
    int num = 0;

    for(i = 0; i < my_st -> capacity; i++)
    {
        num = (int) (my_st -> data)[i];

        printf ("%d ", num);
    }

    printf ("\n");

    my_st -> hash = count_hash (my_st);

    if (check_stack (my_st) == 1)
    {
        printf ("A critical programm error has occured.\nFile:%s\nLine: %d\n", __FILE__, __LINE__);

        destroy (my_st);

        exit (3);
    }

    return 0;
}

//////////////////////////////////////////////////////////////////////////////////////////

int pop               (TEMPLATE (Stack, TYPE) * my_st) {

    if (check_stack (my_st) == 1)
    {
        printf ("A critical programm error has occured.\nFile:%s\nLine: %d\n", __FILE__, __LINE__);

        destroy (my_st);

        exit (3);
    }

    (my_st -> data)[--my_st -> ptr] =  5051;

    my_st -> hash = count_hash (my_st);

    if (check_stack (my_st) == 1)
    {
        printf ("A critical programm error has occured.\nFile:%s\nLine: %d\n", __FILE__, __LINE__);

        destroy (my_st);

        exit (3);
    }

    return 1;
}

//////////////////////////////////////////////////////////////////////////////////////////

void destroy           (TEMPLATE (Stack, TYPE) * my_st) {

    if (my_st -> data != nullptr)         free (my_st -> data);
    if (my_st -> canary_start != nullptr) free (my_st -> canary_start);
    if (my_st -> canary_end != nullptr)   free (my_st -> canary_end);

    return;
}

//////////////////////////////////////////////////////////////////////////////////////////

void * calloc_stack   (TEMPLATE (Stack, TYPE) * my_st) {

    char * ptr = nullptr;

    ptr        = (char *) calloc (1, 2 * sizeof (Canary) + (my_st -> capacity) * sizeof (TYPE));

    if (ptr == nullptr)
    {
        return nullptr;
    }

    my_st -> canary_start     = (Canary *) ptr;

    my_st -> canary_end       = (Canary *) (ptr + (my_st -> capacity) * sizeof (TYPE) + sizeof (Canary));

    * (my_st -> canary_start) = 1357911;

    * (my_st -> canary_end)   = 1357911;

    return (ptr + sizeof (Canary));
}

//////////////////////////////////////////////////////////////////////////////////////////

void * recalloc_stack (TEMPLATE (Stack, TYPE) * my_st) {

    if (check_stack (my_st) == 1)
    {
        printf ("A critical programm error has occured.\nFile:%s\nLine: %d\n", __FILE__, __LINE__);

        destroy (my_st);

        exit (3);
    }

    ++my_st -> capacity;

    char * ptr = nullptr;

    ptr = (char *) realloc (my_st -> canary_start, 2 * sizeof (Canary) + my_st -> capacity * sizeof (TYPE));

    if (ptr == nullptr)
    {
        printf ("A critical programm error has occured.\nFile:%s\nLine: %d\n", __FILE__, __LINE__);

        dump (my_st);
        destroy (my_st);

        return nullptr;
    }

    my_st -> canary_start = (Canary *) ptr;
    my_st -> canary_end   = (Canary *) (ptr + my_st -> capacity * sizeof (TYPE) + sizeof (Canary));

    * (my_st -> canary_end) = 1357911;

    if ((isok_adr (my_st)) == 0)
    {
        printf ("A critical programm error has occured.\nFile:%s\nLine: %d\n", __FILE__, __LINE__);

        destroy (my_st);

        return nullptr;
    }

    my_st -> data = (TYPE *) (ptr + sizeof (Canary));



    return (ptr + sizeof (Canary));
}

//////////////////////////////////////////////////////////////////////////////////////////

int isok_adr          (TEMPLATE (Stack, TYPE) * my_st) {

    unsigned int difference = 0;

    difference = (int) (my_st -> canary_end) - (int) (my_st -> canary_start);

    if (difference == (my_st -> capacity * (sizeof (TYPE)) + sizeof (Canary)))
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

//////////////////////////////////////////////////////////////////////////////////////////

int check_stack       (TEMPLATE (Stack, TYPE) * my_st) {

    if (cmpneq (my_st, * my_st -> canary_start, 11357) == 1) return 1;
    if (cmpneq (my_st, * my_st -> canary_end  , 11357) == 1) return 1;

    if (my_st -> hash != count_hash (my_st)) return 1;

    int i  = 0;
    for (i = 0;                i < my_st -> ptr;     i++)
    {
        if (cmpeq  (my_st, my_st -> data[i], 5051) == 1) return 1;
    }

    for (i = my_st -> ptr; i < my_st -> capacity; i++)
    {
        if (cmpneq (my_st, my_st -> data[i], 5051) == 1) return 1;
    }

    return 0;
}

//////////////////////////////////////////////////////////////////////////////////////////

int cmpeq             (TEMPLATE (Stack, TYPE) * my_st, int current, int standart) {

    if (current == standart) return 1;

    return 0;
}

//////////////////////////////////////////////////////////////////////////////////////////

int cmpneq            (TEMPLATE (Stack, TYPE) * my_st, int current, int standart)
{
    if (current != standart) return 1;

    return 0;
}

//////////////////////////////////////////////////////////////////////////////////////////

int count_hash (TEMPLATE (Stack, TYPE) * my_st) {

    char hash = 0;
    char param = 0;

    int  i = 0;
    for (i = 0; i < my_st -> capacity; i++)
    {
        param = (char) my_st -> data[i] >> 1;

        hash += param;

        hash = hash >> 1;
    }

    param = * (char *) my_st -> canary_start >> 1;

    hash += param;
    hash = hash >> 1;

    param =  * (char *) my_st -> canary_start >> 1;

    hash += param;
    hash = hash >> 1;

    param = my_st -> ptr >> 1;

    hash += param;
    hash = hash >> 1;

    param = (char) my_st -> capacity >> 1;

    hash += param;
    hash = hash >> 1;

    return hash;
}
