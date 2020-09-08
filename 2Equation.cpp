/*

0. ����������:
   - ��� ���������� ���������
   - ��� ������

   - ���������, ��� ������� �����

1. ������ ������������ ����������� ��������� ax^2+bx+c=0 (a, b, c)

2. ��������� ��� ������:
   - ���� a == 0 & b == 0 & c == 0 ===> \infty ������
   - ���� a == 0 & b == 0 & c != 0 ===> ������ ���
   - ���� a == 0 & b != 0 ===> ������ 1, x = -c / b
   - ���� a != 0 ===> ������ ������������:
        - D = b^2 - 4ac:
            - ���� D > 0 ===> ������ 2, x = (-b + sqrt(D)) / 2a; x = (-b - sqrt(D)) / 2a
            - ���� D = 0 ===> ������ 1, x = -b / 2a
            - ���� D < 0 ===> ������ ���

*/
#include <TXLib.h>
#include <stdio.h>
#include <math.h>

int main()
    {
    printf("\n"
           "SolveSq - Solves a square equation\n\n"
           "Enter coeffs a, b, c for equation ax^2+bx+c=0. Enter a: ");

    double a = 0;
    scanf("%lg", &a);

    printf("                                               Enter b: ");

    double b = 0;
    scanf("%lg", &b);

    printf("                                               Enter c: ");

    double c = 0;
    scanf("%lg", &c);

    if (a == 0)
        {
            if(b == 0)
                {
                if(c == 0)
                    {
                    printf("\\infty roots!\n");
                    }

                if(c != 0)
                    {
                    printf("No roots!\n");
                    }
                }

            if(b != 0)
                {
            double x = -c / b;

            printf("1 root, x = %lg\n", x);
                }
        }

    if ( a!= 0)
        {
        double D = b * b - 4 * a * c;

        if(D > 0)
            {
            double x1 = (-b - sqrt(D)) / (2 * a);
            double x2 = (-b + sqrt(D)) / (2 * a);

            printf("2 roots, x1 = %lg, x2 = %lg\n", x1, x2);
            }

        if(D == 0)
            {
            double x = -b / (2 * a);

            printf("1 root, x = %lg\n", x);
            }

        if(D < 0)
            {
            printf("No roots!\n");
            }
        }
    retutrn 0;
    }
