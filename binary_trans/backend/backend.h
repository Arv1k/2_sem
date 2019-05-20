#ifndef BACKEND_BACKEND_H
#define BACKEND_BACKEND_H


#include "../../../1_sem/make_enc/enc.h"
#include "tree/binary_tree.h"
#include <cstdio>


const size_t yad_place_var = 1607;
const size_t yad_var_num = 5678;

struct Variables {
    char* name_var = nullptr;
    size_t place_var = 0;
};

struct Function {
    char* name = nullptr;
    tree* tree_func = nullptr;
    size_t given_num = 0;
    size_t var_num = 0;
    size_t sdvig = 0;
    Variables var[10] = {};
};


enum {
    M_B = 0x42,
    M_s = 0x73,
    M_O = 0x4f,
    M_I = 0x49,
    M_i = 0x69,
    M_N = 0x4e,
    M_R = 0x52,
    M_V = 0x56,
    M_L = 0x4c,
    M_S = 0x53,
    M_C = 0x43,
    M_P = 0x50,
    M_e = 0x45,
};


void FunctionDtor(Function* funcs);

void make_std(char* buffer, Function* funcs);

tree_elem* get_tree(Function* funcs);

void std_tree_dot(tree* nameTree, char* dot_out);

void create_std_tree(tree_elem* pos, FILE* dot_out);

void print_std_mode(tree_elem* pos, FILE* dot_out);

void make_elf(Function* funcs, char* base_name, char* elf_name);

char* translate_funcs(Function* funs);

size_t Compile_tree(Function* curr_func, Function* func_table, char* start_pos);

void push_func_addr(char* name, Function* func_table, char* start_pos);

void transform_var_table(Function* curr_func);

void compile_node(tree_elem* curr_node, Variables* arr_of_vars, Function* arr_of_func);

void cut_stack(Variables* arr_of_vars);

void aligh_stack(Variables* arr_of_vars);

int find_var(char* name, Variables* arr_of_var);

void add();

void div();

void cmp();

void sub();

void mul();

void num(int number);

void scan();

void print();



#endif //BACKEND_BACKEND_H
