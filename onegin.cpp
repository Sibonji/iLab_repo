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
