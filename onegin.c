
0. Создать массив структур с указателями на начало каждой строки и длинной строки

1. Прочитать файл:
   - реализовать функцию fread?
   - определить количество строк и задать длину массива структур
   - записать текст в массив структур(или другой массив, потом разберусь),
   при этом записав указатель на начало каждой строки и длину строки

2. Отсортировать текст:
   - написать функцию сортировки
   - отсортировать текст сохраненный в массиве при помощи функции сортировки

3. Функция сортировки, рекурсивнод:
   - принимает длину строки и указатель на начало строки
   - сравнивает первый символ одной строки, с первым символом другой, если они одинаковы, то сравнивает следующие
   символы и так далее
   - если одна из строк кончилась при сравнении (n символов одной строки совпадают с n символами другой), то строка,
   которая короче, становится перед строкой, которая длиннее
   - сортировка расставляет строки в алфавитном порядке
   - пробелы должны иметь более низкое значение, чем другие символы (но это не точно)
   - знаки препинания в первой версии программы игнорируются (но это не точно)

3.1. Написать функцию стравнения строк, которую добавить в сортировку.

4. Выводим отсортированный текст в файл sorted

symbcount: считает количество символов в тексте

strcount: считывает количество строк в тексте

fill_info: запоняет адрес на новую строку и длину строки в массив структур, для всех строк

sort_func: функция с рекурсивной сортировкой (по типу qsort) использует text_sort для сортировки строк, распологает
строки меньше опорной слева от неё, больше опорной, справа от неё. За опорный элемент берётся последний элемент.

text_sort: функция сортировки являющаяся оболочкой компаратора, запускает цикл, во время которго сравниваются
все строки с опорным элементом и сортируются в зависимости от результата (строки больше опорной ставятся в конец
 меньше опорной остаются в начале, позже опорный элемент перемещается на место l = h, между строкой меньше
опорной и строкой больше опорной.

str_cmp: функция сравнивающая две строки, опорную и любую другую

swap_lines: функция меняющая местами две строки (если быть точнее, то меняется их порядок в массиве структур)
используется в функции text_sort

print_text: выводит отсортированный текст

printtext: функция используящаяся для проверки номеров символов и символов в массиве text (в данный момент
отключена за ненадобностью)
*/

#include <stdio.h>
#include <sys/stat.h>
#include <stdlib.h>

struct info
    {
    char *str_adr;
    int str_len;
    };

int symbcount ();
int strcount (char *text, int symbol_quantity);
void fill_info (int symb_quantity, char* text, int str_quantity, struct info* text_info);
int text_sort (int low, int high, struct info *text_info);
int str_cmp (int l, int high, struct info *text_info);
void sort_func (int low, int high, struct info *text_info);
void swap_lines (int l, struct info *text_info, int h);
void print_text (int str_quantity, struct info *text_info);
void printtext(char *text, int symb_quantity);

int main ()
    {
    FILE *txt = fopen ("text.txt", "r+");

    int symb_quantity;

    symb_quantity = symbcount () + 1;

    char *text;

    text = (char *) calloc(symb_quantity, sizeof(char));

    fread (text, sizeof(char), symb_quantity, txt);

    int str_quantity = 0;

    str_quantity = strcount (text, symb_quantity);

    struct info text_info[str_quantity];

    fill_info (symb_quantity, text, str_quantity, text_info);

    //printtext (text, symb_quantity);

    printf("Strquant: %d\n\n", str_quantity);

    int low, high;

    high = str_quantity - 1;

    low = 0;

    sort_func (low, high, text_info);

    print_text (str_quantity, text_info);

    free (text);

    return 0;
    }

void printtext(char *text, int symb_quantity)
    {
    int i = 0;

    for(i = 0; i <  symb_quantity; i++)
        {
        printf("Symbol is: %c, code of element: %d\n", text[i], text[i]);
        }
    }

int symbcount ()
    {
    struct stat buf;
    stat ("text.txt", &buf);

    return buf.st_size;
    }

int strcount (char *text, int symb_quantity)
    {
    int i = 0;
    int str_quantity = 0;

    for (i = 0; i < symb_quantity; i++)
	    {
	    if ((text[i] == '\n' || text[i] == '\0') && text[i - 1] != '\n' && text[i - 1] != '\0')
	        {
	        ++str_quantity;
		    
		text[i] = '\n';
	        }

        if ((text[i] == '\n' || text[i] == '\0') && (text[i - 1] == '\n' || text[i - 1] == '\0'))
	        {
	        text[i - 1] = '\n';
	        }
	    }

    return str_quantity;
    }

void fill_info (int symb_quantity, char *text, int str_quantity, struct info *text_info)
    {
    int i = 0;
    int quant = 0;
    int j = 0;
    char *adr = &text[0];

    for(i = 0; i < symb_quantity; i++)
	    {
	    ++quant;

	    if ((text[i] == '\n' || text[i] == '\0') && text[i - 1] != '\n' && text[i - 1] != '\0')
            {

            text_info[j].str_adr = adr;


	        text_info[j].str_len = quant;

            quant = 0;

            if (text [i + 1] != '\0')
		        {
                adr = &text[i + 1];
                }
            else adr = &text[symb_quantity + 1];

	        j++;
            }
	    }

    }

void sort_func (int low, int high, struct info *text_info)
    {
    if ((high - low + 1 ) >= 2)
	    {
	    int aver;
        aver = text_sort(low, high, text_info);

        sort_func(low, aver - 1, text_info);
        sort_func(aver, high, text_info);
	    }
    }

int text_sort (int low, int high, struct info *text_info)
    {
    int l = low;
    int h = high - 1;
    int aver = 0;

    int ans = 0;

    while (l < h)
	    {
	    ans = str_cmp (l, high, text_info);

	    if (ans == -1)
	        {
	        swap_lines (l, text_info, h);

	        --h;
	        }
        else if(ans == 1)
            {
            ++l;
	        }
	    }

    ans = 0;

    ans = str_cmp (l, high, text_info);

    if (ans == -1)
        {
        swap_lines (l, text_info, high);

        aver = l;
        }
    else if(ans == 1)
        {
        swap_lines (l + 1, text_info, high);

        aver = l + 1;
        }

    return aver;
    }

int str_cmp (int l, int high, struct info *text_info)
    {
    int i = 0;
    int k = 0;

    int ans = 0;

    char symb_high, symb_low;

    for (i = 0; k == 0; i++)
        {
        symb_high = *(text_info[high].str_adr + i * sizeof(char));
        symb_low = *(text_info[l].str_adr + i * sizeof(char));

        if (symb_high < symb_low)
            {
            ans = -1;

            k = 1;
            }

        if (symb_high > symb_low)
            {
            ans = 1;

            k = 1;
            }
        }

    return ans;
    }

void swap_lines (int l, struct info *text_info, int h)
    {
    char *adr;
    int len = 0;

    if (l != h)
        {
        adr = text_info[h].str_adr;
        len = text_info[h].str_len;

        text_info[h].str_adr = text_info[l].str_adr;
        text_info[h].str_len = text_info[l].str_len;

        text_info[l].str_adr = adr;
        text_info[l].str_len = len;
        }
    }

void print_text (int str_quantity, struct info *text_info)
    {
    int i = 0;
    int j = 0;

    for (i = 0; i < str_quantity; i++)
	    {
	    for (j = 0; j < text_info[i].str_len; j++)
	        {
	        printf("%c", *(text_info[i].str_adr + j * sizeof(char)));
	        }
	    }
    }

