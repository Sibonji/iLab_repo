//
// Created by bulat on 21.02.2021.
//
//TODO:
// - сделать строки как в онегине (можно взять код из onegin.cpp) DONE
// - считать команды и перевести их в машинный код
// - сделать в asm коде метки для jump
// - менять метки в jump на адрес команды в машинном коде
// - имена меток для разных целей
// - сделать однопроходную или двупроходную схему (однопроходная кайф, для нее сделать отдельную
//   структуру (массив) с именами меток)
// - строка 350 доделать, также добавить структуру меток CodeTranslator
// - сделать счетчик команд

#include "File.h"
#include "Enum.h"

int CodeTranslator (char * input, char * output) {
    int input_size = 0; //количество символов в файле с асссемблерным кодом
    char *asm_code = nullptr; //Указатель на массив с данными из файла
    FILE *potok = nullptr; //Указатель на файл
    int cmd_quantity = 0; //количество комманд, которые будут записаны в файл с машинным кодом
    info *text_info = nullptr; //указатель на массив структур с данными о тексте
    int i = 0; //счетчик для циклов
    char *str; //указатель на строку, в которую будет помещаться аргумент у команд наподобии push
    type *command = nullptr; //указатель на массив команд
    type arg = 0; //аргумент команды
    int n_counter = 0; //счетчик количества \n
    int *where_n = nullptr; //указатель на массив с информацией о всех \n
    int check_errors = 0; //счетчик количества ошибок
    int checker = 0;//проверка на последнюю ошибку
    int j = 0;
    int c = 0;
    tag *tags_info = nullptr;
    int cmd_number = 0;
    int tags_jmp_num = 0;
    tags_adr * tag_adr = nullptr;
    int tags_num = 0;

    if ((input_size = symbcount(input)) <= 0) return 1;

    asm_code = (char *) calloc(input_size, sizeof(char));

    potok = fopen(input, "r");

    if (check(errno, potok, asm_code, input) != 0) return 1;

    fread(asm_code, sizeof(char), input_size, potok);

    where_n = (int *) calloc(1, sizeof(int));

    cmd_quantity = cmdcount(asm_code, input_size, where_n, &n_counter);

    command = (type *) calloc(cmd_quantity, sizeof(type));

    text_info = (info *) calloc(cmd_quantity, sizeof(info));

    tags_info = (tag *) calloc(tags_jmp_num + 1, sizeof(tag));

    if (check(errno, potok, asm_code, input) != 0)
    {
        free(text_info);
        free(command);
        free(where_n);
        free(tags_info);

        return 1;
    }

    fill_info(input_size, asm_code, cmd_quantity, text_info);

    /*printf ("\nAdr_quantity: %d\n", cmd_quantity);

    for (i = 0; i < cmd_quantity; i++)
    {
        printf ("%d\n", text_info[i].str_len);
    }*/

    fclose(potok);

    /*for (i = 0; i < n_counter; i++)
    {
        printf ("\\n goes after this command: %d\n", where_n[i]);
    }*/

    for (i = 0, j = 0; j < n_counter && i < cmd_quantity; i++)
    {
        //printf ("Current arg: %s\n", text_info[i].str_adr);
        if (strcmp(text_info[i].str_adr, "push") == 0)
        {
            if (where_n[j] != i + 1)
            {
                print_err3(text_info[i].str_adr, i);

                checker += 1;
            }
            ++j;

            if (checker != 0)
            {
                i = where_n[j - 1];
            }
            else if ((i + 1) >= cmd_quantity)
            {
                print_err3(text_info[i].str_adr, i);

                //printf ("Current cmd: %d\nNumber of commands: %d\n", i + 1, cmd_quantity);

                checker += 1;
            }
            else if ((arg = atoi(text_info[i + 1].str_adr)) == 0 && text_info[i + 1].str_adr[0] != '0' && text_info[i + 1].str_adr[1] != '\0')
            {
                if ((i + 1) < cmd_quantity && strcmp(text_info[i + 1].str_adr, "ax") == 0)
                    command[++cmd_number] = CMD_RAX;
                else if ((i + 1) < cmd_quantity && strcmp(text_info[i + 1].str_adr, "bx") == 0)
                    command[++cmd_number] = CMD_RBX;
                else if ((i + 1) < cmd_quantity && strcmp(text_info[i + 1].str_adr, "cx") == 0)
                    command[++cmd_number] = CMD_RCX;
                else if ((i + 1) < cmd_quantity && strcmp(text_info[i + 1].str_adr, "dx") == 0)
                    command[++cmd_number] = CMD_RDX;
                else
                {
                    print_err1(text_info[i].str_adr, text_info[i + 1].str_adr, i);

                    checker += 1;
                }

                command[cmd_number - 1] = CMD_PUSH_R;
                ++i;
            }
            else
            {
                command[cmd_number] = CMD_PUSH;
                command[++cmd_number] = arg;
                ++i;
            }

            if (checker != 0)
            {
                check_errors += checker;
            }

            checker = 0;
            ++cmd_number;
        }
        else if (strcmp(text_info[i].str_adr, "pop") == 0)
        {
            if ((i + 1) < cmd_quantity && strcmp(text_info[i + 1].str_adr, "ax") == 0)
            {
                if (where_n[j] != i + 1)
                {
                    print_err3(text_info[i].str_adr, i);

                    checker += 1;
                }
                ++j;

                command[cmd_number] = CMD_POP_R;
                command[++cmd_number] = CMD_RAX;
                ++i;
            }
            else if ((i + 1) < cmd_quantity && strcmp(text_info[i + 1].str_adr, "bx") == 0)
            {
                if (where_n[j] != i + 1)
                {
                    print_err3(text_info[i].str_adr, i);

                    checker += 1;
                }
                ++j;

                command[cmd_number] = CMD_POP_R;
                command[++cmd_number] = CMD_RBX;
                ++i;
            }
            else if ((i + 1) < cmd_quantity && strcmp(text_info[i + 1].str_adr, "cx") == 0)
            {
                if (where_n[j] != i + 1)
                {
                    print_err3(text_info[i].str_adr, i);

                    checker += 1;
                }
                ++j;

                command[cmd_number] = CMD_POP_R;
                command[++cmd_number] = CMD_RCX;
                ++i;
            }
            else if ((i + 1) < cmd_quantity && strcmp(text_info[i + 1].str_adr, "dx") == 0)
            {
                if (where_n[j] != i + 1)
                {
                    print_err3(text_info[i].str_adr, i);

                    checker += 1;
                }
                ++j;

                command[cmd_number] = CMD_POP_R;
                command[++cmd_number] = CMD_RDX;
                ++i;
            }
            else
            {

                if (where_n[j] != i)
                {
                    print_err3(text_info[i].str_adr, i);

                    checker += 1;
                }
                ++j;

                command[cmd_number] = CMD_POP;
            }

            if (checker != 0) {
                check_errors += checker;
            }

            checker = 0;
            ++cmd_number;
        }
        else if (strcmp(text_info[i].str_adr, "add") == 0)
        {
            if (where_n[j] != i)
            {
                print_err3(text_info[i].str_adr, i);

                checker += 1;
            }
            ++j;

            command[cmd_number] = CMD_ADD;

            if (checker != 0)
            {
                check_errors += checker;
            }

            checker = 0;
            ++cmd_number;
        }
        else if (strcmp(text_info[i].str_adr, "sub") == 0)
        {
            if (where_n[j] != i)
            {
                print_err3(text_info[i].str_adr, i);

                checker += 1;
            }
            ++j;

            command[cmd_number] = CMD_SUB;

            if (checker != 0)
            {
                check_errors += checker;
            }

            checker = 0;
            ++cmd_number;
        }
        else if (strcmp(text_info[i].str_adr, "div") == 0)
        {
            if (where_n[j] != i)
            {
                print_err3(text_info[i].str_adr, i);

                checker += 1;
            }
            ++j;

            command[cmd_number] = CMD_DIV;

            if (checker != 0)
            {
                check_errors += checker;
            }

            checker = 0;
            ++cmd_number;
        }
        else if (strcmp(text_info[i].str_adr, "mul") == 0)
        {
            if (where_n[j] != i)
            {
                print_err3(text_info[i].str_adr, i);

                checker += 1;
            }
            ++j;

            command[cmd_number] = CMD_MUL;

            if (checker != 0)
            {
                check_errors += checker;
            }

            checker = 0;
            ++cmd_number;
        }
        else if (strcmp(text_info[i].str_adr, "out") == 0)
        {
            if (where_n[j] != i)
            {
                print_err3(text_info[i].str_adr, i);

                checker += 1;
            }
            ++j;

            command[cmd_number] = CMD_OUT;

            if (checker != 0)
            {
                check_errors += checker;
            }

            checker = 0;
            ++cmd_number;
        }
        else if (strcmp(text_info[i].str_adr, "end") == 0)
        {
            if (where_n[j] != i)
            {
                print_err3(text_info[i].str_adr, i);

                checker += 1;
            }
            ++j;

            command[cmd_number] = CMD_END;

            if (checker != 0)
            {
                check_errors += checker;
            }

            checker = 0;
            ++cmd_number;
        }
        else if (strcmp(text_info[i].str_adr, "hlt") == 0)
        {
            if (where_n[j] != i)
            {
                print_err3(text_info[i].str_adr, i);

                checker += 1;
            }
            ++j;

            command[cmd_number] = CMD_HLT;

            if (checker != 0)
            {
                check_errors += checker;
            }

            checker = 0;
            ++cmd_number;
        }
        else if (strcmp(text_info[i].str_adr, "ret") == 0)
        {
            if (where_n[j] != i)
            {
                print_err3(text_info[i].str_adr, i);

                checker += 1;
            }
            ++j;

            command[cmd_number] = CMD_RET;

            if (checker != 0)
            {
                check_errors += checker;
            }

            checker = 0;
            ++cmd_number;
        }
        else if (strcmp(text_info[i].str_adr, "jmp") == 0)
        {
            //fill_jmp_and_call (tags_info, where_n, &i, &j, text_info, checker, &check_errors, command, &cmd_number, &tags_jmp_num);
            if (where_n[j] != i + 1)
            {
                print_err3(text_info[i].str_adr, i);

                checker += 1;
            }
            else
            {
                tags_info[tags_jmp_num].name = (char *) calloc(strlen(text_info[i + 1].str_adr), sizeof(char));

                tags_info[tags_jmp_num].name = text_info[i + 1].str_adr;
                tags_info[tags_jmp_num].adr = cmd_number + 1;

                ++tags_jmp_num;

                tags_info = (tag *) realloc(tags_info, (tags_jmp_num + 1) * sizeof(tag));
            }
            ++j;

            if (checker != 0)
            {
                check_errors += checker;
            }

            command[cmd_number] = CMD_JMP;
            command[++cmd_number] = CMD_UNDF;
            checker = 0;
            ++cmd_number;
            i = where_n[j - 1];
        }
        else if (strcmp(text_info[i].str_adr, "jmpneq") == 0)
        {
            if (where_n[j] != i + 1)
            {
                print_err3(text_info[i].str_adr, i);

                checker += 1;
            }
            else
            {
                tags_info[tags_jmp_num].name = (char *) calloc(strlen(text_info[i + 1].str_adr), sizeof(char));

                tags_info[tags_jmp_num].name = text_info[i + 1].str_adr;
                tags_info[tags_jmp_num].adr = cmd_number + 1;

                ++tags_jmp_num;

                tags_info = (tag *) realloc(tags_info, (tags_jmp_num + 1) * sizeof(tag));
            }
            ++j;

            if (checker != 0)
            {
                check_errors += checker;
            }

            command[cmd_number] = CMD_JMP_NEQ;
            command[++cmd_number] = CMD_UNDF;
            checker = 0;
            ++cmd_number;
            i = where_n[j - 1];
        }
        else if (strcmp(text_info[i].str_adr, "jmpeq") == 0)
        {
            if (where_n[j] != i + 1)
            {
                print_err3(text_info[i].str_adr, i);

                checker += 1;
            }
            else
            {
                tags_info[tags_jmp_num].name = (char *) calloc(strlen(text_info[i + 1].str_adr), sizeof(char));

                tags_info[tags_jmp_num].name = text_info[i + 1].str_adr;
                tags_info[tags_jmp_num].adr = cmd_number + 1;

                ++tags_jmp_num;

                tags_info = (tag *) realloc(tags_info, (tags_jmp_num + 1) * sizeof(tag));
            }
            ++j;

            if (checker != 0)
            {
                check_errors += checker;
            }

            command[cmd_number] = CMD_JMP_EQ;
            command[++cmd_number] = CMD_UNDF;
            checker = 0;
            ++cmd_number;
            i = where_n[j - 1];
        }
        else if (strcmp(text_info[i].str_adr, "jmpm") == 0)
        {
            if (where_n[j] != i + 1)
            {
                print_err3(text_info[i].str_adr, i);

                checker += 1;
            }
            else
            {
                tags_info[tags_jmp_num].name = (char *) calloc(strlen(text_info[i + 1].str_adr), sizeof(char));

                tags_info[tags_jmp_num].name = text_info[i + 1].str_adr;
                tags_info[tags_jmp_num].adr = cmd_number + 1;

                ++tags_jmp_num;

                tags_info = (tag *) realloc(tags_info, (tags_jmp_num + 1) * sizeof(tag));
            }

            if (checker != 0)
            {
                check_errors += checker;
            }

            command[cmd_number] = CMD_JMP_M;
            command[++cmd_number] = CMD_UNDF;
            checker = 0;
            ++cmd_number;
            i = where_n[j++];
        }
        else if (strcmp(text_info[i].str_adr, "jmpl") == 0)
        {
            if (where_n[j] != i + 1)
            {
                print_err3(text_info[i].str_adr, i);

                checker += 1;
            }
            else
            {
                tags_info[tags_jmp_num].name = (char *) calloc(strlen(text_info[i + 1].str_adr), sizeof(char));

                tags_info[tags_jmp_num].name = text_info[i + 1].str_adr;
                tags_info[tags_jmp_num].adr = cmd_number + 1;

                ++tags_jmp_num;

                tags_info = (tag *) realloc(tags_info, (tags_jmp_num + 1) * sizeof(tag));
            }

            if (checker != 0)
            {
                check_errors += checker;
            }

            command[cmd_number] = CMD_JMP_L;
            command[++cmd_number] = CMD_UNDF;
            checker = 0;
            ++cmd_number;
            i = where_n[j++];
        }
        else if (strcmp(text_info[i].str_adr, "jmpmeq") == 0)
        {
            if (where_n[j] != i + 1)
            {
                print_err3(text_info[i].str_adr, i);

                checker += 1;
            }
            else
            {
                tags_info[tags_jmp_num].name = (char *) calloc(strlen(text_info[i + 1].str_adr), sizeof(char));

                tags_info[tags_jmp_num].name = text_info[i + 1].str_adr;
                tags_info[tags_jmp_num].adr = cmd_number + 1;

                ++tags_jmp_num;

                tags_info = (tag *) realloc(tags_info, (tags_jmp_num + 1) * sizeof(tag));
            }

            if (checker != 0)
            {
                check_errors += checker;
            }

            command[cmd_number] = CMD_JMP_MEQ;
            command[++cmd_number] = CMD_UNDF;
            checker = 0;
            ++cmd_number;
            i = where_n[j++];
        }
        else if (strcmp(text_info[i].str_adr, "jmpleq") == 0)
        {
            if (where_n[j] != i + 1)
            {
                print_err3(text_info[i].str_adr, i);

                checker += 1;
            }
            else
            {
                tags_info[tags_jmp_num].name = (char *) calloc(strlen(text_info[i + 1].str_adr), sizeof(char));

                tags_info[tags_jmp_num].name = text_info[i + 1].str_adr;
                tags_info[tags_jmp_num].adr = cmd_number + 1;

                ++tags_jmp_num;

                tags_info = (tag *) realloc(tags_info, (tags_jmp_num + 1) * sizeof(tag));
            }

            if (checker != 0)
            {
                check_errors += checker;
            }

            command[cmd_number] = CMD_JMP_LEQ;
            command[++cmd_number] = CMD_UNDF;
            checker = 0;
            ++cmd_number;
            i = where_n[j++];
        }
        else if (strcmp(text_info[i].str_adr, "call") == 0)
        {
            if (where_n[j] != i + 1)
            {
                print_err3(text_info[i].str_adr, i);

                checker += 1;
            }
            else
            {
                tags_info[tags_jmp_num].name = (char *) calloc(strlen(text_info[i + 1].str_adr), sizeof(char));

                tags_info[tags_jmp_num].name = text_info[i + 1].str_adr;
                tags_info[tags_jmp_num].adr = cmd_number + 1;

                ++tags_jmp_num;

                tags_info = (tag *) realloc(tags_info, (tags_jmp_num + 1) * sizeof(tag));
            }

            if (checker != 0)
            {
                check_errors += checker;
            }

            command[cmd_number] = CMD_CALL;
            command[++cmd_number] = CMD_UNDF;
            checker = 0;
            ++cmd_number;
            i = where_n[j++];
        }
        else if (text_info[i].str_adr[strlen(text_info[i].str_adr) - 1] == ':')
        {
            if (tags_num == 0)
            {
                tag_adr = (tags_adr *) calloc (tags_num + 1, sizeof (tags_adr));
            }
            else
            {
                tag_adr = (tags_adr *) realloc (tag_adr, (tags_num + 1) * sizeof (tags_adr));
            }

            if (where_n[j] != i)
            {
                print_err3(text_info[i].str_adr, i);

                check_errors += 1;
            }

            tag_adr[tags_num].i_num = i;
            tag_adr[tags_num].cmd_num = cmd_number;

            ++tags_num;

            ++j;
        }
        else
        {
            //printf ("Symbol before the last is: %c\n", text_info[i].str_adr[strlen (text_info[i].str_adr) - 1]);
            print_err2(text_info[i].str_adr, i);

            check_errors += 1;
        }
    }

    if (check_asm (check_errors, text_info, tag_adr, tags_num) == 1) return 1;

    //printf ("Check\n\n");

    if (check_errors != 0)
    {
        return 1;
    }

    //printf ("Tags quantity: %d\n", tags_num);
    //printf ("Check\n\n");

    fill_jmp_tags (tags_info, tags_jmp_num, text_info, tags_num, tag_adr, command);

    //printf ("Check\n\n");
    //printf ("Symbol before the last is: %c\n", text_info[0].str_adr[strlen (text_info[0].str_adr) - 1]);

    potok = fopen(output, "wb");
    if (check (errno, potok, asm_code, output) != 0)
    {
        free (text_info);
        free (command);
        free (where_n);
        free (tags_info);

        return 1;
    }

    int entered = fwrite (command, sizeof (type), cmd_number, potok);

    printf ("Cmd_quantity: %d\n", cmd_number);

    for (int i = 0; i < cmd_number; i++) {
        printf("%d ", command[i]);
    }

    printf ("\n");

    printf ("Entered: %d\n", entered);

    //printf ("Tags_num: %d", tags_jmp_num);

    fclose (potok);

    free (where_n);
    free (asm_code);
    free (text_info);
    free (command);
    free (tags_info);

    return 0;
}