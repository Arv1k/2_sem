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
 * ~0,50 sec
 * Too long
 */
char* find_word(const list* hash_table, const char* word) {
    // assert(hash_table);
    // assert(word);

    int hash_sum = GNU_hash(word, '\0');

    size_t cur_count = hash_table[hash_sum].size();
    list_elem* cur_elem = hash_table[hash_sum].head();

    return search_comp(cur_count, cur_elem, word);
}

char* search_comp(size_t cur_count, list_elem* cur_elem, const char* word) {
    register char* tmp_Info = nullptr;

    register size_t word_length = strlen(word);
    register unsigned int i = 0;

    while(cur_count) {
        tmp_Info = cur_elem->Info;

        i = 0;
        for (; i < word_length; i++) {
            if (word[i] == tmp_Info[i])
                continue;

            break;
        }

        if (i != word_length) {
            cur_count--;
            cur_elem = cur_elem->Next;
        }

        else return cur_elem->Info;
    }

    return nullptr;
}
