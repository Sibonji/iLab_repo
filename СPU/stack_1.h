typedef int Data;
typedef int Canary;

typedef struct
{
    Canary * canary_start;

    int hash;

    int capacity;             //Âìåñòèìîñòü ñòýêà (â ôóíêöèè recalloc_stack ñïîëüçóåòñÿ, êàê íûíåøíåå
    int ptr;                  //êîëè÷åñòâî ïåðåìåííûõ òèïà Data

    Data * data;

    Canary * canary_end;
} Stack;

/////////////////////////////////////////////////////////////////////////////////////////

const Data empty_num = 5051;
const Canary canary  = 1357911;

//////////////////////////////////////////////////////////////////////////////////////////


int    pop               (Stack * my_st);
int    dump              (Stack * my_st);
void   destroy           (Stack * my_st);
void * calloc_stack      (Stack * my_st);
void * recalloc_stack    (Stack * my_st);
int    isok_adr          (Stack * my_st);
int    check_stack       (Stack * my_st);
int    count_hash        (Stack * my_st);
int    push              (Stack * my_st, int num);
int    construct         (Stack * my_st, int num);
int    cmpneq            (Stack * my_st, int current, int standart);
int    cmpeq             (Stack * my_st, int current, int standart);
int    is_empty          (Stack * my_st);

//////////////////////////////////////////////////////////////////////////////////////////

int construct         (Stack * my_st, int num)
{
    my_st -> ptr          = 0;
    my_st -> hash         = 0;
    my_st -> capacity     = num;
    my_st -> canary_start = NULL;
    my_st -> canary_end   = NULL;
    my_st -> data         = (Data *) calloc_stack (my_st);

    if (my_st -> data == NULL)
    {
        printf ("A critical programm error has occured.\nFile:%s\nLine: %d\n", __FILE__, __LINE__);

        exit (3);
    }

    int  i = 0;
    for (i = 0; i < my_st -> capacity; i++)
    {
        my_st -> data[i] = empty_num;
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

int is_empty          (Stack * my_st){
    if (check_stack (my_st) == 1)
    {
        printf ("A critical programm error has occured.\nFile:%s\nLine: %d\n", __FILE__, __LINE__);

        destroy (my_st);

        exit (3);
    }

    if (my_st -> ptr == 0) return 1;
    else return 0;
}

//////////////////////////////////////////////////////////////////////////////////////////

int push              (Stack * my_st, int num)
{
    if (check_stack (my_st) == 1)
    {
        printf ("A critical programm error has occured.\nFile:%s\nLine: %d\n", __FILE__, __LINE__);

        destroy (my_st);

        exit (3);
    }

    if (my_st -> ptr + 1 > my_st -> capacity)
    {
        if ((my_st -> data = (Data *) recalloc_stack (my_st)) == NULL)
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

int dump              (Stack * my_st)
{
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

int pop               (Stack * my_st)
{
    if (check_stack (my_st) == 1)
    {
        printf ("A critical programm error has occured.\nFile:%s\nLine: %d\n", __FILE__, __LINE__);

        destroy (my_st);

        exit (3);
    }

    (my_st -> data)[--my_st -> ptr] =  empty_num;

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

void destroy           (Stack * my_st)
{
    if (my_st -> data != NULL)         free (my_st -> data);
    if (my_st -> canary_start != NULL) free (my_st -> canary_start);
    if (my_st -> canary_end != NULL)   free (my_st -> canary_end);

    return;
}

//////////////////////////////////////////////////////////////////////////////////////////

void * calloc_stack   (Stack * my_st)
{
    char * ptr = NULL;

    ptr        = (char *) calloc (1, 2 * sizeof (Canary) + (my_st -> capacity) * sizeof (Data));

    if (ptr == NULL)
    {
        return NULL;
    }

    my_st -> canary_start     = (Canary *) ptr;

    my_st -> canary_end       = (Canary *) (ptr + (my_st -> capacity) * sizeof (Data) + sizeof (Canary));

    * (my_st -> canary_start) = 1357911;

    * (my_st -> canary_end)   = 1357911;

    return (ptr + sizeof (Canary));
}

//////////////////////////////////////////////////////////////////////////////////////////

void * recalloc_stack (Stack * my_st)
{
    if (check_stack (my_st) == 1)
    {
        printf ("A critical programm error has occured.\nFile:%s\nLine: %d\n", __FILE__, __LINE__);

        destroy (my_st);

        exit (3);
    }

    ++my_st -> capacity;

    char * ptr = NULL;

    ptr = (char *) realloc (my_st -> canary_start, 2 * sizeof (Canary) + my_st -> capacity * sizeof (Data));

    if (ptr == NULL)
    {
        printf ("A critical programm error has occured.\nFile:%s\nLine: %d\n", __FILE__, __LINE__);

        dump (my_st);
        destroy (my_st);

        return NULL;
    }

    my_st -> canary_start = (Canary *) ptr;
    my_st -> canary_end   = (Canary *) (ptr + my_st -> capacity * sizeof (Data) + sizeof (Canary));

    * (my_st -> canary_end) = 1357911;

    if ((isok_adr (my_st)) == 0)
    {
        printf ("A critical programm error has occured.\nFile:%s\nLine: %d\n", __FILE__, __LINE__);

        destroy (my_st);

        return NULL;
    }

    my_st -> data = (Data *) (ptr + sizeof (Canary));



    return (ptr + sizeof (Canary));
}

//////////////////////////////////////////////////////////////////////////////////////////

int isok_adr          (Stack * my_st)
{
    unsigned int difference = 0;

    difference = (int) (my_st -> canary_end) - (int) (my_st -> canary_start);

    if (difference == (my_st -> capacity * (sizeof (Data)) + sizeof (Canary)))
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

//////////////////////////////////////////////////////////////////////////////////////////

int check_stack       (Stack * my_st)
{
    if (cmpneq (my_st, * my_st -> canary_start, canary) == 1) return 1;
    if (cmpneq (my_st, * my_st -> canary_end  , canary) == 1) return 1;

    if (my_st -> hash != count_hash (my_st)) return 1;

    int i  = 0;
    for (i = 0;                i < my_st -> ptr;     i++)
    {
        if (cmpeq  (my_st, my_st -> data[i], empty_num) == 1) return 1;
    }

    for (i = my_st -> ptr; i < my_st -> capacity; i++)
    {
        if (cmpneq (my_st, my_st -> data[i], empty_num) == 1) return 1;
    }

    return 0;
}

//////////////////////////////////////////////////////////////////////////////////////////

int cmpeq             (Stack * my_st, int current, int standart)
{
    if (current == standart) return 1;


    return 0;
}

//////////////////////////////////////////////////////////////////////////////////////////

int cmpneq            (Stack * my_st, int current, int standart)
{
    if (current != standart) return 1;


    return 0;
}

//////////////////////////////////////////////////////////////////////////////////////////

int count_hash (Stack * my_st)
{
    int hash = 0;
    /*int param = 0;

    int  i = 0;
    for (i = 0; i < my_st -> capacity; i++)
    {
        param = my_st -> data[i] >> 1;

        hash += param;

        hash = hash >> 1;
    }

    param = * my_st -> canary_start >> 1;

    hash += param;
    hash = hash >> 1;

    param = * my_st -> canary_start >> 1;

    hash += param;
    hash = hash >> 1;

    param = my_st -> ptr >> 1;

    hash += param;
    hash = hash >> 1;

    param = my_st -> capacity >> 1;

    hash += param;
    hash = hash >> 1;*/

    return hash;
}