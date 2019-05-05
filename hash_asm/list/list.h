#ifndef HASH_ASM_LIST_H
#define HASH_ASM_LIST_H



#include <cstdio>
#include <cstdlib>
#include <cassert>
#include <cmath>
#include <cstring>
#include <fstream>


/*#define assert_list(nameList) {\
    if ( !(nameList->list_check()) ) {\
        printf("| !!! Assertion failed !!!\n");\
        printf("|       what: ListOK(),\n");\
        printf("|       in: %s,\n", __FILE__);\
        printf("|       function: %s,\n",  __PRETTY_FUNCTION__);\
        printf("|       on: %d line.\n", __LINE__);\
        printf("| !!! Look at DumpList !!!");\
        nameList->list_dump();\
        abort();\
    }\
}


#define assert_var(variable) {\
    if ( !(std::isfinite(variable)) ) {\
        printf("| !!!Assertion failed!!!\n");\
        printf("|       what: variable error!,\n");\
        printf("|       in: %s,\n", __FILE__);\
        printf("|       function: %s,\n",  __PRETTY_FUNCTION__);\
        printf("|       on: %d line.\n", __LINE__);\
        abort();\
    }\
}*/

typedef char* data_t;

const int yad_count = 119;
//const data_t yad_elem = nullptr;


class list_elem {
public:
    data_t     Info = nullptr;
    list_elem* Next = nullptr;
    list_elem* Prev = nullptr;
};


class list {
private:
    list_elem* Head;
    list_elem* Tail;
    size_t     count;

    bool list_check();

public:
    list();
    ~list();

    bool pop_front();
    bool pop_back();
    bool delete_elem(list_elem* position);

    list_elem* push_front(data_t elem);
    list_elem* push_back(data_t elem);
    list_elem* insert_before(data_t elem, list_elem* position);
    list_elem* insert_after(data_t elem, list_elem* position);

    size_t size() const;
    list_elem* head() const;

    void list_dump();
};



#endif //HASH_ASM_LIST_H
