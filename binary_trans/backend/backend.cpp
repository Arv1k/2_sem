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
int ipert = 0;
int jpert = 0;
int kpert = 0;

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
        *(pc - 1) = '\0';


        funcs[ipert].name = strdup(tmp);
        *(pc - 1) = ' ';
        *pc++ = '(';
        pc++;

        if (*pc != ')') {
            tmp = pc;
            pc = strchr(pc, ' ');
            *pc++ = '\0';

            funcs[ipert].var[jpert].name_var = strdup(tmp);
            funcs[ipert].var[jpert].place_var = jpert + 1;
            funcs[ipert].given_num++;
            jpert++;

            while (*pc == ',') {
                pc += 2;

                tmp = pc;
                pc = strchr(pc, ' ');
                *pc++ = '\0';

                funcs[ipert].var[jpert].name_var = strdup(tmp);
                funcs[ipert].var[jpert].place_var = jpert + 1;
                funcs[ipert].given_num++;
                jpert++;
            }
        }

        assert(*pc == ')');

        pc++;

        assert(*pc == '{');

        funcs[ipert].tree_func = new tree;
        TreeCtor(funcs[ipert].tree_func);

        funcs[ipert].tree_func->Tamyr = get_tree(funcs);
        funcs[ipert].tree_func->count = CounT;

        pc++;
        ipert++;
        jpert = 0;
        kpert = 0;
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

            funcs[ipert].var[jpert].name_var = val->Info.name;
            funcs[ipert].var[jpert].place_var = ++kpert;
            funcs[ipert].var_num++;
            jpert++;


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

char* pos = nullptr;

void make_elf(Function* funcs, char* base_name, char* elf_name) {
    FILE* max = fopen(base_name, "rb");
    long num_symbols = Size(max);

    auto buffer = (char*) calloc(num_symbols, sizeof(char));

    fread(buffer, sizeof(char), num_symbols, max);
    fclose(max);

    pos = buffer;
    while (*((unsigned char*) pos) != 0x90) pos++;

    char* save_pos = pos;

    //print();

    int uyu = 0;
    while (funcs[uyu].tree_func) {
        *pos++ = 0x55;  // push rbp

        *pos++ = 0x48;  // mov rbp, rsp
        *pos++ = 0x89;  //
        *pos++ = 0xe5;  //

        Compile_tree(&(funcs[uyu]), funcs, &pos);
        uyu++;

        *pos++ = 0x5d;  // pop rbp
        *pos++ = 0x90;
        *pos++ = 0x90;
    }

    pos = save_pos;

    uyu = 0;

    while (funcs[uyu].tree_func) {
        *pos++ = 0x55;  // push rbp

        *pos++ = 0x48;  // mov rbp, rsp
        *pos++ = 0x89;  //
        *pos++ = 0xe5;  //

        Compile_tree(&(funcs[uyu]), funcs, &pos);
        uyu++;

        *pos++ = 0x5d;  // pop rbp
        *pos++ = 0x90;
        *pos++ = 0x90;
    }

    FILE* maxu = fopen(elf_name, "wb");
        fwrite(buffer, sizeof(char), num_symbols, maxu);
    fclose(maxu);

    free(buffer);
    /*assert(funcs);
    assert(elf_name);

    FILE* elf = fopen(elf_name, "rb");

    char* buffer = translate_funcs(funcs);

    fclose(elf);*/
}

size_t Compile_tree(Function* curr_func, Function* func_table, char** start_pos) {
    assert(curr_func != nullptr);
    assert(func_table != nullptr);

    pos = *start_pos;

    transform_var_table(curr_func);
    push_func_addr(curr_func->name, func_table, *start_pos);
    compile_node(curr_func->tree_func->Tamyr, curr_func->var, func_table);

    *start_pos = pos;

    return pos - *start_pos;
}

void push_func_addr(char* name, Function* func_table, char* start_pos) {
    int i = 0;
    while (func_table[i].name != nullptr) {
        if (!strcmp(name, func_table[i].name)) {

            func_table[i].sdvig = pos;
            break;
        }
        i++;
    }
}

void transform_var_table(Function* curr_func) {
    int i = 0;
    while (curr_func->var[i].name_var != nullptr) {
        if (i < curr_func->given_num)
            curr_func->var[i].place_var = i + 1;
        else
            curr_func->var[i].place_var = -((curr_func->var[i].place_var - curr_func->given_num) * 8);

        i++;
    }
}

int num_of_param_dont_touch_it = 0;

void compile_node(tree_elem* curr_node, Variables* arr_of_vars, Function* arr_of_func) {
    if (!curr_node) return;

    switch (curr_node->Info.mode) {
        case M_I: { // !
            compile_node(curr_node->Left, arr_of_vars, arr_of_func);

            char *jump_pos = pos;
            pos += 4;

            compile_node(curr_node->Right, arr_of_vars, arr_of_func);

            int offset = pos - jump_pos - 4;

            *((int *) jump_pos) = offset;

            break;
        }

        case M_O: // !
            compile_node(curr_node->Left, arr_of_vars, arr_of_func);
            compile_node(curr_node->Right, arr_of_vars, arr_of_func);

            cmp();

            if (curr_node->Info.number == '=') {
                *pos++ = 0x0f;
                *pos++ = 0x85;
            }

            else if (curr_node->Info.number == '>') {
                *pos++ = 0x0f;
                *pos++ = 0x86;
            }

            else if (curr_node->Info.number == '<') {
                *pos++ = 0x0f;
                *pos++ = 0x83;
            }

            break;

        case M_s: // !
            compile_node(curr_node->Left, arr_of_vars, arr_of_func);
            compile_node(curr_node->Right, arr_of_vars, arr_of_func);

            if (curr_node->Info.number == '+')
                add();

            else if (curr_node->Info.number == '-')
                sub();

            else if (curr_node->Info.number == '/')
                div();

            else if (curr_node->Info.number == '*')
                mul();

            break;

        case M_V: { // !
            int offset = find_var(curr_node->Info.name, arr_of_vars);

            take_from_memory(offset);

            break;
        }

        case M_B: // !
            compile_node(curr_node->Left, arr_of_vars, arr_of_func);
            compile_node(curr_node->Right, arr_of_vars, arr_of_func);

            break;

        case M_R: //???
            compile_node(curr_node->Left, arr_of_vars, arr_of_func);

            *(pos++) = 0x58;

            aligh_stack(arr_of_vars);

            *(pos++) = 0x5d;
            *(pos++) = 0xc3;

            break;

        case M_N: // !
            num(curr_node->Info.number);
            break;

        case M_S: // ?
            if (curr_node->Info.number == 1) {
                compile_node(curr_node->Left, arr_of_vars, arr_of_func);
                print();
            }

            else if (curr_node->Info.number == 0) {
                scan();
            }

            break;

        case M_C: // ?
            if (curr_node->Left != nullptr)
                compile_node(curr_node->Left, arr_of_vars, arr_of_func);

            save_registers(arr_of_vars);
            *pos++ = 0xe8;

            *((int*) pos) = find_add_func(curr_node->Info.name, arr_of_func) - (pos + 8);
            pos += 4;
            return_registers(arr_of_vars);
            *pos++ = 0x50;

            break;

        case M_P: // ???
            compile_node(curr_node->Left, arr_of_vars, arr_of_func);

            num_of_param_dont_touch_it++;
            push_param(num_of_param_dont_touch_it);

            if (curr_node->Right != nullptr)
                compile_node(curr_node->Right, arr_of_vars, arr_of_func);

            num_of_param_dont_touch_it--;
            break;

        case M_e: // !
            compile_node(curr_node->Right, arr_of_vars, arr_of_func);

            *pos++ = 0x58; // pop rax

            push_to_memory(curr_node->Left->Info.name, arr_of_vars);
            break;

        default:

            return;
    }
    return;
}

void push_param(int counter) {
    if (counter > 6) {
        return;
    }

    else if (counter == 1)
        *(pos++) = 0x5f;
    else if (counter == 2)
        *(pos++) = 0x5e;
    else if (counter == 3)
        *(pos++) = 0x5a;
    else if (counter == 4)
        *(pos++) = 0x59;
    else if (counter == 5) {
        *(pos++) = 0x41;
        *(pos++) = 0x58;
    } else if (counter == 6) {
        *(pos++) = 0x41;
        *(pos++) = 0x59;
    }
}

char* find_add_func(char* name_func, Function* arr_of_func) {
    int i = 0;
    while (arr_of_func[i].name != nullptr) {
        if (!strcmp(name_func, arr_of_func[i].name))
            return arr_of_func[i].sdvig;
        i++;
    }
    printf("I can't find this func - %s", name_func);
    abort();
}

void push_to_memory(char* name, Variables* arr_of_vars) {
    int offset = find_var(name, arr_of_vars);

    if (offset <= 0) {
        *(pos++) = 0x48; // mov [rbp + offset], rax
        *(pos++) = 0x89; //
        *(pos++) = 0x45; //
        *(pos++) = 0x00 + (char) offset;
    }

    else {
        if (offset < 5) {
            *(pos++) = 0x48;
            *(pos++) = 0x89;

            switch (offset) {
                case 1:
                    *(pos++) = 0xc7;
                    break;
                case 2:
                    *(pos++) = 0xc6;
                    break;
                case 3:
                    *(pos++) = 0xc2;
                    break;
                case 4:
                    *(pos++) = 0xc1;
                    break;
            }
        }

        else if (offset == 5) {
            *(pos++) = 0x49;
            *(pos++) = 0x89;
            *(pos++) = 0xc0;
        }

        else if (offset == 6) {
            *(pos++) = 0x49;
            *(pos++) = 0x89;
            *(pos++) = 0xc1;
        }
    }

}

void take_from_memory(int offset) {
    if (offset <= 0) {
        *(pos++) = 0x48;  // mov [rbp + offset], rax
        *(pos++) = 0x8b;  //
        *(pos++) = 0x45;  //
        *(pos++) = 0x00 + (char) offset;
        *(pos++) = 0x50;  // push rax
    } else {
        if (offset < 5) {
            *(pos++) = 0x48;
            *(pos++) = 0x89;
            switch (offset) {
                case 1:
                    *(pos++) = 0xf8;
                    break;
                case 2:
                    *(pos++) = 0xf0;
                    break;
                case 3:
                    *(pos++) = 0xc8;
                    break;
                case 4:
                    *(pos++) = 0xd0;
                    break;
            }
        } else if (offset == 5) {
            *(pos++) = 0x4c;
            *(pos++) = 0x89;
            *(pos++) = 0xc0;
        } else if (offset == 6) {
            *(pos++) = 0x4c;
            *(pos++) = 0x89;
            *(pos++) = 0xc8;
        }
        *(pos++) = 0x50;
    }
}

void cut_stack(Variables* arr_of_vars) {
    int i = 0;
    int counter = 0;
    while (arr_of_vars[i].name_var != nullptr) {
        if (arr_of_vars[i].place_var < 0)
            counter++;
        i++;
    }

    *pos++ = 0x48;
    *(pos++) = 0x83;
    *(pos++) = 0xec;
    *(pos++) = counter * 8;
}

void aligh_stack(Variables* arr_of_vars) {
    int i = 0;
    int counter = 0;
    while (arr_of_vars[i].name_var != nullptr) {
        if (arr_of_vars[i].place_var < 0)
            counter++;
        i++;
    }

    *(pos++) = 0x48;
    *(pos++) = 0x83;
    *(pos++) = 0xc4;
    *(pos++) = counter * 8;
}

int find_var(char* name, Variables* arr_of_var) {
    int i = 0;
    while (arr_of_var[i].name_var != nullptr) {
        if (!strcmp(arr_of_var[i].name_var, name))
            return arr_of_var[i].place_var;
        i++;
    }
    printf("I can't find this name %s", name);
    abort();
}

void add() {
    *(pos++) = 0x58;// pop rax, pop rbx
    *(pos++) = 0x5b;

    *(pos++) = 0x48;// add rax, rbx
    *(pos++) = 0x01;
    *(pos++) = 0xd8;

    *(pos++) = 0x50;// push rax
}

void div() {
    *(pos++) = 0x58;// pop rax, pop rbx
    *(pos++) = 0x5b;

    *(pos++) = 0x52;// push rdx

    *(pos++) = 0x48;// xor rdx, rdx
    *(pos++) = 0x31;
    *(pos++) = 0xd2;

    *(pos++) = 0x48;// div rbx
    *(pos++) = 0xf7;
    *(pos++) = 0xf3;

    *(pos++) = 0x5a;// pop rdx
    *(pos++) = 0x50;// push rax
}

void cmp() {
    *pos++ = 0x58; // pop rax
    *pos++ = 0x5b; // pop rbx

    *pos++ = 0x48; // cmp rax, rbx
    *pos++ = 0x39;
    *pos++ = 0xd8;

}

void sub() {
    *pos++ = 0x58; // pop rax
    *pos++ = 0x5b; // pop rbx

    *pos++ = 0x48; // sub rax, rbx
    *pos++ = 0x29;
    *pos++ = 0xd8;

    *pos++ = 0x50; // push rax
}

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
    /* *pos++ = 0xb8;
    *pos++ = 0x34;
    *pos++ = 0xb1;
    *pos++ = 0x01;
    *pos++ = 0x00;
    *pos++ = 0x50;*/

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


void save_registers(Variables* arr_of_func) {
    int i = 0;
    while (arr_of_func[i].name_var != nullptr) {
        if (arr_of_func[i].place_var > 0) {
            switch (arr_of_func[i].place_var) {
                case 1:
                    *pos = 0x57;
                    pos++;
                    break;
                case 2:
                    *pos = 0x56;
                    pos++;
                    break;
                case 3:
                    *pos = 0x52;
                    pos++;
                    break;
                case 4:
                    *pos = 0x51;
                    pos++;
                    break;
                case 5:
                    *pos = 0x41;
                    pos++;
                    *pos = 0x50;
                    pos++;
                    break;
                case 6:
                    *pos = 0x41;
                    pos++;
                    *pos = 0x51;
                    pos++;
                    break;
            }
        }
        i++;
    }
}

void return_registers(Variables* arr_of_func) {
    int i = 0;
    while (arr_of_func[i].name_var != nullptr) {
        if (arr_of_func[i].place_var > 0) {
            switch (arr_of_func[i].place_var) {
                case 1:
                    *pos = 0x5f;
                    pos++;
                    break;
                case 2:
                    *pos = 0x5e;
                    pos++;
                    break;
                case 3:
                    *pos = 0x5a;
                    pos++;
                    break;
                case 4:
                    *pos = 0x59;
                    pos++;
                    break;
                case 5:
                    *pos = 0x41;
                    pos++;
                    *pos = 0x58;
                    pos++;
                    break;
                case 6:
                    *pos = 0x41;
                    pos++;
                    *pos = 0x59;
                    pos++;
                    break;
            }
        }
        i++;
    }
}