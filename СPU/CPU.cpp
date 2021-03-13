//
// Created by bulat on 21.02.2021.
//
//TODO:
// - пока что сделать только для чисел
// - реализация считывания чисел через %d, %f
// - можно поменять TEMPLATE, но вначале прочитать про это
// - сделать библиотеку с макросами для вывода ошибок и с функциями из онегина DONE
// - Почитать про расширение .asm

#include "File.h"
#include "Enum.h"
#include <unistd.h>

#define print_err4 printf ("Programm has stopped his execution because of occured error");

//////////////////////////////////////////////////////////////////////////////////////////////////

#include "stack_1.h"

int push_cmd (cpu CPU, int cmd_quantity, Stack * data, int num);
int pop_cmd (cpu CPU, int cmd_quantity, Stack * data, int num);
int add_cmd (cpu CPU, int cmd_quantity, Stack * data, int num);
int sub_cmd (cpu CPU, int cmd_quantity, Stack * data, int num);
int div_cmd (cpu CPU, int cmd_quantity, Stack * data, int num);
int mul_cmd (cpu CPU, int cmd_quantity, Stack * data, int num);
int jmp_cmd (cpu CPU, int cmd_quantity, Stack * data, int num);
int jmp_neq_cmd (cpu CPU, int cmd_quantity, Stack * data, int num);
int jmp_eq_cmd (cpu CPU, int cmd_quantity, Stack * data, int num);
int jmp_m_cmd (cpu CPU, int cmd_quantity, Stack * data, int num);
int jmp_l_cmd (cpu CPU, int cmd_quantity, Stack * data, int num);
int jmp_meq_cmd (cpu CPU, int cmd_quantity, Stack * data, int num);
int jmp_leq_cmd (cpu CPU, int cmd_quantity, Stack * data, int num);
int call_cmd (cpu CPU, int cmd_quantity, Stack * data, Stack * get_adr, int num);
int ret_cmd (cpu CPU, int cmd_quantity, Stack * data, Stack * get_adr, int num);
int out_cmd (cpu CPU, int cmd_quantity, Stack * data, int num);
int hlt_cmd ();
int push_r_cmd (cpu CPU, int cmd_quantity, Stack * data, int num);
int pop_r_cmd (cpu CPU, int cmd_quantity, Stack * data, int num);

//////////////////////////////////////////////////////////////////////////////////////////////////////

int CodeExecuter (char * input) {
    cpu CPU;
    int input_size = 0;
    int check = 0;
    int end_check = 0;

    Stack data;
    Stack get_adr;

    construct (&data, 5);
    construct (&get_adr, 5);

    CPU.CP = 0;
    CPU.registr = (type *) calloc (4, sizeof (type));

    input_size = symbcount (input);

    CPU.command = (int *) calloc (input_size, sizeof (int));

    //printf ("Cmd_quantity: %d\n", input_size);

    int cmd_quantity = Fill_Cmd_Info (CPU, input, input_size);

    for (int i = 0; i < cmd_quantity && check == 0; i++)
    {
        switch (CPU.command[i]) {
            case CMD_PUSH:
                if (push_cmd (CPU, cmd_quantity, &data, i) != 0) ++check;

                ++i;

                break;
            case CMD_POP:
                if (pop_cmd (CPU, cmd_quantity, &data, i) != 0) ++check;

                break;
            case CMD_ADD:
                if (add_cmd (CPU, cmd_quantity, &data, i) != 0) ++check;

                break;
            case CMD_SUB:
                if (sub_cmd (CPU, cmd_quantity, &data, i) != 0) ++check;

                break;
            case CMD_DIV:
                if (div_cmd (CPU, cmd_quantity, &data, i) != 0) ++check;

                break;
            case CMD_MUL:
                if (mul_cmd (CPU, cmd_quantity, &data, i) != 0) ++check;

                break;
            case CMD_JMP:
                if ((i = jmp_cmd (CPU, cmd_quantity, &data, i)) == -1) ++check;

                break;
            case CMD_JMP_NEQ:
                if ((i = jmp_neq_cmd (CPU, cmd_quantity, &data, i)) == -1) ++check;

                break;
            case CMD_JMP_EQ:
                if ((i = jmp_eq_cmd (CPU, cmd_quantity, &data, i)) == -1) ++check;

                break;
            case CMD_JMP_M:
                if ((i = jmp_m_cmd (CPU, cmd_quantity, &data, i)) == -1) ++check;

                break;
            case CMD_JMP_L:
                if ((i = jmp_l_cmd (CPU, cmd_quantity, &data, i)) == -1) ++check;

                break;
            case CMD_JMP_MEQ:
                if ((i = jmp_meq_cmd (CPU, cmd_quantity, &data, i)) == -1) ++check;

                break;
            case CMD_JMP_LEQ:
                if ((i = jmp_leq_cmd (CPU, cmd_quantity, &data, i)) == -1) ++check;

                break;
            case CMD_CALL:
                if ((i = call_cmd (CPU, cmd_quantity, &data, &get_adr, i)) == -1) ++check;

                break;
            case CMD_RET:
                if ((i = ret_cmd (CPU, cmd_quantity, &data, &get_adr, i)) == -1) ++check;

                break;
            case CMD_OUT:
                if (out_cmd (CPU, cmd_quantity, &data, i) != 0) ++check;

                break;
            case CMD_END:
                printf ("Programm succesfully finished its working\n");
                ++end_check;
                i = cmd_quantity;

                break;
            case CMD_HLT:
                hlt_cmd();
                ++end_check;
                i = cmd_quantity;

                break;
            case CMD_PUSH_R:
                if (push_r_cmd (CPU, cmd_quantity, &data, i) != 0) ++check;

                break;
            case CMD_POP_R:
                if (pop_r_cmd (CPU, cmd_quantity, &data, i) != 0) ++check;

                break;
        }
    }

    for (int i = 0; i < 4; i++)
    {
        printf ("CPU.registr[%d] = %d\n", i, CPU.registr[i]);
    }

    destroy (&data);
    destroy (&get_adr);

    free (CPU.command);
    free (CPU.registr);

    if (check != 0) return 1;
    else if (end_check == 0)
    {
        printf ("SegFault\n");

        return 2;
    }
    else return 0;
}

int Fill_Cmd_Info (cpu CPU, char * input, int input_size) {
    FILE * potok = fopen (input, "rb");
    int i = 0;

    int cmd_quantity = fread (CPU.command, sizeof (type), input_size, potok);

    printf ("Command quantity: %d\n\n", cmd_quantity);
    for (i = 0; i < cmd_quantity; i++)
    {
        printf ("%d ", CPU.command[i]);
    }
    printf ("\n");

    fclose (potok);

    return cmd_quantity;
}

int push_cmd (cpu CPU, int cmd_quantity, Stack * data, int num) {
    if (num + 1 >= cmd_quantity) {
        printf ("Please write argument for command: push. This command has number: %d\n", num);
        print_err4;

        return 1;
    }

    push (data, CPU.command[++num]);

    return 0;
}

int pop_cmd (cpu CPU, int cmd_quantity, Stack * data, int num) {
    if (is_empty (data) != 0)
    {
        print_err6 ("pop", num);
        print_err4;

        return 1;
    }

    pop (data);

    return 0;
}

int add_cmd (cpu CPU, int cmd_quantity, Stack * data, int num) {
    if (data -> ptr < 2)
    {
        print_err6 ("add", num);
        print_err4;

        return 1;
    }

    Data res = (data -> data)[data -> ptr - 1] + (data -> data)[(data -> ptr) - 2];

    //printf ("Data ptr: %d\n", data -> ptr);

    printf ("Add res: %d\n", res);

    push (data, res);

    return 0;
}

int sub_cmd (cpu CPU, int cmd_quantity, Stack * data, int num) {
    if (data -> ptr < 2)
    {
        print_err6 ("sub", num);
        print_err4;

        return 1;
    }

    Data res = (data -> data)[(data -> ptr) - 1] - (data -> data)[(data -> ptr) - 2];

    //printf ("Sub res: %d\n", res);

    push (data, res);

    return 0;
}

int div_cmd (cpu CPU, int cmd_quantity, Stack * data, int num) {
    if (data -> ptr < 2)
    {
        print_err6 ("div", num);
        print_err4;

        return 1;
    }

    Data res = (data -> data)[data -> ptr - 1] / (data -> data)[(data -> ptr) - 2];

    //printf ("Div res: %d\n", res);

    push (data, res);

    return 0;
}

int mul_cmd (cpu CPU, int cmd_quantity, Stack * data, int num) {
    if (data -> ptr < 2)
    {
        print_err6 ("mul", num);
        print_err4;

        return 1;
    }

    Data res = (data -> data)[data -> ptr - 1] * (data -> data)[(data -> ptr) - 2];

    printf ("Mul res: %d\n", res);

    push (data, res);

    return 0;
}

int jmp_cmd (cpu CPU, int cmd_quantity, Stack * data, int num) {
    if (CPU.command[num + 1] == -1)
    {
        print_err5("jmp", num);
        print_err4;

        return -1;
    }

    return CPU.command[num + 1] - 1;
}

int jmp_neq_cmd (cpu CPU, int cmd_quantity, Stack * data, int num) {
    if (CPU.command[num + 1] == -1)
    {
        print_err5("jmp", num);
        print_err4;

        return -1;
    }
    if (data -> ptr < 2)
    {
        print_err6 ("jmpneq", num);
        print_err4;

        return 1;
    }

    if ((data -> data)[data -> ptr - 1] != (data -> data)[(data -> ptr) - 2]) return CPU.command[num + 1] - 1;
    else return num;
}

int jmp_eq_cmd (cpu CPU, int cmd_quantity, Stack * data, int num) {
    if (CPU.command[num + 1] == -1)
    {
        print_err5("jmp", num);
        print_err4;

        return -1;
    }
    if (data -> ptr < 2)
    {
        print_err6 ("jmpeq", num);
        print_err4;

        return 1;
    }

    if ((data -> data)[data -> ptr - 1] == (data -> data)[(data -> ptr) - 2]) return CPU.command[num + 1] - 1;
    else return num;
}

int jmp_meq_cmd (cpu CPU, int cmd_quantity, Stack * data, int num) {
    if (CPU.command[num + 1] == -1)
    {
        print_err5("jmp", num);
        print_err4;

        return -1;
    }
    if (data -> ptr < 2)
    {
        print_err6 ("jmpmeq", num);
        print_err4;

        return 1;
    }

    if ((data -> data)[data -> ptr - 1] >= (data -> data)[(data -> ptr) - 2]) return CPU.command[num + 1] - 1;
    else return num;
}

int jmp_leq_cmd (cpu CPU, int cmd_quantity, Stack * data, int num) {
    if (CPU.command[num + 1] == -1)
    {
        print_err5("jmp", num);
        print_err4;

        return -1;
    }
    if (data -> ptr < 2)
    {
        print_err6 ("jmpleq", num);
        print_err4;

        return 1;
    }

    if ((data -> data)[data -> ptr - 1] <= (data -> data)[(data -> ptr) - 2]) return CPU.command[num + 1] - 1;
    else return num;
}

int jmp_m_cmd (cpu CPU, int cmd_quantity, Stack * data, int num) {
    if (CPU.command[num + 1] == -1)
    {
        print_err5("jmp", num);
        print_err4;

        return -1;
    }
    if (data -> ptr < 2)
    {
        print_err6 ("jmpm", num);
        print_err4;

        return 1;
    }

    if ((data -> data)[data -> ptr - 1] > (data -> data)[(data -> ptr) - 2]) return CPU.command[num + 1] - 1;
    else return num;
}

int jmp_l_cmd (cpu CPU, int cmd_quantity, Stack * data, int num) {
    if (CPU.command[num + 1] == -1)
    {
        print_err5("jmp", num);
        print_err4;

        return -1;
    }
    if (data -> ptr < 2)
    {
        print_err6 ("jmpl", num);
        print_err4;

        return 1;
    }

    if ((data -> data)[data -> ptr - 1] < (data -> data)[(data -> ptr) - 2]) return CPU.command[num + 1] - 1;
    else return num;
}

int out_cmd (cpu CPU, int cmd_quantity, Stack * data, int num) {
    if (data -> ptr == 0)
    {
        print_err6("out", num);
        print_err4;

        return 1;
    }

    //printf ("Out value is: %d\n", (data -> data)[data -> ptr - 1]);

    printf ("%d\n", (data -> data)[data -> ptr - 1]);

    return 0;
}

int hlt_cmd () {
    printf ("Shutdown in\n"
            "3...\n");

    sleep (1);

    printf ("2...\n");

    sleep (1);

    printf ("1...\n");

    sleep (2);

    printf ("Okay, that was a joke.\n"
            "Please don't use command hlt on real assembler.\n");

    return 0;
}

int push_r_cmd (cpu CPU, int cmd_quantity, Stack * data, int num){
    if (data -> ptr == 0)
    {
        print_err6("push", num);
        print_err4;

        return 1;
    }

    CPU.registr[CPU.command[num + 1]] = (data -> data)[data -> ptr - 1];

    return 0;
}

int pop_r_cmd (cpu CPU, int cmd_quantity, Stack * data, int num) {
    if (CPU.registr[CPU.command[num + 1]] == empty_num)
    {
        print_err6("pop", num);
        print_err4;

        return 1;
    }

    CPU.registr[CPU.command[num + 1]] = empty_num;

    return 0;
}

void fill_registr (cpu CPU) {
    for (int i = 0; i < 4; i++)
    {
        CPU.registr[i] = empty_num;
    }

    return;
}

int call_cmd (cpu CPU, int cmd_quantity, Stack * data, Stack * get_adr, int num) {
    if (CPU.command[num + 1] == -1)
    {
        print_err5("call", num);
        print_err4;

        return -1;
    }

    push (get_adr, num);

    return CPU.command[num + 1] - 1;
}

int ret_cmd (cpu CPU, int cmd_quantity, Stack * data, Stack * get_adr, int num) {
    if (is_empty (data) != 0)
    {
        print_err6 ("ret", num);
        print_err4;

        return 1;
    }

    int ret = 0;

    ret = (get_adr -> data)[get_adr -> ptr - 1];

    pop (get_adr);

    return ret;
}