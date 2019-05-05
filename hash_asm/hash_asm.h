#ifndef HASH_ASM_HASH_ASM_H
#define HASH_ASM_HASH_ASM_H



#include "list/list.h"
#include "../1_sem/make_enc/enc.h"

int ASCII_sum(const char* string, size_t num_sym);

int ASCII_sum_div_len(const char* string, size_t num_sym);

int GNU_hash(const char* string, char stopper);

char* find_word(const list* hash_table, const char* word);



#endif //HASH_ASM_HASH_ASM_H
