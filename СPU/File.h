//
// Created by bulat on 21.02.2021.
//

#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <errno.h>
#include <string.h>
#include <sys\stat.h>

#define type int

typedef struct _info{
    char * str_adr;
    int str_len;
} info;

typedef struct _cpu {
    type * registr;
    int CP; //command pointer
    type * command;
} cpu;

typedef struct _tags {
    char * name;
    int adr;
} tag;

typedef struct _tag_adr {
    int cmd_num;
    int i_num;
}tags_adr;

int symbcount (char * name);
int cmdcount (char * text, int symbol_quantity, int * where_n, int * n_counter);
void fill_info (int symb_quantity, char * text, int str_quantity, info * text_info);

int check (int err, FILE * potok, char * asm_code, char * input);
void print_err1 (char * cmd, char * arg, int i);
void print_err2 (char * cmd, int i);
void print_err3 (char * cmd, int i);
void print_err5 (char * cmd, int i);
void print_err6 (char * cmd, int i);

int Fill_Cmd_Info (cpu CPU, char * input, int input_size);

int strcmp_my (char * first, char * second);

void fill_jmp_tags (tag * tags_jmp, int tags_jmp_num, info * tags, int tags_num, tags_adr * tags_adr, type * command);
int check_asm (int check_errors, info * text_info, tags_adr * tag_adr, int tags_num);
int fill_jmp_and_call (tag * tags_info, int * where_n, int * i, int * j, info * text_info, int checker, int * check_errors, int * command, int * cmd_number, int * tags_jmp_num);

void fill_registr (cpu CPU);