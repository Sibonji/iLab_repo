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

3. Вывести ответ
   - к-во корней
   - корень

   Контакты:
   - Раффаэль Делла Пиетра
   - Гриша Степанов

*/

#include <stdio.h>
#include <TXLib.h>
#include <math.h>

int main()
    {
    printf ("\n"
            "SolveLin - Solves a linear equation\n\n"
            "Enter coeffs a, b for equation ax + b = 0. Enter a: ");

    double a = 0;
    scanf ("%lg", &a);

    printf ("                                           Enter b: ");

    double b = 0;
    scanf ("%lg", &b);

    if (a != 0)
        {
        double x = -b / a;  // +-----+
                            // V
        printf ("1 root, x = %lg\n", x);
        }

    if (a == 0)
        {
        if (b == 0)
            {
            printf("\\infty roots!\n");
            }

        if (b != 0)
            {
            printf("No roots!\n");
            }
        }

    return 0;
    }
