#include "list.h"

list::list():
        count(0),
        Head(nullptr),
        Tail(nullptr) {}

bool list::pop_front() {
    if (count == 0) {
        printf("There isn't any element to pop from front!!!\n");

        return true;
    }

    else if (Head == Tail) {
        delete Head;

        Head = nullptr;
        Tail = nullptr;
        count = 0;

        return true;
    }

    Head = (Head)->Next;

    (Head->Prev)->Next = nullptr;
    (Head->Prev)->Info = nullptr;

    delete Head->Prev;

    Head->Prev = nullptr;

    count--;

    return true;
}

bool list::pop_back() {
    if (count == 0) {
        printf("There isn't any element to pop from back!!!\n");

        return true;
    }

    else if (Head == Tail) {
        delete Tail;

        Tail = nullptr;
        Head = nullptr;
        count = 0;

        return true;
    }

    Tail = Tail->Prev;

    (Tail->Next)->Prev = nullptr;
    (Tail->Next)->Info = nullptr;

    delete Tail->Next;

    Tail->Next = nullptr;

    count--;

    return true;
}

list_elem* list::push_front(data_t elem) {
    auto element = new list_elem;

    element->Info = elem;

    if (count == 0) {
        Head = element;
        Tail = element;

        count = 1;

        return element;
    }

    Head->Prev = element;

    element->Next = Head;

    Head = element;

    count++;

    return element;
}

list_elem* list::push_back(data_t elem) {
    auto element = new list_elem;

    element->Info = elem;

    if (count == 0) {
        Head = element;
        Tail = element;

        count = 1;

        return element;
    }

    Tail->Next = element;

    element->Prev = Tail;

    Tail = element;

    count++;

    return element;
}



list_elem* list::insert_before(data_t elem, list_elem* position) {
    assert(position);

    if (count == 0) {
        printf("There aren't any elements!!!\n");

        return nullptr;
    }

    if (position->Prev == nullptr) return push_front(elem);

    auto element = new list_elem;

    element->Info = elem;

    (position->Prev)->Next = element;
    element->Prev = position->Prev;
    position->Prev = element;

    element->Next = position;

    if (element->Prev == nullptr) Head = element;

    count++;

    return element;
}

list_elem* list::insert_after(data_t elem, list_elem* position) {
    assert(position);

    if (count == 0) {
        printf("There aren't any elements!!!\n");

        return nullptr;
    }

    if (position->Next == nullptr) return push_back(elem);

    auto element = new list_elem;

    element->Info = elem;

    (position->Next)->Prev = element;
    element->Next = position->Next;
    position->Next = element;

    element->Prev = position;

    if (element->Next == nullptr) Tail = element;

    count++;

    return element;
}

bool list::delete_elem(list_elem* position) {
    assert(position);

    if (count == 0) {
        printf("There aren't any elements!!!\n");

        return false;
    }

    if (position->Next == nullptr) {
        pop_back();

        return true;
    }

    else if (position->Prev == nullptr) {
        pop_front();

        return true;
    }

    (position->Prev)->Next = position->Next;
    (position->Next)->Prev = position->Prev;

    position->Info = nullptr;
    position->Next = nullptr;
    position->Prev = nullptr;

    count--;

    free(position);

    return true;
}

//$do(wtf)  { printf ("%s:\n", #wtf); wtf; }


list::~list() {
    assert(list_check());

    if (count != 0) {
        size_t iskan = count;

        for (int i = 0; i < iskan; i++) pop_back();
    }

    count = yad_count;
}

bool list::list_check() {
    if (Tail == nullptr && Head == nullptr && count == yad_count) return true;

    if (Tail == nullptr && Head == nullptr)                       return !count;

    if (Tail == nullptr || Head == nullptr)                       return false;

    return count;
}

size_t list::size() const {
    return count;
}

list_elem* list::head() const {
    return Head;
}


void list::list_dump() {
    FILE* Dump = fopen("DumpList.txt", "a+");

    fprintf(Dump ,"#----------------------------------------------------------\n");
    fprintf(Dump ,"# List [%p] ", this);

    fprintf(Dump ,"{\n");

    fprintf(Dump, "#     Head [%p] ", Head);
    if (Head == nullptr) fprintf(Dump, "nullptr; (?)\n");
    else {
        if (!Head->Info) fprintf(Dump, "nullptr; (!!!)\n");
        else             fprintf(Dump, "%s;\n", Head->Info);
    }

    fprintf(Dump, "#     Tail [%p] ", Tail);

    if (Tail == nullptr) fprintf(Dump, "nullptr; (?)\n");
    else {
        if (!Tail->Info) fprintf(Dump, "nullptr; (!!!)\n");
        else             fprintf(Dump, "%s;\n", Tail->Info);
    }

    fprintf(Dump, "#     Count ");

    if (count == yad_count) {
        fprintf(Dump, "%lu; (!!!yad!!!)\n", count);
        fprintf(Dump, "# }\n");

        fprintf(Dump, "#----------------------------------------------------------\n");

        return;
    }

    else if (count == 0) {
        fprintf(Dump, "%lu; (?)\n", count);
        fprintf(Dump, "# }\n");

        fprintf(Dump, "#----------------------------------------------------------\n");

        return;
    }

    fprintf(Dump, "%lu;\n", count);

    fprintf(Dump, "#     Elements {\n");

    list_elem* prom = Head;
    for (int i = 1; i <= count; i++) {
        fprintf(Dump, "#         %d:  [%p]  %s\n", i, prom, prom->Info);

        prom = prom->Next;
    }

    fprintf(Dump, "#     }\n");
    fprintf(Dump, "# }\n");
    fprintf(Dump, "#----------------------------------------------------------\n\n");

    fclose(Dump);
}