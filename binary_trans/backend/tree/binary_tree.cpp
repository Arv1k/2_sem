#include "binary_tree.h"

bool TreeCtor(tree* nameTree) {
    assert(nameTree);

    nameTree->count = 0;

    assert_tree(nameTree);
    return true;
}

tree_elem* TreeAdd(tree* nameTree, data_t elem, char branch, tree_elem* position) {
    assert_tree(nameTree);

    tree_elem* element = (tree_elem*) calloc(1, sizeof(tree_elem));
    element->Info = elem;

    if (nameTree->count == 0) {
        element->Parent = nullptr;

        nameTree->Tamyr = element;
        nameTree->count++;

        assert_tree(nameTree);
        return element;
    }

    if (branch == 'L') {
        element->Parent = position;

        position->Left = element;

        nameTree->count++;
    }

    if (branch == 'R') {
        element->Parent = position;

        position->Right = element;

        nameTree->count++;
    }

    assert_tree(nameTree);
    return nullptr;
}

tree_elem* TreeNode(tree* nameTree, data_t elem, char branch, tree_elem* position) {
    assert_tree(nameTree);
    assert(position);

    tree_elem* element = (tree_elem*) calloc(1, sizeof(tree_elem));
    element->Info = elem;

    element->Parent = position->Parent;
    position->Parent = element;

    if      (branch == 'L') element->Left = element;
    else if (branch == 'R') element->Right = element;

    assert_tree(nameTree);
    return nullptr;
}


Var variables[32] = {};
int pos = 0;
int num = 0;
int jump = 0;
int jump_tmp = 0;
int jump_tmp1 = 0;

Call calls[32] = {};
int pos_calls = 0;

int tempo = 0;

void TreePrint(tree_elem* position, FILE* enterTree) {
    if (!position) return;

    switch ((position->Info).mode) {
        case MODE_CALL:
            if (func_search(position->Left) != -1) {
                fprintf(enterTree, "call :%d\n", calls[func_search(position->Left)].jumpNum);

                return;
            }

            fprintf(enterTree, "call :%d\n", jump);

            calls[pos_calls].name = ((position->Left)->Info).name;
            calls[pos_calls].jumpNum = jump;

            jump++;

            if (!position->Right) {
                pos_calls++;

                return;
            }
            else if (((position->Right)->Info).mode == MODE_VARIABLES) {
                (calls[pos_calls].perem)[0] = Place_op((position->Right)->Left);
                (calls[pos_calls].perem)[1] = Place_op((position->Right)->Right);
            }

            else (calls[pos_calls].perem)[0] = Place_op(position->Right);

            pos_calls++;

            return;

        case MODE_FUNC:
            TreePrint(position->Left, enterTree);
            fprintf(enterTree, "\n\n");
            TreePrint(position->Right, enterTree);

            return;

        case MODE_NAME:
            if (strcmp((position->Info).name, "баш") == 0) {
                TreePrint(position->Left, enterTree);
                TreePrint(position->Right, enterTree);

                fprintf(enterTree, "end\n");

                return;
            }

            tempo = Place_func(position);

            fprintf(enterTree, ":%d\n", calls[tempo].jumpNum);

            if (!position->Right) {
                TreePrint(position->Left, enterTree);
                fprintf(enterTree, "ret");

                return;
            }
            else if (((position->Right)->Info).mode == MODE_VARIABLES) {
                variables[num].Name = (((position->Right)->Left)->Info).name;
                variables[num].position = calls->perem[0];
                num++;

                variables[num].Name = (((position->Right)->Right)->Info).name;
                variables[num].position = calls->perem[1];
                num++;
            }

            else {
                variables[num].Name = ((position->Right)->Info).name;
                variables[num].position = calls->perem[0];
                num++;
            }

            TreePrint(position->Left, enterTree);
            fprintf(enterTree, "ret");

            return;

        case MODE_BORN:
            variables[num].Name = ((position->Left)->Info).name;
            variables[num].position = pos;
            pos++;
            num++;

            return;

        case MODE_LOOP:
            fprintf(enterTree, ":%d\n", jump);

            jump_tmp = jump;
            jump++;

            TreePrint(position->Left, enterTree);

            fprintf(enterTree, ":%d\n", jump);

            jump_tmp1 = jump;
            jump++;

            TreePrint(position->Right, enterTree);

            fprintf(enterTree, "jmp :%d\n", jump_tmp);

            fprintf(enterTree, ":%d\n", jump_tmp1);

            return;

        case MODE_IF:
            TreePrint(position->Left, enterTree);

            fprintf(enterTree, ":%d\n", jump);

            TreePrint(position->Right, enterTree);

            fprintf(enterTree, ":%d\n", jump);

            jump++;

            return;

        case MODE_ASSIGN:
            TreePrint(position->Right, enterTree);

            fprintf(enterTree, "pop [%d]\n", Place_op(position->Left));
            return;

        case MODE_IN:
            fprintf(enterTree, "in\n");

            fprintf(enterTree, "pop [%d]\n", Place_op(position->Left));

            return;
    }

    TreePrint(position->Left, enterTree);
    TreePrint(position->Right, enterTree);

    switch ((position->Info).mode) {
        case MODE_OP:
            fprintf(enterTree, "%s\n", (position->Info).name);
            break;

        case MODE_SIGN:
            if      ((position->Info).number == '+') fprintf(enterTree, "add\n");
            else if ((position->Info).number == '-') fprintf(enterTree, "sub\n");
            else if ((position->Info).number == '*') fprintf(enterTree, "mul\n");
            else if ((position->Info).number == '/') fprintf(enterTree, "div\n");

            break;

        case MODE_VAR:
            fprintf(enterTree, "push [%d]\n", Place_op(position));
            break;

        case MODE_NUMBER:
            fprintf(enterTree, "push %d\n", (position->Info).number);
            break;

        case MODE_OPERATORR:
            break;

        case MODE_OUT:
            fprintf(enterTree, "out\n");
            break;

        case MODE_RETURN:
            fprintf(enterTree, "pop rax\n"
                               "ret\n");
            break;

        case MODE_BIGGER:
            fprintf(enterTree, "ja ");
            break;

        case MODE_EQUAL:
            fprintf(enterTree, "jrc ");
            break;

        case MODE_LESS:
            fprintf(enterTree, "jb ");
            break;

        case MODE_NOT_EQUAL:
            fprintf(enterTree, "jc ");
            break;

        default:
            printf("ERROR!!!\n");
            abort();
    }
}

bool TreeDtor(tree* nameTree) {
    assert_tree(nameTree);

    TreeDoyElems(nameTree->Tamyr, &nameTree->count);

    nameTree->count = yad_count;
    nameTree->Tamyr = nullptr;

    assert(nameTree);
    return true;
}

void TreeDoyElems(tree_elem* position, size_t* con) {
    if (!position) return;

    TreeDoyElems(position->Left, con);
    TreeDoyElems(position->Right, con);

    position->Parent = nullptr;
    position->Left = nullptr;
    position->Right = nullptr;

    if ((position->Info).name != nullptr) free((position->Info).name);

    (position->Info).name = nullptr;
    (position->Info).number = yad_num;
    (position->Info).mode   = yad_mode;

    free(position);
    (*con)--;
}

void TreeElemsOK(tree_elem* position, int* i) {
    if (!position) return;

    TreeElemsOK(position->Left, i);
    TreeElemsOK(position->Right, i);

    (*i)++;
}

bool TreeOK(tree* nameTree) {
    if (!nameTree)                                               return false;
    if (nameTree->count == 0 && nameTree->Tamyr == nullptr)      return true;
    else if (nameTree->count == 0 || nameTree->Tamyr == nullptr) return false;

    int i = 0;
    TreeElemsOK(nameTree->Tamyr, &i);
    if (i != nameTree->count)                                    return false;

    return true;
}

bool is_leaf(tree_elem* position) {
    assert(position);

    if (!position->Left && !position->Right) return true;

    return false;
}

/*tree_elem* TreeSearch(tree_elem* position, data_t elem) {
    if (!position) return nullptr;

    if (strcmp(position->Info, elem) == 0){
        return position;
    }

    tree_elem* cur = nullptr;

    cur = TreeSearch(position->Left, elem);
    if (!cur) cur = TreeSearch(position->Right, elem);

    return cur;
}*/

int Place_op(tree_elem* position) {
   for (int i = 0; i < 32; i++)
       if(strcmp(variables[i].Name, (position->Info).name) == 0)
           return variables[i].position;


   printf("Variable %s is not initialized!!!\n", (position->Info).name);
   abort();
}

int Place_func(tree_elem* position) {
    assert((position->Info).name);

    for (int i = 0; i < 32; i++) {
        if (calls[i].name != nullptr)
            if (strcmp(calls[i].name, (position->Info).name) == 0)
                return i;
    }


    printf("Function %s is not initialized!!!\n", (position->Info).name);
    abort();
}

int func_search(tree_elem* position) {
    assert((position->Info).name);

    for (int i = 0; i < 32; i++) {
        if (calls[i].name != nullptr)
            if (strcmp(calls[i].name, (position->Info).name) == 0)
                return i;
    }

    return -1;
}


