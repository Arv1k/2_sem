#ifndef BACKEND_BACKEND_H
#define BACKEND_BACKEND_H


#include "../../../1_sem/make_enc/enc.h"
#include "tree/binary_tree.h"
#include <cstdio>


const size_t yad_local = 1109;

struct Variables {
    char* name_var = nullptr;
    size_t place_var = 0;
};

struct Function {
    char* name = nullptr;
    tree* tree_func = nullptr;
    size_t var_num = 0;
    Variables var[10] = {};
};



void make_std_tree(tree* name_tree, char* buffer);
tree_elem* get_tree();



#endif //BACKEND_BACKEND_H
