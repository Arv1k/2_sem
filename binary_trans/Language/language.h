#ifndef LANGUAGE_LANGUAGE_H
#define LANGUAGE_LANGUAGE_H


#include "cstdio"
#include "../../../1_sem/make_enc/enc.h"
#include "tree/binary_tree.h"


#define dassert(pointer) {\
    if (!pointer) {\
        printf("| !!! Dassertion failed !!!\n");\
        printf("|       what: %s is nullptr\n", #pointer);\
        printf("|       in: %s,\n", __FILE__);\
        printf("|       function: %s,\n",  __PRETTY_FUNCTION__);\
        printf("|       on: %d line.\n", __LINE__);\
        abort();\
    }\
}

#define pc_assert(statement) {\
    if ( !(statement) ) {\
        printf("| !!! Pc_assertion failed !!!\n");\
        printf("|       what: expected %d instead 0\n", *pc);\
        printf("|       in: %s,\n", __FILE__);\
        printf("|       function: %s,\n",  __PRETTY_FUNCTION__);\
        printf("|       on: %d line.\n", __LINE__);\
        abort();\
        }\
}


const int max_word = 1000;

enum {
    #define CMD_FORM(com, len, num, code) OP_##com = num,

    #include "com.h"

    #undef CMD_FORM

    ELE    = 97,
    EGER   = 98,
    OP_TOP = 99,
    KURSET = 100,
    EIT    = 101,
    TUDY   = 102,
    BU     = 103,
    BIR    = 104,
};

void makeTree(tree* nameTree, char* buffer);

// F ::= баш "" '\n'-----'\n' G '\n'-----'\n' {Id "{Id;}+" '\n'-----'\n' G '\n'-----'\n'}*
tree_elem* GetF(char* buff);

// G ::= {To','}* {To'.'}\0'
tree_elem* GetG();

// To ::= L | A | If
tree_elem* GetTo();

// L ::= әле "C": {To','}+ {To'.'} | әле "C" To
tree_elem* GetL();

// If ::= әгәр "C": {To','}* {To'.'} | әгәр "C" To
tree_elem* GetIf();

// A ::= Id бу E | Id туды | Id әйт | "E" күрсәт | Id "{Id; }*" | {"E" бир | Id бир}
tree_elem* GetA();

// C ::= {(E) | N} {(E) | N} [зуррак | кечкенәрәк | тигез | түгeл]
tree_elem* GetC();

// E ::= T{[+-]T}*
tree_elem* GetE();

// T ::= P{[*/]P}*
tree_elem* GetT();

// P ::= (E) | sin(E) | cos(E) | ln(E) | lg(E) | N | Id
tree_elem* GetP();

// N ::= [0-9]{[0-9]}* | Id
tree_elem* GetN();

// Id ::= [a-z & A-Z]{[a-z & A-Z]}*
tree_elem* GetId();


int which_To();

int which_A();

char* which_word();

void tree_dot(tree* nameTree, char* dot_out);

void create_tree(tree_elem* pos, FILE* dot_out);

void print_mode(tree_elem* pos, FILE* dot_out);

void write_as_std_tree(tree* nameTree, char* buffer);

void std_tree_filling(tree_elem* pos);

void take_params(tree_elem* pos);

void take_body(tree_elem* pos);



#endif //LANGUAGE_LANGUAGE_H
