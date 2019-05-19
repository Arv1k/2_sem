#include "backend.h"

int main(int argc, char* argv[]) {
    FILE* max = fopen(argv[1], "rb");
    long num_symbols = Size(max);

    char* buffer = (char*) calloc(num_symbols + 1, sizeof(char));

    fread(buffer, sizeof(char), num_symbols, max);
    fclose(max);

    Function funcs[10] = {};

    make_std(buffer, funcs);

    //std_tree_dot(funcs[0].tree_func, argv[2]);
    //std_tree_dot(funcs[1].tree_func, argv[2]);

    for (int i = 0; i < 10; i++)
        if (funcs[i].tree_func) FunctionDtor(&(funcs[i]));

    free(buffer);
}