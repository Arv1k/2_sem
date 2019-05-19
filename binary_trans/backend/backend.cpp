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

            funcs[i].var_num++;
            funcs[i].var[j].name_var = strdup(tmp);
            funcs[i].var[j].place_var = j;
            j++;

            while (*pc == ',') {
                pc += 2;

                tmp = pc;
                pc = strchr(pc, ' ');
                *pc++ = '\0';

                funcs[i].var_num++;
                funcs[i].var[j].name_var = strdup(tmp);
                funcs[i].var[j].place_var = j;
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
            funcs[i].var[j].place_var = j;
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
void create_std_tree(tree_elem* pos, FILE* dot_out) {
    assert(dot_out);
    assert(pos);

    fprintf(dot_out, "\t\they%d", tmp);
    print_std_mode(pos, dot_out);
    fprintf(dot_out, ";\n");

    int iskan = tmp;

    if (pos->Left != nullptr) {
        fprintf(dot_out, "\t\they%d", iskan);

        fprintf(dot_out, "->");

        fprintf(dot_out, "hey%d;\n", ++tmp);

        create_std_tree(pos->Left, dot_out);
    }

    if (pos->Right != nullptr) {
        fprintf(dot_out, "\t\they%d", iskan);

        fprintf(dot_out, "->");

        fprintf(dot_out, "hey%d;\n", ++tmp);

        create_std_tree(pos->Right, dot_out);
    }

    assert(pos);
    assert(dot_out);
}

void print_std_mode(tree_elem* pos, FILE* dot_out) {
    assert(pos);
    assert(dot_out);

    switch ((pos->Info).mode) {
        case M_B:        fprintf(dot_out, "[label = \"B\", shape = \"Mcircle\", "
                                              "color=\"#000000\", style=\"filled\", "
                                              "fillcolor = \"#32CD32\"]");
            break;

        case M_s:      fprintf(dot_out, "[label = \"s %c\", shape = \"diamond\", "
                                              "color=\"#000000\", style=\"filled\", "
                                              "fillcolor = \"#F0E68C\"]", (pos->Info).number);
            break;

        case M_O:       fprintf(dot_out, "[label = \"O %c\", shape = \"component\", "
                                              "color=\"#000000\", style=\"filled\", "
                                              "fillcolor = \"#9932CC\"]", (pos->Info).number);
            break;

        case M_I:    fprintf(dot_out, "[label = \"I\", shape = \"Msquare\", "
                                              "color=\"#000000\", style=\"filled\", "
                                              "fillcolor = \"#FFA07A\"]");
            break;

        case M_i:      fprintf(dot_out, "[label = \"i %s\", shape = \"invtriangle\", "
                                              "color=\"#000000\", style=\"filled\", "
                                              "fillcolor = \"#00FFFF\"]", (pos->Info).name);
            break;

        case M_N: fprintf(dot_out, "[label = \"N %d\", shape = \"egg\", "
                                              "color=\"#000000\", style=\"filled\", "
                                              "fillcolor = \"#FFFFFF\"]", pos->Info.number);
            break;

        case M_R:      fprintf(dot_out, "[label = \"R\", shape = \"house\", "
                                              "color=\"#000000\", style=\"filled\", "
                                              "fillcolor = \"#D2691E\"]");
            break;

        case M_V:        fprintf(dot_out, "[label = \"V %s\", shape = \"house\", "
                                              "color=\"#000000\", style=\"filled\", "
                                              "fillcolor = \"#ff6161\"]", pos->Info.name);
            break;

        case M_L:       fprintf(dot_out, "[label = \"L\", shape = \"box3d\", "
                                              "color=\"#000000\", style=\"filled\", "
                                              "fillcolor = \"#32CD32\"]");
            break;

        case M_S:        fprintf(dot_out, "[label = \"S %d\", shape = \"box3d\", "
                                              "color=\"#000000\", style=\"filled\", "
                                              "fillcolor = \"#FFDEAD\"]", pos->Info.number);
            break;

        case M_C:    fprintf(dot_out, "[label = \"C %s\", shape = \"box3d\", "
                                              "color=\"#000000\", style=\"filled\", "
                                              "fillcolor = \"#708090\"]", pos->Info.name);
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

    assert(pos);
    assert(dot_out);
}