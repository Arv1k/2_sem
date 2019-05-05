#include "hash_asm.h"

int ASCII_sum(const char* string, size_t num_sym) {
    assert(string);

    int hash_sum = 0;

    for (int i = 0; i < num_sym; i++)
        hash_sum += *(string);

    return hash_sum;
}

int ASCII_sum_div_len(const char* string, size_t num_sym) {
    assert(string);

    int hash_sum = ASCII_sum(string, num_sym);

    if (!hash_sum) return 0;

    return hash_sum / num_sym;
}

int GNU_hash(const char* string, char stopper) {
    assert(string);

    int h = 5381;

    for (unsigned char c = *string; c != stopper; c = *++string)
        h = h * 33 + c;

    h %= 1000;

    return (h < 0)? -h : h;
}
//----------------------------------------------------------------------------------------------------------------------

/**
 * 72,41
 * @param hash_table
 * @param word
 * @return
 */
char* find_word(const list* hash_table, const char* word) {
    //assert(hash_table);
    //  assert(word);

    int hash_sum = GNU_hash(word, '\0'); //!

    //list cur_list = hash_table[hash_sum];

    size_t cur_count = hash_table[hash_sum].size(); //!
    list_elem* cur_elem = hash_table[hash_sum].head(); //!

//    const char* tmp_word = nullptr;
//    char* tmp_Info = nullptr;

    while(cur_count) {
//        tmp_Info = cur_elem->Info;
//        tmp_word = word;

        int i = 0;

//        while(word[i] && word[i] == cur_elem->Info[i])
//            i++;


        while(word[i]) {
            if (word[i] == cur_elem->Info[i]) {
                i++;
                continue;
            }

            break;
        }

        if (word[i]) {
            cur_count--;
            cur_elem = cur_elem->Next;
        }

        else return cur_elem->Info;
    }

    return nullptr;
}


/**
 * 88,17
 * Better, but not the best
 */

/*char* find_word(const list* hash_table, const char* word) {
    //assert(hash_table);
    //assert(word);

    int hash_sum = GNU_hash(word, '\0');

    //list cur_list = hash_table[hash_sum];

    size_t cur_count = hash_table[hash_sum].size();
    list_elem* cur_elem = hash_table[hash_sum].head();

    const char* tmp_word = nullptr;
    char* tmp_Info = nullptr;

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
}*/

/** 94,56
 * Too long
 */
/*char* find_word(const list* hash_table, const char* word) {
    assert(hash_table);
    assert(word);

    int hash_sum = GNU_hash(word, '\0');

    size_t cur_count = hash_table[hash_sum].size();
    list_elem* cur_elem = hash_table[hash_sum].head();

    char* tmp_Info = nullptr;

    size_t word_length = strchr(word, '\0') - word;
    int i = 0;

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
}*/
