#include "hash_asm.h"

unsigned long curr_tick_num() {
    unsigned int High, Low;
    asm volatile(   ".intel_syntax noprefix\n\t"
                    "RDTSC\n\t"
                    ".att_syntax prefix\n\t"
    :"=a"(Low), "=d"(High)
    :
    :"cc");
    return ((unsigned long)High << 32 | Low);
}

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
 * ~0,29 sec
 * @param hash_table
 * @param word
 * @return6
 */
char* find_word(const list* hash_table, const char* word) {
    //assert(hash_table);
    //assert(word);

    int hash_sum = GNU_hash(word, '\0'); //!

    size_t cur_count = hash_table[hash_sum].size(); //!
    list_elem* cur_elem = hash_table[hash_sum].head(); //!

    //FILE* ticks = fopen("ticks.txt", "a+");

    unsigned long you = curr_tick_num();
    char* hey = search_comp(cur_count, cur_elem, word);
    you = curr_tick_num() - you;

    printf("%ld\n", you);

    //fclose(ticks);
    return hey;
}

// char* search_comp(size_t cur_count, list_elem* cur_elem, const char* word) {
//     while(cur_count) {
//         register int i = 0;
//
//         while(word[i]) {
//             if (word[i] == cur_elem->Info[i]) {
//                 i++;
//                 continue;
//             }
//
//             break;
//         }
//
//         if (word[i]) {
//             cur_count--;
//             cur_elem = cur_elem->Next;
//         }
//
//         else return cur_elem->Info;
//     }
//
//     return nullptr;
// }
