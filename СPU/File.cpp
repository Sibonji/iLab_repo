//
// Created by bulat on 21.02.2021.
//

#include "File.h"
#include "Enum.h"

int symbcount (char * name) {
    struct stat buf;
    if(stat (name, &buf) == -1)
    {
        printf("Programm couldn't fill stat \nProgramm: %s \nLine: %d", __FILE__, __LINE__);

        return -1;
    }

    return buf.st_size;
}

void fill_info (int symb_quantity, char *text, int str_quantity, info *text_info) {
    int i = 0;
    int quant = 0;
    int j = 0;

    while (text[i] == '\0' || text[i] == '\n' || text[i] == ' ') ++i;

    char *adr = &text[i];

    for(; i < symb_quantity; i++)
    {
        if (text[i] == '\0' && (i - 1) >= 0 && text[i - 1] != '\0')
        {
            text_info[j].str_adr = adr;

            text_info[j].str_len = quant;

            quant = 0;

            while (text[i + 1] == '\0' && i < symb_quantity) i++;

            adr = &text[i + 1];

            j++;
        }
        else
        {
            ++quant;
        }
    }
}

int cmdcount (char *text, int symb_quantity, int * where_n, int * n_counter) {
    int i = 0;
    int str_quantity = 0;

    for (i = 0; i < symb_quantity; i++)
    {
        if ((text[i] == '\n' || text[i] == ' ' || text[i] == '\0') && (i - 1) >= 0 && text[i - 1] != '\n' && text[i - 1] != '\0' && text[i - 1] != ' ')
        {
            ++str_quantity;

            if (text[i] == '\n' || text[i] == '\0')
            {
                if (* n_counter != 0)
                {
                    where_n = (int *) realloc (where_n, sizeof (int) * (* n_counter + 1));
                }
                where_n[* n_counter] = str_quantity - 1;

                ++(* n_counter);
            }

            text[i] = '\0';
        }

        if ((text[i] == '\n' || text[i] == ' ' || text[i] == '\0') && (i - 1) >= 0 && (text[i - 1] == '\n' || text[i - 1] == '\0' || text[i - 1] == ' '))
        {
            if (text[i] == '\n' || text[i] == '\0')
            {
                if (str_quantity > 0 && where_n[* n_counter - 1] != str_quantity - 1)
                {
                    if (* n_counter != 0)
                    {
                        where_n = (int *) realloc (where_n, sizeof (int) * (* n_counter + 1));
                    }
                    where_n[* n_counter] = str_quantity - 1;

                    ++(* n_counter);
                }
            }

            text[i] = '\0';
        }
    }

    return str_quantity;
}

int check (int err, FILE * potok, char * asm_code, char * input) {
    if (err)
    {
        char answer[100];

        printf ("Problem file: %s\n", input);

        fclose (potok);
        free (asm_code);

        return 1;
    }

    return 0;
}

void print_err1 (char * cmd, char * arg, int i) {
    printf ("Please write correct argument to the command: %s (this command has number: %d), instead of this argument: %s\n", cmd, i, arg);

    return;
}

void print_err2 (char * cmd, int i) {
    printf ("Please write corect command instead of: %s. This command has number: %d\n", cmd, i);

    return;
}

void print_err3 (char * cmd, int i) {
    printf ("Please write argument for command: %s. This command has number: %d\n", cmd, i);

    return;
}

void print_err5 (char * cmd, int i) {
    printf ("Please write correct tag for command: %s. This command has number: %d\n", cmd, i);

    return;
}

void print_err6 (char * cmd, int i) {
    printf ("Couldn't use %s, that has command: %d, because stack has insufficient values\n", cmd, i);

    return;
}

int strcmp_my (char * first, char * second) {
    int i = 0;
    int len1 = strlen (first);
    int len2 = strlen (second);
    int check = 0;

    //printf ("First: %s,  second: %s\n", first, second);

    for (i = 0; i < len1 && i < len2 && check == 0; i++)
    {
        if (first[i] != second[i])
        {
            if ((first[i] == ':' && second[i] == '\0' && first[i + 1] == '\0') || (second[i] == ':' && first[i] == '\0' && second[i + 1] == '\0'))
            {
                ++i;
                ++i;
            }
            else check = 1;
        }
    }

    //printf ("Check: %d\n", check);

    if (check == 1) return 1;
    else return 0;
}

void fill_jmp_tags (tag * tags_jmp, int tags_jmp_num, info * tags, int tags_num, tags_adr * tag_adr, type * command) {
    int i = 0;
    int j = 0;

   // printf ("Tags_num: %d, Tags_jmp_num: %d\n", tags_num, tags_jmp_num);

    for (i = 0; i < tags_num; i++)
    {
        for (j = 0; j < tags_jmp_num; j++)
        {
            if (strcmp_my(tags_jmp[j].name, tags[tag_adr[i].i_num].str_adr) == 0)
            {
                //printf ("Jmp tag: %s, tag: %s\n", tags_jmp[j].name, tags[tags_adr[i]].str_adr);

                command[tags_jmp[i].adr] = tag_adr[i].cmd_num;
            }
        }
    }

    //printf ("AAAAA\n");

    return;
}

int check_asm (int check_errors, info * text_info, tags_adr * tag_adr, int tags_num) {
    int i = 0;
    int j = 0;

    for (i = 0; i < tags_num; i++)
    {
        for (j = 0; j < tags_num; j++)
        {
            if (i != j && strcmp (text_info[tag_adr[i].i_num].str_adr, text_info[tag_adr[j].i_num].str_adr) == 0)
            {
                check_errors += 1;
            }
        }
    }

    if (check_errors != 0) return 1;
    else return 0;
}


int fill_jmp_and_call (tag * tags_info, int * where_n, int * i, int * j, info * text_info, int checker, int * check_errors, int * command, int * cmd_number, int * tags_jmp_num) {
    if (where_n[(* j)] != (* i) + 1)
    {
        print_err3(text_info[(* i)].str_adr, (* i));

        checker += 1;
    }
    else
    {
        tags_info[(* tags_jmp_num)].name = (char *) calloc(strlen(text_info[(* i) + 1].str_adr), sizeof(char));

        tags_info[(* tags_jmp_num)].name = text_info[(* i) + 1].str_adr;
        tags_info[(* tags_jmp_num)++].adr = * cmd_number + 1;

        tags_info = (tag *) realloc(tags_info, ((* tags_jmp_num) + 1) * sizeof(tag));
    }

    if (checker != 0)
    {
        * check_errors += checker;
    }

    command[* cmd_number] = CMD_JMP;
    command[++(* cmd_number)] = CMD_UNDF;
    checker = 0;
    ++(* cmd_number);
    (* i) = where_n[(* j)++];

    return 0;
}