/*

0. Ñîçäàòü ìàññèâ ñòðóêòóð ñ óêàçàòåëÿìè íà íà÷àëî êàæäîé ñòðîêè è äëèííîé ñòðîêè

1. Ïðî÷èòàòü ôàéë:
   - ðåàëèçîâàòü ôóíêöèþ fread?
   - îïðåäåëèòü êîëè÷åñòâî ñòðîê è çàäàòü äëèíó ìàññèâà ñòðóêòóð
   - çàïèñàòü òåêñò â ìàññèâ ñòðóêòóð(èëè äðóãîé ìàññèâ, ïîòîì ðàçáåðóñü),
   ïðè ýòîì çàïèñàâ óêàçàòåëü íà íà÷àëî êàæäîé ñòðîêè è äëèíó ñòðîêè

2. Îòñîðòèðîâàòü òåêñò:
   - íàïèñàòü ôóíêöèþ ñîðòèðîâêè
   - îòñîðòèðîâàòü òåêñò ñîõðàíåííûé â ìàññèâå ïðè ïîìîùè ôóíêöèè ñîðòèðîâêè

3. Ôóíêöèÿ ñîðòèðîâêè, ðåêóðñèâíîä:
   - ïðèíèìàåò äëèíó ñòðîêè è óêàçàòåëü íà íà÷àëî ñòðîêè
   - ñðàâíèâàåò ïåðâûé ñèìâîë îäíîé ñòðîêè, ñ ïåðâûì ñèìâîëîì äðóãîé, åñëè îíè îäèíàêîâû, òî ñðàâíèâàåò ñëåäóþùèå
   ñèìâîëû è òàê äàëåå
   - åñëè îäíà èç ñòðîê êîí÷èëàñü ïðè ñðàâíåíèè (n ñèìâîëîâ îäíîé ñòðîêè ñîâïàäàþò ñ n ñèìâîëàìè äðóãîé), òî ñòðîêà,
   êîòîðàÿ êîðî÷å, ñòàíîâèòñÿ ïåðåä ñòðîêîé, êîòîðàÿ äëèííåå
   - ñîðòèðîâêà ðàññòàâëÿåò ñòðîêè â àëôàâèòíîì ïîðÿäêå
   - ïðîáåëû äîëæíû èìåòü áîëåå íèçêîå çíà÷åíèå, ÷åì äðóãèå ñèìâîëû (íî ýòî íå òî÷íî)
   - çíàêè ïðåïèíàíèÿ â ïåðâîé âåðñèè ïðîãðàììû èãíîðèðóþòñÿ (íî ýòî íå òî÷íî)

3.1. Íàïèñàòü ôóíêöèþ ñòðàâíåíèÿ ñòðîê, êîòîðóþ äîáàâèòü â ñîðòèðîâêó.

4. Âûâîäèì îòñîðòèðîâàííûé òåêñò â ôàéë sorted

symbcount: ñ÷èòàåò êîëè÷åñòâî ñèìâîëîâ â òåêñòå

strcount: ñ÷èòûâàåò êîëè÷åñòâî ñòðîê â òåêñòå

fill_info: çàïîíÿåò àäðåñ íà íîâóþ ñòðîêó è äëèíó ñòðîêè â ìàññèâ ñòðóêòóð, äëÿ âñåõ ñòðîê

sort_func: ôóíêöèÿ ñ ðåêóðñèâíîé ñîðòèðîâêîé (ïî òèïó qsort) èñïîëüçóåò text_sort äëÿ ñîðòèðîâêè ñòðîê, ðàñïîëîãàåò
ñòðîêè ìåíüøå îïîðíîé ñëåâà îò íå¸, áîëüøå îïîðíîé, ñïðàâà îò íå¸. Çà îïîðíûé ýëåìåíò áåð¸òñÿ ïîñëåäíèé ýëåìåíò.

text_sort: ôóíêöèÿ ñîðòèðîâêè ÿâëÿþùàÿñÿ îáîëî÷êîé êîìïàðàòîðà, çàïóñêàåò öèêë, âî âðåìÿ êîòîðãî ñðàâíèâàþòñÿ
âñå ñòðîêè ñ îïîðíûì ýëåìåíòîì è ñîðòèðóþòñÿ â çàâèñèìîñòè îò ðåçóëüòàòà (ñòðîêè áîëüøå îïîðíîé ñòàâÿòñÿ â êîíåö
 ìåíüøå îïîðíîé îñòàþòñÿ â íà÷àëå, ïîçæå îïîðíûé ýëåìåíò ïåðåìåùàåòñÿ íà ìåñòî l = h, ìåæäó ñòðîêîé ìåíüøå
îïîðíîé è ñòðîêîé áîëüøå îïîðíîé.

str_cmp: ôóíêöèÿ ñðàâíèâàþùàÿ äâå ñòðîêè, îïîðíóþ è ëþáóþ äðóãóþ

swap_lines: ôóíêöèÿ ìåíÿþùàÿ ìåñòàìè äâå ñòðîêè (åñëè áûòü òî÷íåå, òî ìåíÿåòñÿ èõ ïîðÿäîê â ìàññèâå ñòðóêòóð)
èñïîëüçóåòñÿ â ôóíêöèè text_sort

print_text: âûâîäèò îòñîðòèðîâàííûé òåêñò

printtext: ôóíêöèÿ èñïîëüçóÿùàÿñÿ äëÿ ïðîâåðêè íîìåðîâ ñèìâîëîâ è ñèìâîëîâ â ìàññèâå text (â äàííûé ìîìåíò
îòêëþ÷åíà çà íåíàäîáíîñòüþ)
*/

#include <stdio.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <ctype.h>
#include <assert.h>
#include <locale.h>

///////////////////////////////////////////////////////////////////////////////////

typedef struct
    {
    char *str_adr;
    int str_len;
    } info;

int symbcount ();
int strcount (char *text, int symbol_quantity);
void fill_info (int symb_quantity, char* text, int str_quantity, info *text_info);
int str_cmp (int l, int high, info *text_info);
void sort_func (int low, int high, info *text_info, int(*str_cmp)(int low, int high, info *text_info));
void swap_lines (int l, info *text_info, int h);
void print_text (int str_quantity, info *text_info, FILE *sorted);
int reverse_str_cmp (int low, int high, info *text_info);

///////////////////////////////////////////////////////////////////////////////////

int main ()
    {
    //setlocale(LC_ALL, "ru_RU.cp1251");

    FILE *txt = NULL;

    if((txt = fopen("Onegin.txt", "r+")) == NULL)
        {
        printf("Programm couldn't open the file \nProgramm: %s \nLine: %d\n", __FILE__, __LINE__);

        return -1;
        }

    int all_symb = symbcount();

    int symb_quantity = 0;

    if((symb_quantity = all_symb + 1) < 1)
        {
        printf("Programm couldn't work with this number of symbols \nProgramm: %s \nLine: %d\n", __FILE__, __LINE__);

        return -1;
        }

    char *text = NULL;

    if((text = (char *) calloc(symb_quantity, sizeof(char))) == NULL)
        {
        printf("Programm couldn't use calloc to allocate memory \nProgramm: %s \nLine: %d\n", __FILE__, __LINE__);

        return -1;
        }

    if((fread (text, sizeof(char), symb_quantity, txt)) == all_symb)
        {
        printf("Programm couldn't read text from file\nProgramm: %s \nLine: %d\n", __FILE__, __LINE__);

        return -1;
        }

    int str_quantity = 0;

    str_quantity = strcount (text, symb_quantity);

    info *text_info = NULL;

    if(( text_info = (info *) calloc(str_quantity, sizeof(info))) == NULL)
        {
        printf("Pogramm couldn't use calloc to ollocate memory \nProgramm: %s \nLine: %d\n", __FILE__, __LINE__);

        return -1;
        }

    fill_info (symb_quantity, text, str_quantity, text_info);

    int low = 0;
    int high = 0;

    high = str_quantity - 1;


    FILE *sorted = NULL;

    if((sorted = fopen("sorted.txt", "w")) == NULL)
        {
        printf("Programm couldn't open sorted.txt \nProgramm: %s \nLine: %d\n", __FILE__, __LINE__);

        return -1;
        }

    sort_func (low, high, text_info, str_cmp);

    fprintf(sorted, "\n\n\n\nSorted text\n\n\n\n");
    print_text (str_quantity, text_info, sorted);

    fclose(sorted);

    if((sorted = fopen("sorted.txt", "a")) == NULL)
        {
        printf("Programm couldn't open sorted.txt \nProgramm: %s \nLine: %d\n", __FILE__, __LINE__);

        return -1;
        }

    sort_func (low, high, text_info, reverse_str_cmp);

    fprintf(sorted, "\n\n\n\nReverse sorted text\n\n\n\n");

    print_text (str_quantity, text_info, sorted);

    fclose(sorted);

    fclose(txt);

    free(text);

    return 0;
    }

///////////////////////////////////////////////////////////////////////////////////

int symbcount ()
    {
    struct stat buf;
    if(stat ("text.txt", &buf) == -1)
        {
        printf("Programm couldn't fill stat \nProgramm: %s \nLine: %d", __FILE__, __LINE__);

        return -1;
        }

    return buf.st_size;
    }

///////////////////////////////////////////////////////////////////////////////////

int strcount (char *text, int symb_quantity)
    {
    int i = 0;
    int str_quantity = 0;

    for (i = 0; i < symb_quantity; i++)
	    {
	    if ((text[i] == '\n' || text[i] == '\0') && text[i - 1] != '\n' && text[i - 1] != '\0')
	        {
	        ++str_quantity;

	        text[i] = '\0';
	        }

        if ((text[i] == '\n' || text[i] == '\0') && (text[i - 1] == '\n' || text[i - 1] == '\0'))
	        {
	        text[i - 1] = '\0';
	        }
	    }

    return str_quantity;
    }

///////////////////////////////////////////////////////////////////////////////////

void fill_info (int symb_quantity, char *text, int str_quantity, info *text_info)
    {
    int i = 0;
    int quant = 0;
    int j = 0;
    char *adr = &text[0];

    for(i = 0; i < symb_quantity; i++)
	    {
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
        else
            {
            ++quant;
            }
	    }

    }

///////////////////////////////////////////////////////////////////////////////////

void sort_func (int low, int high, info *text_info, int(*cmp)(int low, int high, info *text_info))
    {
    if ((high - low + 1 ) >= 2)
	    {
        int l = low;
        int h = high - 1;
        int aver = 0;

        int ans = 0;

        while (l < h)
	        {
	        ans = cmp (l, high, text_info);

	        if (ans == -1)
	            {
	            swap_lines (l, text_info, h);

	            --h;
	            }
            else if(ans == 1 || ans == 0)
                {
                ++l;
	            }
	        }

        ans = 0;

        ans = cmp (l, high, text_info);

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

        sort_func(low, aver - 1, text_info, cmp);
        sort_func(aver, high, text_info, cmp);
        }
    }

///////////////////////////////////////////////////////////////////////////////////

int str_cmp (int low, int high, info *text_info)
    {
    int i = 0;
    int j = 0;
    int k = 0;

    unsigned int test = 0;

    int ans = 0;

    char symb_high = '\0';
    char symb_low = '\0';

    for (i = 0, j = 0; k == 0; i++, j++)
        {

        while(!(isalpha(test = *(text_info[high].str_adr + i * sizeof(char)))) && test != '\0')
            {
            ++i;
            }

        while(!(isalpha(test = *(text_info[low].str_adr + j * sizeof(char)))) && test != '\0')
            {
            ++j;
            }

        symb_high = *(text_info[high].str_adr +  i * sizeof(char));
        symb_low = *(text_info[low].str_adr + j * sizeof(char));

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

///////////////////////////////////////////////////////////////////////////////////

void swap_lines (int l, info *text_info, int h)
    {
    char *adr = NULL;
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

///////////////////////////////////////////////////////////////////////////////////

int reverse_str_cmp (int low, int high, info *text_info)
    {
    int i = 0;
    int j = 0;
    int k = 0;

    int ans = 0;

    char symb_high = '\0';
    char symb_low = '\0';

    for (i = 1, j = 1; k == 0; i++, j++)
        {

        while(!(isalpha(symb_high = *(text_info[high].str_adr + text_info[high].str_len - i * sizeof(char)))) && symb_high != '\0')
            {
            ++i;
            }

        while(!(isalpha(symb_low = *(text_info[low].str_adr + text_info[low].str_len - j * sizeof(char)))) && symb_low != '\0')
            {
            ++j;
            }

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

////////////////////////////////////////////////////////////////////////////////////////////

void print_text (int str_quantity, info *text_info, FILE *sorted)
    {
    int i = 0;

    for (i = 0; i < str_quantity; i++)
	    {
        fprintf(sorted ,"%s", text_info[i].str_adr);

        fprintf(sorted ,"\n");
	    }
    }
