//TODO:
// - помнить, что все задания написанные в туду, являюьтся заданиями для того файла, где они написаны
// - почитать про функцию system ()
// - реализовать возможность ввода команды, при которой не будет создаваться файл с машинным кодом, а мы будем сразу переходить к компиляции программы на процессоре

#include <stdlib.h>

int CodeTranslator (char * input, char * output);
int CodeExecuter   (char * output);

int main (int argc, char * argv[]) {
    int return_value = 0;

    if (CodeTranslator (argv[1], argv[2]) != 0)
    {
        return 1;
    }

    if (CodeExecuter (argv[2]) != 0)
    {
        return 1;
    }

    return 0;
}
