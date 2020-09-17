/*

0. Напечатать:
   - Как называется П.
   - Что делает П.

   а также:

   -Объясним, что вводить далее

1. Ввести коэфф.лин.ур. ax + b = 0 (a, b)
   Если польз. не ввел правильное число, то повторить ввод

2. Записать уравнение в общем виде
   Разобрать все случаи:
   - Если (a != 0) ===> 1 корень, x = -b / a
   - Если (a == 0) и (b != 0) ===> нет корней
   - Если (a == 0) и (b == 0) ===> \infty корней
   - Иначе: ===> программа ведет себя странно (напечатать)
   - сделать для этого отдельную функцию: SolveSq ()
   - Перевести очень малые числа в удобный для программы вид, функция: IsZero ()

3. Вывести ответ
   - к-во корней
   - корень
   
4. Провести Юнит тесты(пока через if):
   - Сделать отдельную функцию
   - Для проверки отправлять запрос в функцию решающую уравнения
   - функция Sq_Test ()

*/
#include <TXLib.h>
#include <stdio.h>
#include <math.h>

//-----------------------------------------------------------------------------------

int  SolveSq (double a, double b, double c, double* x1, double* x2);
int  Is_Zero (double* a, double* b, double* c);
void Sq_Test();

//-----------------------------------------------------------------------------------

int main ()
    {
    Sq_Test();
    printf("\n"
           "SolveSq - Solves a square equation\n\n"
           "Enter coeffs a, b, c for equation ax^2+bx+c=0. Enter a, b, c: ");

    double a = 0, b = 0, c = 0, n = 0;

    while (n = scanf("%lf %lf %lf", &a, &b, &c) != 3)
        {
        printf("Please enter three numbers and only numbers.   Enter a, b, c: \n");
 /*Вот тут не разобрался как сделать так, чтобы код не выводил printf большое количество раз, через циклы и увеличивание n не получалось. Как можно подправить?*/

        fflush(stdin);
        }

    Is_Zero (&a, &b, &c);

    double x1, x2;
    int nRoots = SolveSq(a, b, c, &x1, &x2);

    if (nRoots ==  0) printf("No roots!\n");
    if (nRoots == -1) printf("Infinity roots!\n");
    if (nRoots ==  1) printf("1 root x = %lg!\n", x1);
    if (nRoots ==  2) printf("2 roots x1 = %lg, x2 = %lg!\n", x1, x2);

    return 0;
    }

//-----------------------------------------------------------------------------------

int SolveSq (double a, double b, double c, double* x1, double* x2)
    {
    if (a == 0)
        {
        if (b == 0)
            {
            if (c == 0)
                {
                return 3;
                }

            if (c != 0)
                {
                return 0;
                }
            }

        if (b != 0)
            {
        *x1 = -c / b;

        return 1;
            }
        }

    if ( a!= 0)
        {
        double D = b * b - 4 * a * c;

        if(D > 0)
            {
            *x1 = (-b - sqrt(D)) / (2 * a);
            *x2 = (-b + sqrt(D)) / (2 * a);

            return 2;
            }

        if(D == 0)
            {
            *x1 = -b / (2 * a);

            return 1;
            }

        if(D < 0)
            {
            return 0;
            }
        }
    }

//------------------------------------------------------------------------

int Is_Zero (double* a, double* b, double* c)
   {
   while((*a < pow(10, -5) && *a > 0) || (*b < pow(10,-5) && *b > 0) || (*c < pow(10, -5) && *c > 0))
        {
        *a = *a * pow(10, 5);
        *b = *b * pow(10, 5);
        *c = *c * pow(10, 5);
        }
   }

//------------------------------------------------------------------------
void Sq_Test ()
    {
    double x1 = 0, x2 = 0, n = 0;

    n = SolveSq (0, 0, 0, &x1, &x2);

    if (n == 3)                           printf("Test 1 ok!\n");
    else                                  printf("Test 1 bad, expected n = 3, but n = %d!\n", n);

    n = SolveSq (1, 2, 1, &x1, &x2);

    if (n == 1 && x1 == -1)               printf("Test 2 ok!\n");
    else                                  printf("Test 2 bad, expected n = 1, x = -1, but n = %d, x = %d!\n", n, x1);

    n = SolveSq (0, 0, 1, &x1, &x2);

    if (n == 0)                           printf("Test 3 ok!\n");
    else                                  printf("Test 3 bad, expected n = 0, but n = %d!\n", n);

    n = SolveSq (0, 1, 1, &x1, &x2);

    if (n == 1 && x1 == -1)               printf("Test 4 ok!\n");
    else                                  printf("Test 4 bad, expected n = 1, x = -1, but n = %d, x = %d!\n", n, x1);

    n = SolveSq (1, 0, -1, &x1, &x2);

    if (n == 2 && x1 == -1 && x2 == 1)    printf("Test 5 ok!\n");
    else                                  printf("Test 5 bad, expected n = 2, x = -1, x2 = 1, but n = %d, x1 = %d!\n, x2 = %d", n, x1, x2);

    n = SolveSq (2, 5, 2, &x1, &x2);

    if (n == 2 && x1 == -2 && x2 == -0,5) printf("Test 6 ok!\n");
    else                                  printf("Test 6 bad, expected n = 2, x = -2, x2 = -0,5, but n = %d, x1 = %d!\n, x2 = %d", n, x1, x2);

    n = SolveSq (1, 1, 1, &x1, &x2);

    if (n == 0)                           printf("Test 7 ok!\n");
    else                                  printf("Test 7 bad, expected n = 0, but n = %d!\n", n);
    
    n = SolveSq (2e-10, 5e-10, 2e-10, &x1, &x2);
   
    if (n == 2 && x1 == -2 && x2 == -0,5) printf("Test 8 ok!\n");
    else                                  printf("Test 8 bad, expected n = 2, x = -2, x2 = -0,5, but n = %d, x1 = %d!\n, x2 = %d", n, x1, x2);
    }
