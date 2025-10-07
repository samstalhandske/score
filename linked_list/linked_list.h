#ifdef SCORE_LINKED_LIST

#ifndef SCORE_LINKED_LIST_H
#define SCORE_LINKED_LIST_H

#include <stddef.h>
#include <stdbool.h>

typedef struct Score_Linked_List_Node Score_Linked_List_Node;

typedef struct Score_Linked_List_Node {
    void *data;
    Score_Linked_List_Node *prev;
    Score_Linked_List_Node *next;
} Score_Linked_List_Node;

typedef struct {
    Score_Linked_List_Node *head;
    Score_Linked_List_Node *tail;
    unsigned int size;
} Score_Linked_List;

typedef enum {
    Equal,
    Not_Equal,
} Score_Linked_List_Compare_Result;

typedef Score_Linked_List_Compare_Result (*Score_Linked_List_Compare_Function)(void *a, void *b);
typedef void (*Score_Linked_List_Foreach_Callback)(void *data, void *user);

bool score_linked_list_add(Score_Linked_List *list, void *data);
bool score_linked_list_remove(Score_Linked_List *list, Score_Linked_List_Node *node);
void score_linked_list_clear(Score_Linked_List *list);

Score_Linked_List_Node *score_linked_list_front(const Score_Linked_List *list);
Score_Linked_List_Node *score_linked_list_back(const Score_Linked_List *list);

bool score_linked_list_is_empty(const Score_Linked_List *list);
unsigned int score_linked_list_size(const Score_Linked_List *list);

Score_Linked_List_Node *score_linked_list_find(const Score_Linked_List *list,
                                        void *data,
                                        Score_Linked_List_Compare_Function compare);

void score_linked_list_foreach(const Score_Linked_List *list,
                            Score_Linked_List_Foreach_Callback callback,
                            void *user);

#endif

#endif