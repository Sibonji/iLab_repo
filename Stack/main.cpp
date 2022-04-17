#include "Types.h" //Библиотека, с обьявлениями функций нужных для работы стэка с различными типами данных

#define TYPE float
#include "Stack.h"
#undef TYPE

#define TYPE int
#include "Stack.h"
#undef TYPE

#define TYPE double
#include "Stack.h"
#undef TYPE

#define TYPE char
#include "Stack.h"
#undef TYPE

int main() {
    Stack_float stk;

    for (int i = 0; i < 10; i++) stk.push (346);

    stk.dump ();

    return 0;
}
