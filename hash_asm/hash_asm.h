#ifndef HASH_ASM_HASH_ASM_H
#define HASH_ASM_HASH_ASM_H



#include "list/list.h"
#include "../../1_sem/make_enc/enc.h"


int GNU_hash(const char* string, char stopper);

char* find_word(const list* hash_table, const char* word);

char* search_comp(size_t cur_count, list_elem* cur_elem, const char* word);




#endif //HASH_ASM_HASH_ASM_H
