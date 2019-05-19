#include "backend.h"

Function funcs[10] = {};

size_t CounT = 0;

char* pc = nullptr;
void make_std_tree(tree* name_tree, char* buffer) {
    assert(name_tree);
    assert(buffer);

    pc = buffer;

    int i = 0;
    int j = 0;

    assert(*pc == '#');

    pc++;

    char* tmp = pc;
    pc = strchr(pc, ' ');
    *pc++ = '\0';

    assert(*pc == '(');
    funcs[i].name = tmp;

    pc += 2;
    if (*pc != ')') {
        tmp = pc;
        pc = strchr(pc, ' ');
        *pc++ = '\0';

        funcs[i].var_num++;
        funcs[i].var[j].name_var = tmp;
        funcs[i].var[j++].place_var++;

        while (*pc == ',') {
            pc += 2;

            tmp = pc;
            pc = strchr(pc, ' ');
            *pc++ = '\0';

            funcs[i].var_num++;
            funcs[i].var[j].name_var = tmp;
            funcs[i].var[j++].place_var++;
        }
    }

    assert(*pc == ')');

    pc += 2;

    assert(*pc == '{');

    funcs[i].tree_func->Tamyr = get_tree();
    funcs[i].tree_func->count = CounT;
}

tree_elem* get_tree() {



}
