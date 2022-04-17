//TODO:
// - сделать класс Stack вместо структуры
// - сделать переменные стэка "приватными"
// - переписать обьявления функций для таких переменых
// - DUMP: data, var_name, type, pointer, pointer to data, hash, canaries DONE
// - Сделать конструктор по умолчанию

#include <stdio.h>
#include  <stdlib.h>
#include <mem.h>

#define CAT(x, y) x##_##y
#define TEMPLATE(x, y) CAT(x, y)

class TEMPLATE (Stack, TYPE) {
    private:

    Canary canary_stk_start;
    char hash;
    int capacity;             //Вместимость стэка (в функции recalloc_stack спользуется, как нынешнее
    int ptr;                  //количество переменных типа Data

    Canary * canary_data_start;
    TYPE * data;
    Canary * canary_data_end;

    Canary canary_stk_end;

    int    check_stack       ();
    char    count_hash        ();

    public:

    TEMPLATE (Stack, TYPE) ();
    TEMPLATE (Stack, TYPE) (int quant);
    ~TEMPLATE (Stack, TYPE) ();
    TEMPLATE (Stack, TYPE) (const TEMPLATE(Stack, TYPE)& obj);
    TYPE    pop               ();
    int    dump              ();
    void * calloc_stack      ();
    void * recalloc_stack    ();
    int    isok_adr          ();
    int    push              (TYPE num);
    int    cmpneq            (TYPE current, TYPE standart);
    int    cmpeq             (TYPE current, TYPE standart);
};

//////////////////////////////////////////////////////////////////////////////////////////
TEMPLATE (Stack, TYPE)::TEMPLATE (Stack, TYPE)         (int quant) {
    ptr          = 0;
    hash         = 0;
    capacity     = quant;
    canary_data_start = nullptr;
    canary_data_end   = nullptr;
    data         = (TYPE *) calloc_stack ();
    canary_stk_end = perfect_canary;
    canary_stk_start = perfect_canary;

    if (data == nullptr)
    {
        print_err;

        exit (3);
    }

    int  i = 0;
    for (i = 0; i < capacity; i++)
    {
        data[i] = TEMPLATE(poison, TYPE);
    }

    hash = count_hash ();

    if (check_stack () == 1)
    {
        print_err;

        exit (3);
    }
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////

TEMPLATE (Stack, TYPE)::TEMPLATE (Stack, TYPE)         () {
    int quant = 1;

    ptr          = 0;
    hash         = 0;
    capacity     = quant;
    canary_data_start = nullptr;
    canary_data_end   = nullptr;
    data         = (TYPE *) calloc_stack ();
    canary_stk_end = perfect_canary;
    canary_stk_start = perfect_canary;

    if (data == nullptr)
    {
        print_err;

        exit (3);
    }

    int  i = 0;
    for (i = 0; i < capacity; i++)
    {
        data[i] = TEMPLATE(poison, TYPE);
    }

    hash = count_hash ();

    if (check_stack () == 1)
    {
        print_err;

        exit (3);
    }
}

//////////////////////////////////////////////////////////////////////////////////////////

TEMPLATE (Stack, TYPE)::TEMPLATE (Stack, TYPE) (TEMPLATE(Stack, TYPE) const& obj){
    int quant = 1;

    ptr          = 0;
    hash         = 0;
    capacity     = quant;
    canary_data_start = nullptr;
    canary_data_end   = nullptr;
    data         = (TYPE *) calloc_stack ();
    canary_stk_end = perfect_canary;
    canary_stk_start = perfect_canary;

    if (data == nullptr)
    {
        print_err;

        exit (3);
    }

    int  i = 0;
    for (i = 0; i < capacity; i++)
    {
        data[i] = TEMPLATE(poison, TYPE);
    }

    memcpy (data, obj.data, capacity);

    hash = count_hash ();
}

//////////////////////////////////////////////////////////////////////////////////////////

TEMPLATE (Stack, TYPE)::~TEMPLATE(Stack, TYPE) () {
    if (canary_data_start != nullptr) free (canary_data_start);
}

//////////////////////////////////////////////////////////////////////////////////////////

int TEMPLATE (Stack, TYPE)::push              (TYPE num) {

    if (check_stack () == 1)
    {
        //print_err;

        exit (3);
    }

    if (ptr + 1 > capacity)
    {
        if ((data = (TYPE *) recalloc_stack ()) == nullptr)
        {
            exit (3);
        }
    }

    data[ptr++] = num;

    hash = count_hash ();

    if (check_stack () == 1)
    {
        //print_err;

        exit (3);
    }

    return 0;
}

//////////////////////////////////////////////////////////////////////////////////////////

int TEMPLATE (Stack, TYPE)::dump              () {

    if (check_stack () == 1)
    {
        //print_err;

        exit (3);
    }

    int i   = 0;
    int num = 0;

    TEMPLATE(Print, TYPE) ();

    printf ("Data var name: %s\n", getname(data));

    printf ("Data capacity: %d\n"
            "Pointer to data: %p\n"
            "Data:\n", capacity, data);

    for(i = 0; i < capacity; i++)
    {
        TEMPLATE(Print, TYPE) ((data)[i]);
    }

    printf ("\n\nCanary type: int\n\n");
    printf ("Stack canary_1 pointer: %p, stack canary_2 pointer: %p\n"
            "Data canary_data_start pointer: %p, data canary_data_end pointer: %p\n", \
            &canary_stk_start, &canary_stk_end, canary_data_start, canary_data_end);
    printf ("\nStack canary_1: %d, stack canary_2: %d\n"
            "Data canary_data_start: %d, data canary_data_end: %d\n", canary_stk_start, canary_stk_end, * canary_data_start, * canary_data_end);
    printf ("\nHash: %c\n", hash);

    printf ("\n");

    hash = count_hash ();

    if (check_stack () == 1)
    {
        //print_err;

        exit (3);
    }

    return 0;
}

//////////////////////////////////////////////////////////////////////////////////////////

TYPE TEMPLATE (Stack, TYPE)::pop               () {
    if (check_stack () == 1)
    {
        //print_err;

        exit (3);
    }

    TYPE value = data[--ptr];

    data[ptr] =  TEMPLATE(poison, TYPE);

    hash = count_hash ();

    if (check_stack () == 1)
    {
        //print_err;

        exit (3);
    }

    return value;
}

//////////////////////////////////////////////////////////////////////////////////////////

void * TEMPLATE (Stack, TYPE)::calloc_stack   () {

    char * pointer = nullptr;

    pointer        = (char *) calloc (1, 2 * sizeof (Canary) + (capacity) * sizeof (TYPE));

    if (pointer == nullptr)
    {
        return nullptr;
    }

    canary_data_start     = (Canary *) pointer;

    canary_data_end       = (Canary *) (pointer + (capacity) * sizeof (TYPE) + sizeof (Canary));

    * (canary_data_start) = perfect_canary;

    * (canary_data_end)   = perfect_canary;

    return (pointer + sizeof (Canary));
}

//////////////////////////////////////////////////////////////////////////////////////////

void * TEMPLATE (Stack, TYPE)::recalloc_stack () {

    if (check_stack () == 1)
    {
        //print_err;

        exit (3);
    }

    ++capacity;

    char * pointer = nullptr;

    pointer = (char *) realloc (canary_data_start, 2 * sizeof (Canary) + capacity * sizeof (TYPE));

    if (pointer == nullptr)
    {
        //print_err;

        dump ();

        return nullptr;
    }

    canary_data_start = (Canary *) pointer;
    canary_data_end   = (Canary *) (pointer + capacity * sizeof (TYPE) + sizeof (Canary));

    * (canary_data_end) = perfect_canary;

    if ((isok_adr ()) != 0)
    {
        print_err;

        return nullptr;
    }

    data = (TYPE *) (pointer + sizeof (Canary));

    return (pointer + sizeof (Canary));
}

//////////////////////////////////////////////////////////////////////////////////////////

int TEMPLATE (Stack, TYPE)::isok_adr          () {

    unsigned int difference = 0;

    difference = (int) (canary_data_end) - (int) (canary_data_start);

    if (difference == (capacity * (sizeof (TYPE)) + sizeof (Canary)))
    {
        return 0;
    }
    else
    {
        return 1;
    }
}

//////////////////////////////////////////////////////////////////////////////////////////

int TEMPLATE (Stack, TYPE)::check_stack       () {
    if (canary_stk_start != perfect_canary) {
        print_err;
        return 1;
    }
    if (canary_stk_end != perfect_canary) {
        print_err;
        return 1;
    }
    if (* canary_data_start != perfect_canary) {
        print_err;
        return 1;
    }
    if (* canary_data_end  != perfect_canary) {
        print_err;
        return 1;
    }

    if (hash != count_hash ()) {
        print_err;
        return 1;
    }

    if (isok_adr() != 0)
    {
        print_err;
        return 1;
    }

    for (int i = 0; i < ptr; i++)
    {
        if (cmpeq  (data[i], TEMPLATE(poison, TYPE)) == 1) {
            print_err;
            return 1;
        }
    }

    for (int i = ptr; i < capacity; i++)
    {
        if (cmpneq (data[i], TEMPLATE(poison, TYPE)) == 1) {
            print_err;
            return 1;
        }
    }

    return 0;
}

//////////////////////////////////////////////////////////////////////////////////////////

int TEMPLATE (Stack, TYPE)::cmpeq             (TYPE current, TYPE standart) {

    if (current == standart) return 1;

    return 0;
}

//////////////////////////////////////////////////////////////////////////////////////////

int TEMPLATE (Stack, TYPE)::cmpneq            (TYPE current, TYPE standart)
{
    if (current != standart) return 1;

    return 0;
}

//////////////////////////////////////////////////////////////////////////////////////////

char TEMPLATE (Stack, TYPE)::count_hash        () {
    int i = 0;

    char _hash = '\0';
    char param = '\0';

    for (i = 0; i < capacity * sizeof (TYPE); i++)
    {
        _hash += ((char *) data)[i];
        _hash >> 1;
    }

    for (i = 0; i < sizeof (Canary); i++)
    {
        _hash += ((char *) canary_data_start)[i];
        _hash >> 1;
        _hash += ((char *) canary_data_end)[i];
        _hash >> 1;
        _hash += ((char *) &canary_stk_start)[i];
        _hash >> 1;
        _hash += ((char *) &canary_stk_end)[i];
        _hash >> 1;
    }
    for (i = 0; i < sizeof (int); i++)
    {
        _hash += ((char *) &ptr)[i];
        _hash >> 1;
        _hash += ((char *) &capacity)[i];
        _hash >> 1;
    }

    return _hash;
}