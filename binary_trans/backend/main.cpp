#include "backend.h"

int main(int argc, char* argv[]) {
    FILE* max = fopen(argv[1], "rb");
    long num_symbols = Size(max);

    char* buffer = (char*) calloc(num_symbols + 1, sizeof(char));

    fread(buffer, sizeof(char), num_symbols, max);
    fclose(max);

    tree TrEE = {};

    make_std_tree(&TrEE, buffer);

    free(buffer);
}