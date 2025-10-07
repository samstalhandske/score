#ifdef SCORE_LINKED_LIST

#include "linked_list.h"

#include <stdlib.h>
#include <assert.h>

static Score_Linked_List_Node *score_linked_listcreate_node(void *data) {
    Score_Linked_List_Node *node = (Score_Linked_List_Node *)malloc(sizeof(Score_Linked_List_Node));
    if (node == NULL) {
        free(node);
        return NULL;
    }

    node->data = data;
    node->prev = NULL;
    node->next = NULL;
    return node;
}

bool score_linked_listadd(Score_Linked_List *list, void *data) {
    if (list == NULL) {
        return false;
    }

    Score_Linked_List_Node *node = score_linked_listcreate_node(data);
    if (node == NULL) {
        return false;
    }

    if (list->tail == NULL) {
        list->head = node;
        list->tail = node;
    }
    else {
        node->prev = list->tail;

        list->tail->next = node;
        list->tail = node;
    }

    list->size++;
    return true;
}

int score_linked_listremove(Score_Linked_List *list, Score_Linked_List_Node *node) {
    if (list == NULL || node == NULL) {
        return false;
    }

    assert(list->size > 0);

    if (node->prev != NULL) {
        node->prev->next = node->next;
    }
    else {
        list->head = node->next;
    }

    if (node->next != NULL) {
        node->next->prev = node->prev;
    }
    else {
        list->tail = node->prev;
    }

    free(node);
    list->size--;

    return true;
}

void score_linked_listclear(Score_Linked_List *list) {
    if (list == NULL) {
        return;
    }

    Score_Linked_List_Node *curr = NULL;
    Score_Linked_List_Node *next = NULL;

    curr = list->head;
    while (curr != NULL) {
        next = curr->next;
        free(curr);

        curr = next;
    }

    list->head = NULL;
    list->tail = NULL;
    list->size = 0;
}

Score_Linked_List_Node *score_linked_listfront(const Score_Linked_List *list) {
    if (list == NULL) {
        return NULL;
    }

    return list->head;
}

Score_Linked_List_Node *score_linked_listback(const Score_Linked_List *list) {
    if (list == NULL) {
        return NULL;
    }

    return list->tail;
}

bool score_linked_listis_empty(const Score_Linked_List *list) {
    if (list == NULL) {
        return true;
    }

    return list->size == 0;
}

unsigned int score_linked_listsize(const Score_Linked_List *list) {
    if (list == NULL) {
        return false;
    }

    return list->size;
}

Score_Linked_List_Node *score_linked_listfind(const Score_Linked_List *list,
                                    void *data,
                                    Score_Linked_List_Compare_Function compare)
{
    if (list == NULL || compare == NULL) {
        return NULL;
    }

    Score_Linked_List_Node *curr = list->head;
    while (curr != NULL) {
        if (compare(curr->data, data)) {
            return curr;
        }

        curr = curr->next;
    }

    return NULL;
}

void score_linked_listforeach(const Score_Linked_List *list,
                         Score_Linked_List_Foreach_Callback callback,
                         void *user) {
    if (list == NULL || callback == NULL) {
        return;
    }

    Score_Linked_List_Node *curr = list->head;
    while (curr != NULL) {
        callback(curr->data, user);
        curr = curr->next;
    }
}

#endif