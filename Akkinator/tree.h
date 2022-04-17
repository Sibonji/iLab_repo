#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <errno.h>
#include <string.h>
#include <sys\stat.h>
#include <sapi.h>
#include <string.h>
#include <tchar.h>
#include <SDKDDKVer.h>

#define print_err printf("Error occured during the programm working \nProgramm: %s \nLine: %d\n", __FILE__, __LINE__); \
                  return 1;

class tree {
public:
    tree* left;
    tree* right;
    char* str;

    void print_tree ();
};

void tree::print_tree() {
    printf ("{\n");
    printf ("%s\n", str);
    if (left != nullptr)
    {
        left -> print_tree ();
    }
    else if (right != nullptr)
    {
        right -> print_tree ();
    }
    printf ("}\n");
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class info {
public:
    char *str_adr;
    int str_len;
};

class text {
public:
    int size;
    char* arr;
    int str_quantity;
    info* text_info;

    text();
    void destroy_text();
};

text::text() {
    size = 0;
    arr  = nullptr;
    str_quantity = 0;
    text_info = nullptr;
}

void text::destroy_text() {
    size = 0;
    if (arr != nullptr)
        free(arr);
    str_quantity = 0;
    if (text_info != nullptr)
        free (text_info);
}



int open_file  (FILE* potok, char* input, text* my_text);
int strcount   (char* text, int symb_quantity);
int symbcount  (char* name);
void fill_info (int symb_quantity, char* text, int str_quantity, info* text_info);
void fill_tree (tree* curr, text* text_info, int* num);
int fprint_tree (tree* curr, char* input);
void get_tree  (tree* curr, FILE* potok);
void destroy_tree (tree* curr);
void ask_user  (tree* curr);
void work_with_user (tree* curr);
int fprint_tree2 (tree* curr, char* input);
void get_tree2  (tree* curr, FILE* potok);