/*

0. ����������:
   - ��� ���������� �.
   - ��� ������ �.

   � �����:

   -��������, ��� ������� �����

1. ������ �����.���.��. ax + b = 0 (a, b)
   ���� �����. �� ���� ���������� �����, �� ��������� ����

2. �������� ��������� � ����� ����
   ��������� ��� ������:
   - ���� (a != 0) ===> 1 ������, x = -b / a
   - ���� (a == 0) � (b != 0) ===> ��� ������
   - ���� (a == 0) � (b == 0) ===> \infty ������
   - �����: ===> ��������� ����� ���� ������� (����������)

3. ������� �����
   - �-�� ������
   - ������

   ��������:
   - �������� ����� ������
   - ����� ��������

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
