#include "tree.h"

int main(int argc, char * argv[]) {
    tree* curr = nullptr;
    curr = (tree*) calloc (1, sizeof (tree));

    FILE* potok = nullptr;
    text my_text;

    if (open_file (potok, argv[1], &my_text) != 0)
    {
        print_err;
    }

    int num = 0;

    for (int i = 0; i < my_text.str_quantity; i++)
    {
        printf ("str_len[%d]: %d\n", i, my_text.text_info[i].str_len);
    }
    printf ("%s\n", my_text.text_info[4].str_adr);

    fill_tree (curr, &my_text, &num);
    ask_user  (curr);
    if (fprint_tree (curr, argv[1]) != 0)
    {
        printf ("Error\n");
        fflush (stdout);
    }

    fprint_tree2 (curr, argv[2]);

    my_text.destroy_text();

    destroy_tree (curr);
}

int symbcount (char * name) {
    struct stat buf;
    if(stat (name, &buf) == -1)
    {
        printf("Programm couldn't fill stat \nProgramm: %s \nLine: %d\n", __FILE__, __LINE__);
        fflush (stdout);

        return -1;
    }

    return buf.st_size;
}

int fprint_tree (tree* curr, char* input)
{
    FILE* potok = nullptr;

    if((potok = fopen(input, "w")) == nullptr) return 1;
    get_tree (curr, potok);

    return 0;
}

int fprint_tree2 (tree* curr, char* input)
{
    FILE* potok = nullptr;

    if((potok = fopen(input, "w")) == nullptr) return 1;

    fprintf (potok, "digraph test {\n");
    get_tree2 (curr, potok);
    fprintf (potok, "}");

    return 0;
}
void get_tree2  (tree* curr, FILE* potok)
{
    if (curr -> left != nullptr)
    {
        fprintf  (potok,"\"%s\" -> \"%s\";\n", curr -> str, curr -> left -> str);
        get_tree2 (curr -> left, potok);
    }
    if (curr -> right != nullptr)
    {
        fprintf  (potok,"\"%s\" -> \"%s\";\n", curr -> str, curr -> right -> str);
        get_tree2 (curr -> right, potok);
    }
}

int open_file(FILE* potok, char* input, text* my_text) {
    if ((my_text -> size = symbcount (input)) <= 0) return 1;
    my_text -> arr = (char *) calloc (my_text -> size, sizeof (char));

    if((potok = fopen(input, "rt")) == nullptr) return 1;
    fread (my_text -> arr, sizeof(char), my_text -> size, potok);

    my_text -> str_quantity = strcount (my_text -> arr, my_text -> size);
    if ((my_text -> text_info = (info *) calloc (my_text -> str_quantity, sizeof (info))) == nullptr) return 1;

    fill_info (my_text -> size, my_text -> arr, my_text -> str_quantity, my_text -> text_info);

    return 0;
}

void fill_info (int symb_quantity, char *text, int str_quantity, info *text_info)
{
    int i = 0;
    int quant = 0;
    int j = 0;
    char *adr = &text[0];

    for(i = 0; i < symb_quantity; i++)
    {
        //printf ("text[%d]: %d\n", i, text[i]);

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

void fill_tree (tree* curr, text* txt, int* num) {
    curr -> str = (char*) calloc (txt -> text_info[*num].str_len + 1, sizeof (char));
    int i = 0;
    for (i = 0; *num < txt -> str_quantity && i < txt -> text_info[*num].str_len; i++)
    {
        curr -> str[i] = txt -> text_info[*num].str_adr[i];
    }

    curr -> str[i] = 0;
    printf ("%s\n", curr -> str);

    ++(*num);
    //printf ("NUM: %d\n", *num);

    if (*num < txt -> str_quantity && txt -> text_info[*num].str_adr[0] == '{')
    {
        curr -> left = (tree*) calloc (1, sizeof (tree));
        ++(*num);
        //printf ("Pointer to left: %p\n", curr -> left);
        fill_tree (curr -> left, txt, num);
        //printf ("txt: %s\n", txt -> text_info[*num].str_adr);

        if (((*num)) < txt -> str_quantity && txt -> text_info[*num].str_adr[0] == '{')
        {
            *num = (*num) + 1;

            curr -> right = (tree*) calloc (1, sizeof (tree));
            fill_tree (curr -> right, txt, num);
        }
        else if (((*num)) < txt -> str_quantity && txt -> text_info[*num].str_adr[0] == '}')
        {
            (*num) = (*num) + 1;
        }
    }

    if (*num < txt -> str_quantity && txt -> text_info[*num].str_adr[0] == '}')
        ++(*num);
}

void get_tree  (tree* curr, FILE* potok) {
    fflush (potok);
    fprintf (potok,"%s\n", curr -> str);

    if (curr -> left != nullptr)
    {
        fprintf  (potok,"{\n");
        get_tree (curr -> left, potok);
        fprintf  (potok, "}\n");
    }
    if (curr -> right != nullptr)
    {
        fprintf  (potok, "{\n");
        get_tree (curr -> right, potok);
        fprintf  (potok, "}\n");
    }
}

void destroy_tree (tree* curr)
{
    if (curr -> left != nullptr)
        destroy_tree (curr -> left);
    if (curr -> right != nullptr)
        destroy_tree (curr -> right);

    free (curr -> str);
    free (curr);
}

void ask_user (tree* curr)
{
    printf ("Want to find something? [y/n]:");
    fflush (stdout);

    int check = 0;
    char ans = '\0';

    while (check == 0)
    {
        int num = 0;
        num = scanf ("%c", &ans);

        for (int i = 0; i < num + 1; i++)
            fflush (stdin);

        if (ans == 'y' || ans == 'Y')
        {
            work_with_user(curr);
        }
        else if (ans == 'n' || ans == 'N')
        {
            ++check;
        }
        else if (ans == 10)
        {
            printf ("Want to find something else? [y/n]:");
            fflush (stdout);
        }
        else
        {
            printf ("Please write correct answer! %d\n", ans);
            fflush (stdout);
        }
    }
}

void work_with_user (tree* curr)
{
    printf ("Is it %s? [y/n]:", curr -> str);
    fflush (stdout);

    int check = 0;
    char ans  = '\0';
    while (check == 0)
    {
        int num = 0;
        num = scanf ("%c", &ans);

        for (int i = 0; i < num + 1; i++)
            fflush (stdin);

        if (ans == 'y' || ans == 'Y')
        {
            if (curr -> right == nullptr)
            {
                printf ("It is %s! Please write enter to further work.\n", curr -> str);
                fflush (stdout);
                return;
            }
            else
            {
                work_with_user (curr -> right);
                return;
            }
        }
        else if (ans == 'n' || ans == 'N')
        {
            if (curr -> left != nullptr)
            {
                work_with_user (curr -> left);
                return;
            }
            else {
                printf("What word you wanted to find?\n");
                fflush (stdout);

                tree *users = nullptr;
                users = (tree *) calloc(1, sizeof(tree));

                tree *my = nullptr;
                my = (tree *) calloc(1, sizeof(tree));

                my->str = curr->str;
                my->left = nullptr;
                my->right = nullptr;

                users->str = (char *) calloc(100, sizeof(char));
                users->left = nullptr;
                users->right = nullptr;

                num = scanf("%s", users->str);
                for (int i = 0; i < num + 1; i++)
                    fflush (stdin);

                printf("What is the difference between %s and %s?\n", my->str, users->str);
                fflush (stdout);

                curr->str = (char *) calloc(100, sizeof(char));

                fflush(stdout);
                fgets(curr -> str, 100, stdin);

                for (int i = 0; i < 100; i++)
                {
                    fflush (stdin);
                    if (curr -> str[i - 1] == '\n')
                    {
                        curr -> str[i - 1] = '\0';
                        break;
                    }
                }

                curr -> left  = my;
                curr -> right = users;

                return;
            }
        }
    }
}