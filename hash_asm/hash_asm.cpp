#include "hash_asm.h"



int GNU_hash(const char* string, char stopper) {
    //assert(string);

    register int h = 5381;

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

    return search_comp(cur_count, cur_elem, word);
}

char* search_comp(size_t cur_count, list_elem* cur_elem, const char* word) {
    /*while(cur_count) {
        register int i = 0;

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

    return nullptr;*/



    asm(   ".L16:\n"
           "\tcmpq\t$0, -16(%rbp)\n"
           "\tje\t.L8\n"
           "\tmovl\t$0, %ebx\n"
           ".L12:\n"
           "\tmovslq\t%ebx, %rdx\n"
           "\tmovq\t-32(%rbp), %rax\n"
           "\taddq\t%rdx, %rax\n"
           "\tmovzbl\t(%rax), %eax\n"
           "\ttestb\t%al, %al\n"
           "\tje\t.L9\n"
           "\tmovslq\t%ebx, %rdx\n"
           "\tmovq\t-32(%rbp), %rax\n"
           "\taddq\t%rdx, %rax\n"
           "\tmovzbl\t(%rax), %edx\n"
           "\tmovq\t-24(%rbp), %rax\n"
           "\tmovq\t(%rax), %rcx\n"
           "\tmovslq\t%ebx, %rax\n"
           "\taddq\t%rcx, %rax\n"
           "\tmovzbl\t(%rax), %eax\n"
           "\tcmpb\t%al, %dl\n"
           "\tjne\t.L18\n"
           "\taddl\t$1, %ebx\n"
           "\tnop\n"
           "\tjmp\t.L12\n"
           ".L18:\n"
           "\tnop\n"
           ".L9:\n"
           "\tmovslq\t%ebx, %rdx\n"
           "\tmovq\t-32(%rbp), %rax\n"
           "\taddq\t%rdx, %rax\n"
           "\tmovzbl\t(%rax), %eax\n"
           "\ttestb\t%al, %al\n"
           "\tje\t.L13\n"
           "\tsubq\t$1, -16(%rbp)\n"
           "\tmovq\t-24(%rbp), %rax\n"
           "\tmovq\t8(%rax), %rax\n"
           "\tmovq\t%rax, -24(%rbp)\n"
           "\tjmp\t.L16\n"
           ".L13:\n"
           "\tmovq\t-24(%rbp), %rax\n"
           "\tmovq\t(%rax), %rax\n"
           "\tjmp\t.L15\n"
           ".L8:\n"
           "\tmovl\t$0, %eax\n"
           ".L15:\n"
           "\tpopq\t%rbx\n");
}
