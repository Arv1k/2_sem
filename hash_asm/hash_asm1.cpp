#include "hash_asm.h"


int GNU_hash(const char* string, char stopper) {
    //assert(string);

    int h = 5381;

    for (unsigned char c = *string; c != stopper; c = *++string)
        h = h * 33 + c;

    h %= 1000;

    return (h < 0)? -h : h;
}
//----------------------------------------------------------------------------------------------------------------------
/**
 * ~0,33 sec
 * Better, but not the best
 */
char* find_word(const list* hash_table, const char* word) {
    //assert(hash_table);
    //assert(word);

    int hash_sum = GNU_hash(word, '\0');

    size_t cur_count = hash_table[hash_sum].size();
    list_elem* cur_elem = hash_table[hash_sum].head();

    return search_comp(cur_count, cur_elem, word);
}

char* search_comp(size_t cur_count, list_elem* cur_elem, const char* word) {
    register const char* tmp_word = nullptr;
    register char*       tmp_Info = nullptr;

    while(cur_count) {
        tmp_Info = cur_elem->Info;
        tmp_word = word;

        while(*tmp_word) {
            if (*tmp_word == *tmp_Info) {
                tmp_word++;
                tmp_Info++;
                continue;
            }

            break;
        }

        if (*tmp_word) {
            cur_count--;
            cur_elem = cur_elem->Next;
        }

        else return cur_elem->Info;
    }

    return nullptr;
}
