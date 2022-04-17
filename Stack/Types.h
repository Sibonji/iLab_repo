#include <stdlib.h>
#include <stdio.h>

#define print_err printf ("A critical programm error has occured.\nFile:%s\nLine: %d\n", __FILE__, __LINE__);

#define getname(var) #var
#define Canary int

void Print_int (int num);
void Print_float (float num);
void Print_double (double num);
void Print_char (char num);

#define poison_int 5051
#define poison_char '\0'
#define poison_float 5051.5
#define poison_double 5051.5
#define perfect_canary 1981


void Print_int (int num) {
    printf ("%d ", num);

    return;
}

void Print_float (float num) {
    printf ("%lf ", num);

    return;
}

void Print_double (double num) {
    printf ("%f ", num);

    return;
}

void Print_char (char num) {
    printf ("%c ", num);

    return;
}

void Print_int () {
    printf ("Data type: int\n");

    return;
}

void Print_float () {
    printf ("Data type: float\n");

    return;
}

void Print_double () {
    printf ("Data type: double\n");

    return;
}

void Print_char () {
    printf ("Data type: char\n");

    return;
}
