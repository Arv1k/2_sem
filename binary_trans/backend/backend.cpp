#include "backend.h"

void FunctionDtor(Function* func) {
    free(func->name);
    TreeDtor(func->tree_func);

    func->tree_func = nullptr;

    func->var_num = yad_var_num;

    for (int i = 0; i < 10; i++) {
        if (func->var[i].name_var) free(func->var[i].name_var);
        func->var[i].place_var = yad_place_var;
    }
}

size_t CounT = 0;
int i = 0;
int j = 0;
int k = 0;

char* pc = nullptr;
void make_std(char* buffer, Function* funcs) {
    assert(buffer);
    assert(funcs);

    pc = buffer;

    while (*pc) {
        assert(*pc == '#');

        pc++;

        char *tmp = pc;
        pc = strchr(pc, '(');
        *pc = '\0';


        funcs[i].name = strdup(tmp);
        *pc++ = '(';
        pc++;

        if (*pc != ')') {
            tmp = pc;
            pc = strchr(pc, ' ');
            *pc++ = '\0';

            funcs[i].var[j].name_var = strdup(tmp);
            funcs[i].var[j].place_var = j + 1;
            funcs[i].given_num++;
            j++;

            while (*pc == ',') {
                pc += 2;

                tmp = pc;
                pc = strchr(pc, ' ');
                *pc++ = '\0';

                funcs[i].var[j].name_var = strdup(tmp);
                funcs[i].var[j].place_var = j + 1;
                funcs[i].given_num++;
                j++;
            }
        }

        assert(*pc == ')');

        pc++;

        assert(*pc == '{');

        funcs[i].tree_func = new tree;
        TreeCtor(funcs[i].tree_func);

        funcs[i].tree_func->Tamyr = get_tree(funcs);
        funcs[i].tree_func->count = CounT;

        pc++;
        i++;
        j = 0;
        k = 0;
        CounT = 0;
    }
}

tree_elem* get_tree(Function* funcs) {
    assert(*pc == '{');
    pc++;

    char* tmp = nullptr;
    auto val = new tree_elem;

    CounT++;

    switch (*pc) {
        case M_B:
            val->Info.mode = *pc++;

            val->Left  = get_tree(funcs);
            val->Right = get_tree(funcs);

            assert(*pc == '}');
            pc++;

            return val;

        case M_S:
            val->Info.mode   = *pc++;
            val->Info.number = (*pc++) - 0x30;

            val->Left  = get_tree(funcs);
            val->Right = nullptr;

            assert(*pc == '}');
            pc++;

            return val;

        case M_e:
            val->Info.mode = *pc++;

            val->Left  = get_tree(funcs);
            val->Right = get_tree(funcs);

            assert(*pc == '}');
            pc++;

            return val;

        case M_I:
            val->Info.mode = *pc++;

            val->Left  = get_tree(funcs);
            val->Right = get_tree(funcs);

            assert(*pc == '}');
            pc++;

            return val;

        case M_C:
            val->Info.mode = *pc++;

            tmp = pc;
            pc = strchr(pc, '{');

            *pc = '\0';
            val->Info.name = strdup(tmp);
            *pc = '{';


            val->Left  = get_tree(funcs);
            val->Right = nullptr;

            assert(*pc == '}');
            pc++;

            return val;

        case M_s:
            val->Info.mode = *pc++;
            val->Info.number = (int) *pc++;

            val->Left  = get_tree(funcs);
            val->Right = get_tree(funcs);

            assert(*pc == '}');
            pc++;

            return val;

        case M_L:
            val->Info.mode = *pc++;

            val->Left  = get_tree(funcs);
            val->Right = get_tree(funcs);

            assert(*pc == '}');
            pc++;

            return val;

        case M_O:
            val->Info.mode = *pc++;
            val->Info.number = (int) *pc++;

            val->Left  = get_tree(funcs);
            val->Right = get_tree(funcs);

            assert(*pc == '}');
            pc++;

            return val;

        case M_R:
            val->Info.mode = *pc++;

            val->Left  = get_tree(funcs);
            val->Right = nullptr;

            assert(*pc == '}');
            pc++;

            return val;

        case M_N:
            val->Info.mode = *pc++;
            val->Info.number = *((int*) pc);

            pc += 4;

            val->Left = nullptr;
            val->Right = nullptr;

            assert(*pc == '}');
            pc++;

            return val;

        case M_P:
            val->Info.mode = *pc++;

            val->Left = get_tree(funcs);
            val->Right = get_tree(funcs);

            assert(*pc == '}');
            pc++;

            return val;

        case M_i:
            val->Info.mode = *pc++;

            tmp = pc;
            pc = strchr(pc, '}');

            *pc = '\0';
            val->Info.name = strdup(tmp);

            funcs[i].var[j].name_var = val->Info.name;
            funcs[i].var[j].place_var = ++k;
            funcs[i].var_num++;
            j++;


            *pc = '}';

            val->Right = nullptr;
            val->Left  = nullptr;

            pc++;

            return val;

        case M_V:
            val->Info.mode = *pc++;

            tmp = pc;
            pc = strchr(pc, '}');

            *pc = '\0';
            val->Info.name = strdup(tmp);

            *pc = '}';

            pc++;

            return val;

        case '}':
            delete val;
            CounT--;

            pc++;
            return nullptr;
    }
}

void std_tree_dot(tree* nameTree, char* dot_out) {
    assert(dot_out);
    assert_tree(nameTree);

    FILE *file_dot = fopen(dot_out, "wb");
    assert(file_dot);

    fprintf(file_dot, "digraph {\n");
    fprintf(file_dot, "\tnode[color = \"#000000\", fontsize = 20];\n"
                      "\tedge[color = \"#000000\", fontsize = 20];\n");

    create_std_tree(nameTree->Tamyr, file_dot);

    fprintf(file_dot, "}");

    assert(file_dot);
    fclose(file_dot);

    system("dot -Tjpg -o tree.jpg dott.dot");
    system("xviewer tree.jpg");

    assert_tree(nameTree);
}

int tmp = 0;
void create_std_tree(tree_elem* position, FILE* dot_out) {
    assert(dot_out);
    assert(position);

    fprintf(dot_out, "\t\they%d", tmp);
    print_std_mode(position, dot_out);
    fprintf(dot_out, ";\n");

    int iskan = tmp;

    if (position->Left != nullptr) {
        fprintf(dot_out, "\t\they%d", iskan);

        fprintf(dot_out, "->");

        fprintf(dot_out, "hey%d;\n", ++tmp);

        create_std_tree(position->Left, dot_out);
    }

    if (position->Right != nullptr) {
        fprintf(dot_out, "\t\they%d", iskan);

        fprintf(dot_out, "->");

        fprintf(dot_out, "hey%d;\n", ++tmp);

        create_std_tree(position->Right, dot_out);
    }

    assert(position);
    assert(dot_out);
}

void print_std_mode(tree_elem* position, FILE* dot_out) {
    assert(position);
    assert(dot_out);

    switch ((position->Info).mode) {
        case M_B:        fprintf(dot_out, "[label = \"B\", shape = \"Mcircle\", "
                                              "color=\"#000000\", style=\"filled\", "
                                              "fillcolor = \"#32CD32\"]");
            break;

        case M_s:      fprintf(dot_out, "[label = \"s %c\", shape = \"diamond\", "
                                              "color=\"#000000\", style=\"filled\", "
                                              "fillcolor = \"#F0E68C\"]", (position->Info).number);
            break;

        case M_O:       fprintf(dot_out, "[label = \"O %c\", shape = \"component\", "
                                              "color=\"#000000\", style=\"filled\", "
                                              "fillcolor = \"#9932CC\"]", (position->Info).number);
            break;

        case M_I:    fprintf(dot_out, "[label = \"I\", shape = \"Msquare\", "
                                              "color=\"#000000\", style=\"filled\", "
                                              "fillcolor = \"#FFA07A\"]");
            break;

        case M_i:      fprintf(dot_out, "[label = \"i %s\", shape = \"invtriangle\", "
                                              "color=\"#000000\", style=\"filled\", "
                                              "fillcolor = \"#00FFFF\"]", (position->Info).name);
            break;

        case M_N: fprintf(dot_out, "[label = \"N %d\", shape = \"egg\", "
                                              "color=\"#000000\", style=\"filled\", "
                                              "fillcolor = \"#FFFFFF\"]", position->Info.number);
            break;

        case M_R:      fprintf(dot_out, "[label = \"R\", shape = \"house\", "
                                              "color=\"#000000\", style=\"filled\", "
                                              "fillcolor = \"#D2691E\"]");
            break;

        case M_V:        fprintf(dot_out, "[label = \"V %s\", shape = \"house\", "
                                              "color=\"#000000\", style=\"filled\", "
                                              "fillcolor = \"#ff6161\"]", position->Info.name);
            break;

        case M_L:       fprintf(dot_out, "[label = \"L\", shape = \"box3d\", "
                                              "color=\"#000000\", style=\"filled\", "
                                              "fillcolor = \"#32CD32\"]");
            break;

        case M_S:        fprintf(dot_out, "[label = \"S %d\", shape = \"box3d\", "
                                              "color=\"#000000\", style=\"filled\", "
                                              "fillcolor = \"#FFDEAD\"]", position->Info.number);
            break;

        case M_C:    fprintf(dot_out, "[label = \"C %s\", shape = \"box3d\", "
                                              "color=\"#000000\", style=\"filled\", "
                                              "fillcolor = \"#708090\"]", position->Info.name);
            break;

        case M_P:      fprintf(dot_out, "[label = \"P\", shape = \"box3d\", "
                                              "color=\"#000000\", style=\"filled\", "
                                              "fillcolor = \"#EE82EE\"]");
            break;

        case M_e:    fprintf(dot_out, "[label = \"E\", shape = \"parallelogram\", "
                                              "color=\"#000000\", style=\"filled\", "
                                              "fillcolor = \"#00b34a\"]");
            break;

        default:             fprintf(dot_out, "\"error\"");
            break;
    }

    assert(position);
    assert(dot_out);
}

void make_elf(Function* funcs, char* elf_name) {
    assert(funcs);
    assert(elf_name);

    FILE* elf = fopen(elf_name, "rb");

    char* buffer = translate_funcs(funcs);

    fclose(elf);
}

char* translate_funcs(Function* funcs) {

}

char* pos = nullptr;

void mul() {
    *pos++ = 0x58; // pop rax
    *pos++ = 0x5b; // pop rbx

    *pos++ = 0x48; // mul rbx
    *pos++ = 0xf7; //
    *pos++ = 0xe3; //

    *pos++ = 0x50; // push rax
}

void num(int number) {
    *pos++ = 0xb8;          // mov rax, number
    *((int*) pos) = number; //
    pos += 4;               //

    *pos++ = 0x50; // push rax
}

void scan() {
    *pos++ = 0x41;
    *pos++ = 0x53;
    *pos++ = 0x56;
    *pos++ = 0x57;
    *pos++ = 0x52;
    *pos++ = 0x51;
    *pos++ = 0x48;
    *pos++ = 0x83;
    *pos++ = 0xec;
    *pos++ = 0x10;
    *pos++ = 0xb8;
    *pos++ = 0x00;
    *pos++ = 0x00;
    *pos++ = 0x00;
    *pos++ = 0x00;
    *pos++ = 0x48;
    *pos++ = 0x89;
    *pos++ = 0xe6;
    *pos++ = 0xba;
    *pos++ = 0x0a;
    *pos++ = 0x00;
    *pos++ = 0x00;
    *pos++ = 0x00;
    *pos++ = 0xbf;
    *pos++ = 0x00;
    *pos++ = 0x00;
    *pos++ = 0x00;
    *pos++ = 0x00;
    *pos++ = 0x0f;
    *pos++ = 0x05;
    *pos++ = 0x48;
    *pos++ = 0x89;
    *pos++ = 0xc1;
    *pos++ = 0x48;
    *pos++ = 0xff;
    *pos++ = 0xc9;
    *pos++ = 0x48;
    *pos++ = 0x31;
    *pos++ = 0xc0;
    *pos++ = 0x41;
    *pos++ = 0xbb;
    *pos++ = 0x0a;
    *pos++ = 0x00;
    *pos++ = 0x00;
    *pos++ = 0x00;
    *pos++ = 0x48;
    *pos++ = 0x31;
    *pos++ = 0xf6;
    *pos++ = 0x8a;
    *pos++ = 0x1c;
    *pos++ = 0x34;
    *pos++ = 0x80;
    *pos++ = 0xeb;
    *pos++ = 0x30;
    *pos++ = 0x49;
    *pos++ = 0xf7;
    *pos++ = 0xe3;
    *pos++ = 0x48;
    *pos++ = 0x01;
    *pos++ = 0xd8;
    *pos++ = 0x48;
    *pos++ = 0xff;
    *pos++ = 0xc6;
    *pos++ = 0xe2;
    *pos++ = 0xef;
    *pos++ = 0x48;
    *pos++ = 0x83;
    *pos++ = 0xc4;
    *pos++ = 0x10;
    *pos++ = 0x59;
    *pos++ = 0x5a;
    *pos++ = 0x5f;
    *pos++ = 0x5e;
    *pos++ = 0x41;
    *pos++ = 0x5b;
    *pos++ = 0x50;
}

void print() {
    *pos++ = 0x55; //ahahahhahahhahahha
    *pos++ = 0x48; //ahahahhahahhahahha
    *pos++ = 0x89; //ahahahhahahhahahha
    *pos++ = 0xe5; //ahahahhahahhahahha
    *pos++ = 0x57; //ahahahhahahhahahha
    *pos++ = 0x56; //ahahahhahahhahahha
    *pos++ = 0x51; //ahahahhahahhahahha
    *pos++ = 0x52; //ahahahhahahhahahha
    *pos++ = 0x41; //ahahahhahahhahahha
    *pos++ = 0x53; //ahahahhahahhahahha
    *pos++ = 0x48; //ahahahhahahhahahha
    *pos++ = 0x83; //ahahahhahahhahahha
    *pos++ = 0xec; //ahahahhahahhahahha
    *pos++ = 0x10; //ahahahhahahhahahha
    *pos++ = 0x48; //ahahahhahahhahahha
    *pos++ = 0x8b; //ahahahhahahhahahha
    *pos++ = 0x45; //ahahahhahahhahahha
    *pos++ = 0x08; //ahahahhahahhahahha
    *pos++ = 0x48; //ahahahhahahhahahha
    *pos++ = 0x31; //ahahahhahahhahahha
    *pos++ = 0xd2; //ahahahhahahhahahha
    *pos++ = 0x48; //ahahahhahahhahahha
    *pos++ = 0x39; //ahahahhahahhahahha
    *pos++ = 0xd0; //ahahahhahahhahahha
    *pos++ = 0x75; //ahahahhahahhahahha
    *pos++ = 0x0c; //ahahahhahahhahahha
    *pos++ = 0xb2; //ahahahhahahhahahha
    *pos++ = 0x30; //ahahahhahahhahahha
    *pos++ = 0x88; //ahahahhahahhahahha
    *pos++ = 0x14; //ahahahhahahhahahha
    *pos++ = 0x24; //ahahahhahahhahahha
    *pos++ = 0xb8; //ahahahhahahhahahha
    *pos++ = 0x01; //ahahahhahahhahahha
    *pos++ = 0x00; //ahahahhahahhahahha
    *pos++ = 0x00; //ahahahhahahhahahha
    *pos++ = 0x00; //ahahahhahahhahahha
    *pos++ = 0xeb; //ahahahhahahhahahha
    *pos++ = 0x3d; //ahahahhahahhahahha
    *pos++ = 0x48; //ahahahhahahhahahha
    *pos++ = 0x31; //ahahahhahahhahahha
    *pos++ = 0xff; //ahahahhahahhahahha
    *pos++ = 0xbb; //ahahahhahahhahahha
    *pos++ = 0x0a; //ahahahhahahhahahha
    *pos++ = 0x00; //ahahahhahahhahahha
    *pos++ = 0x00; //ahahahhahahhahahha
    *pos++ = 0x00; //ahahahhahahhahahha
    *pos++ = 0x48; //ahahahhahahhahahha
    *pos++ = 0xff; //ahahahhahahhahahha
    *pos++ = 0xc7; //ahahahhahahhahahha
    *pos++ = 0x48; //ahahahhahahhahahha
    *pos++ = 0x31; //ahahahhahahhahahha
    *pos++ = 0xd2; //ahahahhahahhahahha
    *pos++ = 0x48; //ahahahhahahhahahha
    *pos++ = 0xf7; //ahahahhahahhahahha
    *pos++ = 0xf3; //ahahahhahahhahahha
    *pos++ = 0x48; //ahahahhahahhahahha
    *pos++ = 0x83; //ahahahhahahhahahha
    *pos++ = 0xf8; //ahahahhahahhahahha
    *pos++ = 0x00; //ahahahhahahhahahha
    *pos++ = 0x75; //ahahahhahahhahahha
    *pos++ = 0xf1; //ahahahhahahhahahha
    *pos++ = 0x48; //ahahahhahahhahahha
    *pos++ = 0x89; //ahahahhahahhahahha
    *pos++ = 0xf9; //ahahahhahahhahahha
    *pos++ = 0x48; //ahahahhahahhahahha
    *pos++ = 0x8b; //ahahahhahahhahahha
    *pos++ = 0x45; //ahahahhahahhahahha
    *pos++ = 0x08; //ahahahhahahhahahha
    *pos++ = 0x48; //ahahahhahahhahahha
    *pos++ = 0xff; //ahahahhahahhahahha
    *pos++ = 0xcf; //ahahahhahahhahahha
    *pos++ = 0x48; //ahahahhahahhahahha
    *pos++ = 0x31; //ahahahhahahhahahha
    *pos++ = 0xd2; //ahahahhahahhahahha
    *pos++ = 0x48; //ahahahhahahhahahha
    *pos++ = 0xf7; //ahahahhahahhahahha
    *pos++ = 0xf3; //ahahahhahahhahahha
    *pos++ = 0x48; //ahahahhahahhahahha
    *pos++ = 0x83; //ahahahhahahhahahha
    *pos++ = 0xc2; //ahahahhahahhahahha
    *pos++ = 0x30; //ahahahhahahhahahha
    *pos++ = 0x88; //ahahahhahahhahahha
    *pos++ = 0x14; //ahahahhahahhahahha
    *pos++ = 0x3c; //ahahahhahahhahahha
    *pos++ = 0x48; //ahahahhahahhahahha
    *pos++ = 0x83; //ahahahhahahhahahha
    *pos++ = 0xff; //ahahahhahahhahahha
    *pos++ = 0x00; //ahahahhahahhahahha
    *pos++ = 0x75; //ahahahhahahhahahha
    *pos++ = 0xea; //ahahahhahahhahahha
    *pos++ = 0xb8; //ahahahhahahhahahha
    *pos++ = 0x0a; //ahahahhahahhahahha
    *pos++ = 0x00; //ahahahhahahhahahha
    *pos++ = 0x00; //ahahahhahahhahahha
    *pos++ = 0x00; //ahahahhahahhahahha
    *pos++ = 0x48; //ahahahhahahhahahha
    *pos++ = 0x89; //ahahahhahahhahahha
    *pos++ = 0x04; //ahahahhahahhahahha
    *pos++ = 0x0c; //ahahahhahahhahahha
    *pos++ = 0xb8; //ahahahhahahhahahha
    *pos++ = 0x01; //ahahahhahahhahahha
    *pos++ = 0x00; //ahahahhahahhahahha
    *pos++ = 0x00; //ahahahhahahhahahha
    *pos++ = 0x00; //ahahahhahahhahahha
    *pos++ = 0x48; //ahahahhahahhahahha
    *pos++ = 0x89; //ahahahhahahhahahha
    *pos++ = 0xe6; //ahahahhahahhahahha
    *pos++ = 0xba; //ahahahhahahhahahha
    *pos++ = 0x0a; //ahahahhahahhahahha
    *pos++ = 0x00; //ahahahhahahhahahha
    *pos++ = 0x00; //ahahahhahahhahahha
    *pos++ = 0x00; //ahahahhahahhahahha
    *pos++ = 0xbf; //ahahahhahahhahahha
    *pos++ = 0x01; //ahahahhahahhahahha
    *pos++ = 0x00; //ahahahhahahhahahha
    *pos++ = 0x00; //ahahahhahahhahahha
    *pos++ = 0x00; //ahahahhahahhahahha
    *pos++ = 0x0f; //ahahahhahahhahahha
    *pos++ = 0x05; //ahahahhahahhahahha
    *pos++ = 0x41; //ahahahhahahhahahha
    *pos++ = 0x5b; //ahahahhahahhahahha
    *pos++ = 0x5a; //ahahahhahahhahahha
    *pos++ = 0x59; //ahahahhahahhahahha
    *pos++ = 0x5e; //ahahahhahahhahahha
    *pos++ = 0x5f; //ahahahhahahhahahha
}
