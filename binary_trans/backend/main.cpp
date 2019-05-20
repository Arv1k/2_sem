#include "backend.h"

int main(int argc, char* argv[]) {
    FILE* max = fopen(argv[1], "rb");
    long num_symbols = Size(max);

    char* buffer = (char*) calloc(num_symbols + 1, sizeof(char));

    fread(buffer, sizeof(char), num_symbols, max);
    fclose(max);

    Function funcs[10] = {};

    make_std(buffer, funcs);

    for (int j = 0; j < 10; j++)
        if (funcs[j].tree_func)
            std_tree_dot(funcs[j].tree_func, argv[2]);

    make_elf(funcs, argv[3], argv[4]);

    for (int i = 0; i < 10; i++)
        if (funcs[i].tree_func) FunctionDtor(&(funcs[i]));

    free(buffer);
}