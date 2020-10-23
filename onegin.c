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
void text_info (struct info *text_info);
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

    int low, high;

    high = str_quantity - 1;

    low = 0;

    sort_func(low, high, text_info);

    print_text(str_quantity, text_info);

    return 0;
    }

void printtext(char *text, int symb_quantity)
    {
    int i = 0;

    for(i = 0; i <  symb_quantity; i++)
        {
        printf("%c", text[i]);
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
	        --h;

	        swap_lines (l, text_info, h);
	        }
        else if(ans == 1)
            {
            ++l;
	        }

	    }

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
