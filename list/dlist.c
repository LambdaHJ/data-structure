#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "dlist.h"

void dlist_init(DList *list, void (*destroy)(void *data))
{
    list->size = 0;
    list->destroy = destroy;
    list->head = NULL;
    list->tail = NULL;
}

void dlist_destroy(DList *list)
{
    void *data = NULL;

    while (dlist_size(list) > 0)
    {
        if (list->destroy != NULL && dlist_remove(list, dlist_tail(list), (void **)data) == 0)
        {
            list->destroy(data);
        }
    }

    memset(list, 0, sizeof(DList));

    return;
}

int dlist_ins_next(DList *list, DListElmt *element, const void *data)
{
    DListElmt *new_element;
    if (element == NULL && dlist_size(list) !=0)
    {
        return -1;
    }

    if ((new_element = (DListElmt *)malloc(sizeof(DListElmt))) == NULL)
    {
        return -1;
    }

    new_element->data = (void *)data;

    if (dlist_size(list) == 0)
    {
        list->head = new_element;
        list->tail = new_element;
        new_element->pre = NULL;
        new_element->next = NULL;

    }
    else
    {
        new_element->next = element->next;
        new_element->pre = element;

        if (element->next == NULL)
        {
            list->tail = new_element;
        }
        else
        {
            element->next->pre = new_element;
        }

        element->next = new_element;
    }

    list->size++;
    return 0;
}

int dlist_ins_pre(DList *list, DListElmt *element, const void *data)
{
    DListElmt *new_element;
    if (element == NULL && dlist_size(list) !=0)
    {
        return -1;
    }

    if ((new_element = (DListElmt *)malloc(sizeof(DListElmt))) == NULL)
    {
        return -1;
    }

    new_element->data = (void *)data;

    if (dlist_size(list) == 0)
    {
        list->head = new_element;
        list->tail = new_element;
        new_element->pre = NULL;
        new_element->next = NULL;

    }
    else
    {
        new_element->next = element;
        new_element->pre = element->pre;

        if (element->pre == NULL)
        {
            list->head = new_element;
        }
        else
        {
            element->pre->next = new_element;
        }

        element->pre = new_element;
    }

    list->size++;
    return 0;
}

int dlist_remove(DList *list, DListElmt *element, void **data)
{
    if (element == NULL || dlist_size(list) == 0)
    {
        return 0;
    }

    *data = element->data;

    if (element == list->head)
    {
        list->head = element->next;
        if (list->head == NULL)
        {
            list->tail = NULL;
        }
        else
        {
            element->next->pre = NULL;
        }
    }
    else
    {
        element->pre->next = element->next;
        if (element->next == NULL)
        {
            list->tail = element->pre;
        }
        else
        {
            element->next->pre = element->pre;
        }
    }

    free(element);

    list->size--;
    return 0;
}
