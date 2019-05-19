#include "language.h"

size_t CoUNT = 0;
char* pc = nullptr;

#define SKIP_EXTRA pc++;\
                   while (((*pc) == ' ') || ((*pc) == '\n')) pc++;

void makeTree(tree* nameTree, char* buffer) {
    assert_tree(nameTree);
    assert(buffer);

    nameTree->Tamyr = GetF(buffer);
    nameTree->count = CoUNT;

    assert_tree(nameTree);
}

tree_elem* GetF(char* buff) {
    dassert(buff);

    pc = buff;

    char* tmp = pc;
    pc = strchr(pc, ' ');

    (*pc) = '\0';
    if (strcmp(tmp, "баш") != 0) {
        printf("Invalid code!!! There isn't \"баш\"!!!\n");

        abort();
    }

    (*pc) = ' ';
    pc++;
    pc_assert((*pc) == '"');

    pc += 3;
    SKIP_EXTRA;

    pc_assert((*pc) == '-');
    pc += 5;
    SKIP_EXTRA;

    tree_elem *val1 = (tree_elem *) calloc(1, sizeof(*val1));
    CoUNT++;

    (val1->Info).mode = MODE_NAME;
    (val1->Info).name = strdup("баш");

    tree_elem* val2 = GetG();

    SKIP_EXTRA;
    pc_assert((*pc) == '-');
    pc += 5;

    SKIP_EXTRA;

    val1->Left = val2;
    val2->Parent = val1;

    val1->Right = nullptr;

    while ((*pc) != '\0') {
        tmp = pc;
        pc = strchr(pc, ' ');

        (*pc) = '\0';

        tree_elem* val3 = (tree_elem *) calloc(1, sizeof(*val3));
        CoUNT++;

        (val3->Info).mode = MODE_NAME;
        (val3->Info).name = strdup(tmp);

        (*pc) = ' ';
        pc++;
        pc_assert((*pc) == '"');

        pc++;
        tree_elem* val4 = nullptr;
        if ((*pc) != '"') {
            val4 = GetId();

            while ((*pc) == ';') {
                SKIP_EXTRA;

                tree_elem *val5 = GetId();

                tree_elem *val6 = (tree_elem *) calloc(1, sizeof(*val6));
                CoUNT++;

                (val6->Info).mode = MODE_VARIABLES;

                tree_elem* tmp1 = val4;
                val4 = val6;
                val6 = tmp1;

                val4->Left = val6;
                val6->Parent = val4;

                val4->Right = val5;
                val5->Parent = val4;
            }
        }

        pc_assert((*pc) == '"');
        pc++;

        pc_assert((*pc) == ':');

        SKIP_EXTRA;

        pc_assert((*pc) == '-');
        pc += 5;

        SKIP_EXTRA;

        val3->Right = val4;
        if (val4 != nullptr) val4->Parent = val3;

        tree_elem* val7 = GetG();

        SKIP_EXTRA;
        pc_assert((*pc) == '-');
        pc += 5;

        SKIP_EXTRA;

        val3->Left = val7;
        val7->Parent = val3;

        tree_elem* val8 = (tree_elem*) calloc(1, sizeof(*val8));
        CoUNT++;

        (val8->Info).mode = MODE_FUNC;

        tree_elem* tmp2 = val1;
        val1 = val8;
        val8 = tmp2;

        val1->Left = val8;
        val8->Parent = val1;

        val1->Right = val3;
        val3->Parent = val1;
    }

    pc_assert(*(pc) == '\0')
    return val1;
}

tree_elem* GetG() {
    dassert(pc);

    tree_elem* val1 = GetTo();

    while ((*pc) == ',') {
        SKIP_EXTRA;

        tree_elem* val2 = GetTo();

        tree_elem *val3 = (tree_elem *) calloc(1, sizeof(*val3));
        CoUNT++;

        (val3->Info).mode = MODE_OPERATORR;

        tree_elem* tmp = val1;
        val1 = val3;
        val3 = tmp;

        val1->Right = val2;
        val2->Parent = val1;

        val1->Left = val3;
        val3->Parent = val1;
    }

    dassert(pc);
    pc_assert((*pc) == '.');
    return val1;
}

tree_elem* GetTo() {
    dassert(pc);

    tree_elem* val = nullptr;

    int smth = which_To();
    switch (smth) {
        case EGER:
            val = GetIf();
            break;

        case ELE:
            val = GetL();
            break;

        case OP_TOP:
            val = GetA();
            break;

        default:
            printf("Smth wrong!\n");
            abort();
    }

    dassert(pc);
    pc_assert((*pc) == '.' || (*pc) == ',');
    return val;
}

tree_elem* GetL() {
    dassert(pc);

    tree_elem* val1 = GetC();

    pc_assert((*pc) == '"');

    pc++;

    if ((*pc) == ':') {
        SKIP_EXTRA;

        tree_elem* val2 = GetTo();

        while ((*pc) != '.') {
            SKIP_EXTRA;

            tree_elem *val4 = GetTo();

            tree_elem* val5 = (tree_elem *) calloc(1, sizeof(*val1));
            CoUNT++;

            (val5->Info).mode = MODE_OPERATORR;

            tree_elem* tmp = val2;
            val2 = val5;
            val5 = tmp;

            val2->Right = val4;
            val4->Parent = val2;

            val2->Left = val5;
            val5->Parent = val2;
        }

        pc_assert((*pc) == '.');
        pc++;

        tree_elem* val3 = (tree_elem *) calloc(1, sizeof(*val1));
        CoUNT++;

        (val3->Info).mode = MODE_LOOP;

        val3->Left = val1;
        val1->Parent = val3;

        val3->Right = val2;
        val2->Parent = val3;

        dassert(pc);
        return val3;
    }

    SKIP_EXTRA;

    tree_elem* val2 = GetTo();

    tree_elem* val3 = (tree_elem *) calloc(1, sizeof(*val1));
    CoUNT++;

    (val3->Info).mode = MODE_LOOP;

    val3->Left = val1;
    val1->Parent = val3;

    val3->Right = val2;
    val2->Parent = val3;

    pc_assert((*pc) == ',' || (*pc) == '.');
    dassert(pc);
    return val3;
}

tree_elem* GetIf() {
    dassert(pc);

    tree_elem* val1 = GetC();

    pc_assert((*pc) == '"');

    pc++;

    if ((*pc) == ':') {
        SKIP_EXTRA;

        tree_elem* val2 = GetTo();

        while ((*pc) != '.') {
            SKIP_EXTRA;

            tree_elem *val4 = GetTo();

            tree_elem* val5 = (tree_elem *) calloc(1, sizeof(*val1));
            CoUNT++;

            (val5->Info).mode = MODE_OPERATORR;

            tree_elem* tmp = val2;
            val2 = val5;
            val5 = tmp;

            val2->Right = val4;
            val4->Parent = val2;

            val2->Left = val5;
            val5->Parent = val2;
        }

        pc_assert((*pc) == '.');
        pc++;

        tree_elem* val3 = (tree_elem *) calloc(1, sizeof(*val1));
        CoUNT++;

        (val3->Info).mode = MODE_IF;

        val3->Left = val1;
        val1->Parent = val3;

        val3->Right = val2;
        val2->Parent = val3;

        dassert(pc);
        return val3;
    }

    SKIP_EXTRA;

    tree_elem* val2 = GetTo();

    tree_elem* val3 = (tree_elem *) calloc(1, sizeof(*val1));
    CoUNT++;

    (val3->Info).mode = MODE_IF;

    val3->Left = val1;
    val1->Parent = val3;

    val3->Right = val2;
    val2->Parent = val3;

    pc_assert((*pc) == ',' || (*pc) == '.');
    dassert(pc);
    return val3;
}

tree_elem* GetA() {
    dassert(pc);

    tree_elem* val1 = nullptr;

    if ((*pc) == '"') {
        SKIP_EXTRA;

        val1 = GetE();

        pc_assert((*pc) == '"');

        SKIP_EXTRA;

        tree_elem* val2 = (tree_elem*) calloc(1, sizeof(*val2));
        CoUNT++;

        if(which_A() == KURSET)   (val2->Info).mode = MODE_OUT;

        else if(which_A() == BIR) (val2->Info).mode = MODE_RETURN;

        else                      abort();

        val2->Left = val1;
        val1->Parent = val2;

        val2->Right = nullptr;

        dassert(pc);
        return val2;
    }


    else val1 = GetId();

    tree_elem* val2 = (tree_elem*) calloc(1, sizeof(*val2));
    CoUNT++;

    if ((*pc) == '"') {
        pc++;

        tree_elem* val4 = nullptr;
        if ((*pc) != '"') {
            val4 = GetId();

            while ((*pc) == ';') {
                SKIP_EXTRA;

                tree_elem *val5 = GetId();

                tree_elem *val6 = (tree_elem *) calloc(1, sizeof(*val6));
                CoUNT++;

                (val6->Info).mode = MODE_VARIABLES;

                tree_elem* tmp1 = val4;
                val4 = val6;
                val6 = tmp1;

                val4->Left = val6;
                val6->Parent = val4;

                val4->Right = val5;
                val5->Parent = val4;
            }
        }

        pc_assert((*pc) == '"');

        SKIP_EXTRA;

        (val2->Info).mode = MODE_CALL;

        val2->Left = val1;
        val1->Parent = val2;

        val2->Right = val4;
        if (val4 != nullptr) val4->Parent = val2;

        return val2;
    }

    tree_elem* val3 = nullptr;
    switch (which_A()) {
        case EIT:
            (val2->Info).mode = MODE_IN;
            break;

        case TUDY:
            (val2->Info).mode = MODE_BORN;
            break;

        case BU:
            (val2->Info).mode = MODE_ASSIGN;

            while ((*pc) == ' ') pc++;

            val3 = GetE();

            val2->Left = val1;
            val1->Parent = val2;

            val2->Right = val3;
            val1->Parent = val3;

            dassert(pc);
            return val2;

        case KURSET:
            (val2->Info).mode = MODE_OUT;
            break;

        case BIR:
            (val2->Info).mode = MODE_RETURN;
            break;

        default:
            abort();
    }

    val2->Left = val1;
    val1->Parent = val2;

    val2->Right = nullptr;

    pc_assert(((*pc) == '.') || ((*pc) == ',') );

    dassert(pc);
    return val2;
}

tree_elem* GetC() {
    tree_elem* val1 = GetE();
    tree_elem* val2 = GetE();

    char* tmp = pc;
    pc = strchr(pc, '"');
    (*pc) = '\0';

    tree_elem* val3 = (tree_elem*) calloc(1, sizeof(*val3));
    CoUNT++;

    if      (strcmp(tmp, "зуррак") == 0)     (val3->Info).mode = MODE_BIGGER;

    else if (strcmp(tmp, "кечкенәрәк") == 0) (val3->Info).mode = MODE_LESS;

    else if (strcmp(tmp, "тигез") == 0)      (val3->Info).mode = MODE_EQUAL;

    else if (strcmp(tmp, "түгeл") == 0)      (val3->Info).mode = MODE_NOT_EQUAL;

    val3->Left = val1;
    val1->Parent = val3;

    val3->Right = val2;
    val2->Parent = val3;

    (*pc) = '"';

    dassert(pc);
    return val3;
}

tree_elem* GetE() {
    dassert(pc);

    tree_elem* val1 = GetT();

    while(*pc == '+' || *pc == '-') {
        char op = (*pc);

        SKIP_EXTRA;

        tree_elem* val2 = GetT();

        tree_elem* val3 = (tree_elem*) calloc(1, sizeof(*val3));
        CoUNT++;

        (val3->Info).mode = MODE_SIGN;
        (val3->Info).number = op;

        tree_elem* tmp = val1;
        val1 = val3;
        val3 = tmp;

        val1->Right = val2;
        val2->Parent = val1;

        val1->Left = val3;
        val3->Parent = val1;
    }

    dassert(pc);
    return val1;
}

tree_elem* GetT() {
    dassert(pc);

    tree_elem* val1 = GetP();

    while(*pc == '*' || *pc == '/') {
        char op = (*pc);

        SKIP_EXTRA;

        tree_elem* val2 = GetP();

        tree_elem* val3 = (tree_elem*) calloc(1, sizeof(*val3));
        CoUNT++;

        (val3->Info).mode = MODE_SIGN;
        (val3->Info).number = op;

        tree_elem* tmp = val1;
        val1 = val3;
        val3 = tmp;

        val1->Right = val2;
        val2->Parent = val1;

        val1->Left = val3;
        val3->Parent = val1;
    }

    dassert(pc);
    return val1;
}

tree_elem* GetP() {
    dassert(pc);

    tree_elem* val = nullptr;

    if (*pc == '(') {
        SKIP_EXTRA;

        val = GetE();
        assert(*pc == ')');

        SKIP_EXTRA;

        dassert(pc);
        return val;
    }

    if (*pc == 's' || *pc == 'c' || *pc == 'l' || *pc == 't' || *pc == 'a' || *pc == 'e') {

        char* word = which_word();

        if (!word) return GetN();

        while ((*pc) == ' ') pc++;

        val = GetP();

        tree_elem* val2 = (tree_elem*) calloc(1, sizeof(*val2));
        CoUNT++;

        (val2->Info).mode = MODE_OP;
        (val2->Info).name = word;

        val2->Right = val;
        val->Parent = val2;

        dassert(pc);
        return val2;
    }

    dassert(pc);
    return GetN();
}

tree_elem* GetN() {
    dassert(pc);

    tree_elem* val = (tree_elem*) calloc(1, sizeof(*val));
    CoUNT++;

    if ('0' <= (*pc) && (*pc) <= '9') {
        (val->Info).mode = MODE_NUMBER;

        while ('0' <= (*pc) && (*pc) <= '9') {
            (val->Info).number = ((val->Info).number * 10) + (*pc - '0');

            pc++;
        }
    }

    else if (('a' <= (*pc) && (*pc) <= 'z') || ('A' <= (*pc) && (*pc) <= 'Z')) {
        char var[max_word] = "";
        (val->Info).mode = MODE_VAR;

        int i = 0;
        while (('a' <= (*pc) && (*pc) <= 'z') || ('A' <= (*pc) && (*pc) <= 'Z')) {
            var[i] = (*pc);

            pc++;
            i++;
        }

        (val->Info).name = strdup(var);
    }

    else {
        printf("Invalid entry!!!\n--> %c\n", *pc);

        abort();
    }

    while ((*pc) == ' ') pc++;

    dassert(pc);
    return val;
}

tree_elem* GetId() {
    dassert(pc);

    tree_elem* val = (tree_elem*) calloc(1, sizeof(*val));
    CoUNT++;

    if (('a' <= (*pc) && (*pc) <= 'z') || ('A' <= (*pc) && (*pc) <= 'Z')) {
        char var[max_word] = "";
        (val->Info).mode = MODE_VAR;

        int i = 0;
        while (('a' <= (*pc) && (*pc) <= 'z') || ('A' <= (*pc) && (*pc) <= 'Z')) {
            var[i] = (*pc);

            pc++;
            i++;
        }

        (val->Info).name = strdup(var);
    }

    else {
        printf("Invalid entry!!!\n--> %c\n", *pc);

        abort();
    }

    while ((*pc) == ' ') pc++;

    dassert(pc);
    return val;
}

char* which_word() {
    dassert(pc);

    int i = 0;
    while (pc[i] >= 'a' && pc[i] <= 'z') i++;

    char tmp = pc[i];
    pc[i] = '\0';

    #define CMD_FORM(com, len, num, code) if (strcmp(pc, #com) == 0) {\
                                                 pc[i] = tmp;\
                                                 pc += len;\
                                                 return strdup(#com);\
                                              }

    #include "com.h"

    #undef CMD_FORM

    pc[i] = tmp;

    dassert(pc);
    return nullptr;
}

int which_To() {
    dassert(pc);

    char* tmp = pc;
    pc = strchr(pc, ' ');
    if (!pc) {
        pc = tmp;

        dassert(pc);
        return OP_TOP;
    }

    (*pc) = '\0';

    if (strcmp(tmp, "әле") == 0) {
        (*pc) = ' ';

        pc += 2;

        dassert(pc);
        return ELE;
    }

    else if (strcmp(tmp, "әгәр") == 0) {
        (*pc) = ' ';

        pc += 2;

        dassert(pc);
        return EGER;
    }

    else {
        (*pc) = ' ';

        pc = tmp;
        while (((*pc) == ' ') || ((*pc) == '\n')) pc++;

        dassert(pc);
        return OP_TOP;
    }
}

int which_A() {
    dassert(pc);

    char* tmp = pc;
    while ( !((*pc) == ',' || (*pc) == '.' || (*pc) == ' ') ) pc++;

    char tmp1 = (*pc);
    (*pc) = '\0';

    if (strcmp(tmp, "бу") == 0) {
        (*pc) = tmp1;

        dassert(pc);
        return BU;
    }

    else if (strcmp(tmp, "туды") == 0) {
        (*pc) = tmp1;

        dassert(pc);
        return TUDY;
    }

    if (strcmp(tmp, "әйт") == 0) {
        (*pc) = tmp1;

        dassert(pc);
        return EIT;
    }

    if (strcmp(tmp, "күрсәт") == 0) {
        (*pc) = tmp1;

        dassert(pc);
        return KURSET;
    }

    else if (strcmp(tmp, "бир") == 0) {
        (*pc) = tmp1;

        dassert(pc);
        return BIR;
    }
}

void tree_dot(tree* nameTree, char* dot_out) {
    assert(dot_out);
    assert_tree(nameTree);

    FILE *file_dot = fopen(dot_out, "wb");
    assert(file_dot);

    fprintf(file_dot, "digraph {\n");
    fprintf(file_dot, "\tnode[color = \"#000000\", fontsize = 20];\n"
                      "\tedge[color = \"#000000\", fontsize = 20];\n");

    create_tree(nameTree->Tamyr, file_dot);

    fprintf(file_dot, "}");

    assert(file_dot);
    fclose(file_dot);

    system("dot -Tjpg -o tree.jpg dott.dot");
    system("xviewer tree.jpg");

    assert_tree(nameTree);
}

int tmp = 0;
void create_tree(tree_elem* pos, FILE* dot_out) {
    assert(dot_out);
    assert(pos);

    fprintf(dot_out, "\t\they%d", tmp);
    print_mode(pos, dot_out);
    fprintf(dot_out, ";\n");

    int iskan = tmp;

    if (pos->Left != nullptr) {
        fprintf(dot_out, "\t\they%d", iskan);

        fprintf(dot_out, "->");

        fprintf(dot_out, "hey%d;\n", ++tmp);

        create_tree(pos->Left, dot_out);
    }

    if (pos->Right != nullptr) {
        fprintf(dot_out, "\t\they%d", iskan);

        fprintf(dot_out, "->");

        fprintf(dot_out, "hey%d;\n", ++tmp);

        create_tree(pos->Right, dot_out);
    }

    assert(pos);
    assert(dot_out);
}

void print_mode(tree_elem* pos, FILE* dot_out) {
    assert(pos);
    assert(dot_out);

    switch ((pos->Info).mode) {
        case MODE_OP:        fprintf(dot_out, "[label = \"%s %d\", shape = \"Mcircle\", "
                                              "color=\"#000000\", style=\"filled\", "
                                              "fillcolor = \"#32CD32\"]", (pos->Info).name, MODE_OP);
                             break;

        case MODE_SIGN:      fprintf(dot_out, "[label = \"%c %d\", shape = \"diamond\", "
                                              "color=\"#000000\", style=\"filled\", "
                                              "fillcolor = \"#F0E68C\"]", (pos->Info).number, MODE_SIGN);
                             break;

        case MODE_VAR:       fprintf(dot_out, "[label = \"%s %d\", shape = \"component\", "
                                              "color=\"#000000\", style=\"filled\", "
                                              "fillcolor = \"#9932CC\"]", (pos->Info).name, MODE_VAR);
                             break;

        case MODE_NUMBER:    fprintf(dot_out, "[label = \"%d %d\", shape = \"Msquare\", "
                                              "color=\"#000000\", style=\"filled\", "
                                              "fillcolor = \"#FFA07A\"]", (pos->Info).number, MODE_NUMBER);
                             break;

        case MODE_NAME:      fprintf(dot_out, "[label = \"%s %d\", shape = \"invtriangle\", "
                                              "color=\"#000000\", style=\"filled\", "
                                              "fillcolor = \"#00FFFF\"]", (pos->Info).name, MODE_NAME);
                             break;

        case MODE_OPERATORR: fprintf(dot_out, "[label = \"operator %d\", shape = \"egg\", "
                                              "color=\"#000000\", style=\"filled\", "
                                              "fillcolor = \"#FFFFFF\"]", MODE_OPERATORR);
                             break;

        case MODE_LOOP:      fprintf(dot_out, "[label = \"loop %d\", shape = \"house\", "
                                              "color=\"#000000\", style=\"filled\", "
                                              "fillcolor = \"#D2691E\"]", MODE_LOOP);
                             break;

        case MODE_IF:        fprintf(dot_out, "[label = \"if %d\", shape = \"house\", "
                                              "color=\"#000000\", style=\"filled\", "
                                              "fillcolor = \"#800000\"]", MODE_IF);
                             break;

        case MODE_OUT:       fprintf(dot_out, "[label = \"out %d\", shape = \"box3d\", "
                                              "color=\"#000000\", style=\"filled\", "
                                              "fillcolor = \"#32CD32\"]", MODE_OUT);
                             break;

        case MODE_IN:        fprintf(dot_out, "[label = \"in %d\", shape = \"box3d\", "
                                              "color=\"#000000\", style=\"filled\", "
                                              "fillcolor = \"#FFDEAD\"]", MODE_IN);
                             break;

        case MODE_ASSIGN:    fprintf(dot_out, "[label = \"= %d\", shape = \"box3d\", "
                                              "color=\"#000000\", style=\"filled\", "
                                              "fillcolor = \"#708090\"]", MODE_ASSIGN);
                             break;

        case MODE_BORN:      fprintf(dot_out, "[label = \"born %d\", shape = \"box3d\", "
                                              "color=\"#000000\", style=\"filled\", "
                                              "fillcolor = \"#EE82EE\"]", MODE_BORN);
                             break;

        case MODE_BIGGER:    fprintf(dot_out, "[label = \"> %d\", shape = \"parallelogram\", "
                                              "color=\"#000000\", style=\"filled\", "
                                              "fillcolor = \"#006400\"]", MODE_BIGGER);
                             break;

        case MODE_EQUAL:     fprintf(dot_out, "[label = \"== %d\", shape = \"parallelogram\", "
                                               "color=\"#000000\", style=\"filled\", "
                                               "fillcolor = \"#FF7F50\"]", MODE_EQUAL);
                             break;

        case MODE_LESS:      fprintf(dot_out, "[label = \"< %d\", shape = \"parallelogram\", "
                                              "color=\"#000000\", style=\"filled\", "
                                              "fillcolor = \"#FFE4B5\"]", MODE_LESS);
                             break;

        case MODE_NOT_EQUAL: fprintf(dot_out, "[label = \"!= %d\", shape = \"parallelogram\", "
                                              "color=\"#000000\", style=\"filled\", "
                                              "fillcolor = \"#FF4500\"]", MODE_NOT_EQUAL);
                             break;

        case MODE_VARIABLES: fprintf(dot_out, "[label = \"variable %d\", shape = \"egg\", "
                                              "color=\"#000000\", style=\"filled\", "
                                              "fillcolor = \"#FFFFFF\"]", MODE_VARIABLES);
                             break;

        case MODE_FUNC:      fprintf(dot_out, "[label = \"function %d\", shape = \"egg\", "
                                              "color=\"#000000\", style=\"filled\", "
                                              "fillcolor = \"#FFFFFF\"]", MODE_FUNC);
                             break;

        case MODE_CALL:      fprintf(dot_out, "[label = \"call %d\", shape = \"egg\", "
                                              "color=\"#000000\", style=\"filled\", "
                                              "fillcolor = \"#FFFFFF\"]", MODE_CALL);
                             break;

        case MODE_RETURN:    fprintf(dot_out, "[label = \"return %d\", shape = \"box3d\", "
                                              "color=\"#000000\", style=\"filled\", "
                                              "fillcolor = \"#F5C32F\"]", MODE_RETURN);
                             break;

        default:             fprintf(dot_out, "\"error\"");
                             break;
    }

    assert(pos);
    assert(dot_out);
}

char* ip = nullptr;
void write_as_std_tree(tree* nameTree, char* buffer) {
    assert_tree(nameTree);

    ip = buffer;
    std_tree_filling(nameTree->Tamyr);

    *ip++ = 0x00;

    assert_tree(nameTree);
}


int skobka = 0;
void std_tree_filling(tree_elem* pos) {
    if (pos->Info.mode == MODE_FUNC) {
        std_tree_filling(pos->Left);

        std_tree_filling(pos->Right);
        return;
    }

    assert(pos->Info.mode == MODE_NAME);

    *ip++ = '#';

    for (int i = 0; pos->Info.name[i]; i++)
        *ip++ = pos->Info.name[i];

    *ip++ = ' ';
    *ip++ = '(';
    if (pos->Right) take_params(pos->Right);
    else            *ip++ = ' ';
    *ip++ = ')';

    take_body(pos->Left);

    *ip++ = '{';
    *ip++ = '}';

    for (int i = 0; i < skobka; i++)
        *ip++ = '}';

    *ip++ = '\n';

    skobka = 0;
}

void take_params(tree_elem* pos) {
    if (pos->Info.mode != MODE_VARIABLES) {
        assert(pos->Info.mode == MODE_VAR);

        for (int i = 0; pos->Left->Info.name[i]; i++)
            *ip++ = pos->Info.name[i];
    }

    assert(pos->Left->Info.mode  == MODE_VAR);
    assert(pos->Right->Info.mode == MODE_VAR);

    *ip++ = ' ';
    for (int i = 0; pos->Left->Info.name[i]; i++)
        *ip++ = pos->Left->Info.name[i];

    *ip++ = ' ';
    *ip++ = ',';
    *ip++ = ' ';

    for (int i = 0; pos->Right->Info.name[i]; i++)
        *ip++ = pos->Right->Info.name[i];

    *ip++ = ' ';
}

#define new_body *ip++ = '{';\
                 *ip++ = M_B;\
                 *ip++ = '{';

#define end_body *ip++ = '}';\
                 skobka++;
                 
                 

void take_body(tree_elem* pos) {
    if (pos->Info.mode == MODE_OPERATORR) {
        take_body(pos->Left);

        take_body(pos->Right);

        return;
    }

    switch (pos->Info.mode) {
        case MODE_BORN: //+
            new_body;

            *ip++ = M_i;

            assert(pos->Left->Info.mode == MODE_VAR);

            for (int i = 0; pos->Left->Info.name[i]; i++)
                *ip++ = pos->Left->Info.name[i];

            end_body;
            break;

        case MODE_IN: //+
            new_body;

            *ip++ = M_S;
            *ip++ = 0x30;

            assert(pos->Left->Info.mode == MODE_VAR);

            *ip++ = '{';
            *ip++ = M_P;

            take_body(pos->Left);

            *ip++ = '{';
            *ip++ = '}';
            *ip++ = '}';

            end_body;
            break;

        case MODE_OUT:
            new_body;

            *ip++ = M_S;
            *ip++ = 0x31;

            *ip++ = '{';
            *ip++ = M_P;

            take_body(pos->Left);

            *ip++ = '{';
            *ip++ = '}';
            *ip++ = '}';

            end_body;
            break;

        case MODE_ASSIGN:
            new_body;

            *ip++ = M_e;

            assert(pos->Left->Info.mode == MODE_VAR);

            take_body(pos->Left);
            take_body(pos->Right);

            end_body;
            break;

        case MODE_IF:
            new_body;

            *ip++ = M_I;

            take_body(pos->Left);
            take_body(pos->Right);

            end_body;
            break;

        case MODE_CALL:
            new_body;

            *ip++ = M_C;

            assert(pos->Left->Info.mode == MODE_VAR);

            for (int i = 0; pos->Left->Info.name[i]; i++)
                *ip++ = pos->Left->Info.name[i];

            if (pos->Right) take_body(pos->Right);
            else {
                *ip++ = '{';
                *ip++ = '}';
            }

            end_body;

            break;

        case MODE_SIGN:
            *ip++ = '{';
            *ip++ = M_s;
            *ip++ = (char) pos->Info.number;

            take_body(pos->Left);
            take_body(pos->Right);

            *ip++ = '}';
            break;

        case MODE_LOOP:
            *ip++ = '{';

            *ip++ = M_L;

            take_body(pos->Left);
            take_body(pos->Right);

            *ip++ = '}';
            break;

        case MODE_BIGGER:
            *ip++ = '{';

            *ip++ = M_O;
            *ip++ = '>';

            take_body(pos->Left);
            take_body(pos->Right);

            *ip++ = '}';
            break;

        case MODE_LESS:
            *ip++ = '{';

            *ip++ = M_O;
            *ip++ = '<';

            take_body(pos->Left);
            take_body(pos->Right);

            *ip++ = '}';
            break;

        case MODE_NOT_EQUAL:
            *ip++ = '{';

            *ip++ = M_O;
            *ip++ = '!';

            take_body(pos->Left);
            take_body(pos->Right);

            *ip++ = '}';
            break;

        case MODE_EQUAL:
            *ip++ = '{';

            *ip++ = M_O;
            *ip++ = '=';

            take_body(pos->Left);
            take_body(pos->Right);

            *ip++ = '}';
            break;

        case MODE_RETURN:
            *ip++ = '{';

            *ip++ = M_R;

            take_body(pos->Left);

            *ip++ = '}';

            break;

        case MODE_VAR: //+
            *ip++ = '{';

            *ip++ = M_V;
            for (int i = 0; pos->Info.name[i]; i++)
                *ip++ = pos->Info.name[i];

            *ip++ = '}';
            break;

        case MODE_NUMBER: //+
            *ip++ = '{';

            *ip++ = M_N;
            *((int*) ip) = pos->Info.number;
            ip += sizeof(int);

            *ip++ = '}';
            break;

        case MODE_OP:

            break;

        case MODE_VARIABLES:
            *ip++ = '{';
            *ip++ = M_P;

            take_body(pos->Left);
            take_body(pos->Right);

            *ip++ = '}';
            break;
    }
}