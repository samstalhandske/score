#ifdef SCORE_LINKED_LIST

#include "linked_list.h"

#include <stdlib.h>
#include <assert.h>

static SCore_Linked_List_Node *score_linked_list_create_node(void *data) {
    SCore_Linked_List_Node *node = (SCore_Linked_List_Node *)malloc(sizeof(SCore_Linked_List_Node));
    if (node == NULL) {
        free(node);
        return NULL;
    }

    node->data = data;
    node->prev = NULL;
    node->next = NULL;
    return node;
}

SCORE_BOOL score_linked_list_add(SCore_Linked_List *list, void *data) {
    SCore_Linked_List_Node *created_node = NULL;

    if (list == NULL) {
        return SCORE_FALSE;
    }

    created_node = score_linked_list_create_node(data);
    if (created_node == NULL) {
        return SCORE_FALSE;
    }

    if (list->tail == NULL) {
        list->head = created_node;
        list->tail = created_node;
    }
    else {
        created_node->prev = list->tail;

        list->tail->next = created_node;
        list->tail = created_node;
    }

    list->size++;
    return SCORE_TRUE;
}

SCORE_BOOL score_linked_list_remove(SCore_Linked_List *list, SCore_Linked_List_Node *node) {
    if (list == NULL || node == NULL) {
        return SCORE_FALSE;
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

    return SCORE_TRUE;
}

void score_linked_list_clear(SCore_Linked_List *list) {
    SCore_Linked_List_Node *curr = NULL;
    SCore_Linked_List_Node *next = NULL;

    if (list == NULL) {
        return;
    }

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

SCore_Linked_List_Node *score_linked_list_front(const SCore_Linked_List *list) {
    if (list == NULL) {
        return NULL;
    }

    return list->head;
}

SCore_Linked_List_Node *score_linked_list_back(const SCore_Linked_List *list) {
    if (list == NULL) {
        return NULL;
    }

    return list->tail;
}

SCORE_BOOL score_linked_list_is_empty(const SCore_Linked_List *list) {
    if (list == NULL) {
        return SCORE_TRUE;
    }

    return list->size == 0;
}

unsigned int score_linked_list_size(const SCore_Linked_List *list) {
    if (list == NULL) {
        return SCORE_FALSE;
    }

    return list->size;
}

SCore_Linked_List_Node *score_linked_list_find(const SCore_Linked_List *list, void *data, SCore_Linked_List_Compare_Function compare) {
    SCore_Linked_List_Node *curr = NULL;

    if (list == NULL || compare == NULL) {
        return NULL;
    }

    curr = list->head;
    while (curr != NULL) {
        if (compare(curr->data, data)) {
            return curr;
        }

        curr = curr->next;
    }

    return NULL;
}

void score_linked_list_foreach(const SCore_Linked_List *list, SCore_Linked_List_Foreach_Callback callback, void *user) {
    SCore_Linked_List_Node *curr = NULL;

    if (list == NULL || callback == NULL) {
        return;
    }

    curr = list->head;
    while (curr != NULL) {
        callback(curr->data, user);
        curr = curr->next;
    }
}

#endif