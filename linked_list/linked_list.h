#ifdef SCORE_LINKED_LIST

#ifndef SCORE_LINKED_LIST_H
#define SCORE_LINKED_LIST_H

#include <stddef.h>

typedef struct SCore_Linked_List_Node SCore_Linked_List_Node;

typedef struct SCore_Linked_List_Node {
    void *data;
    SCore_Linked_List_Node *prev;
    SCore_Linked_List_Node *next;
} SCore_Linked_List_Node;

typedef struct {
    SCore_Linked_List_Node *head;
    SCore_Linked_List_Node *tail;
    unsigned int size;
} SCore_Linked_List;

typedef enum {
    Equal,
    Not_Equal,
} SCore_Linked_List_Compare_Result;

typedef SCore_Linked_List_Compare_Result (*SCore_Linked_List_Compare_Function)(void *a, void *b);
typedef void (*SCore_Linked_List_Foreach_Callback)(void *data, void *user);

SCORE_BOOL score_linked_list_add(SCore_Linked_List *list, void *data);
SCORE_BOOL score_linked_list_remove(SCore_Linked_List *list, SCore_Linked_List_Node *node);
void score_linked_list_clear(SCore_Linked_List *list);

SCore_Linked_List_Node *score_linked_list_front(const SCore_Linked_List *list);
SCore_Linked_List_Node *score_linked_list_back(const SCore_Linked_List *list);

SCORE_BOOL score_linked_list_is_empty(const SCore_Linked_List *list);
unsigned int score_linked_list_size(const SCore_Linked_List *list);

SCore_Linked_List_Node *score_linked_list_find(const SCore_Linked_List *list,
                                        void *data,
                                        SCore_Linked_List_Compare_Function compare);

void score_linked_list_foreach(const SCore_Linked_List *list,
                            SCore_Linked_List_Foreach_Callback callback,
                            void *user);

#endif

#endif