#include "hash_asm.h"

int main(int argc, char* argv[]) {
    /*
    if (argc < 2) {
        printf("Where is the source file?\n");

        return 0;
    }*/

    list hash_table[1000] = {};

    str* dictfull = Fill_the_Addresses("dictfull.txt");

    str* tmpfull = dictfull;


    int hash_sum = 0;
    while(tmpfull->String) {
        hash_sum = GNU_hash(tmpfull->String, ':');

        hash_table[hash_sum].push_front(tmpfull->String);

        tmpfull++;
    }

    //for (int i = 0; i < 1000; i++) hash_table[i].list_dump();

    str* dict = Fill_the_Addresses("dict.txt");
    str* tmp = dict;

    for (int i = 0; i < 100; i++) {
        char *hey = nullptr;
        while (tmp->String) {
            hey = find_word(hash_table, tmp->String);

            if (hey) printf("%s\n", hey);
            else     printf("Nope!\n");

            tmp++;
        }
        tmp = dict;
    }

    free(dict->String);
    free(dict);

    free(dictfull->String);
    free(dictfull);
}
