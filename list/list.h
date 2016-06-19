//
//  list.h
//  DataStructure
//
//  Created by 黄金 on 16/6/5.
//  Copyright © 2016年 黄金. All rights reserved.
//

#ifndef list_h
#define list_h

// Define a structure for linked list element.
typedef struct ListElmt_{
    void *data;
    struct ListElmt_ *next;
} ListElmt;

// Define a structure for linked lists.
typedef struct List_{
    int size;
    int (*match)(const void *key1, const void *key2);
    void (*destroy)(void *data);
    ListElmt *head;
    ListElmt *tail;
} List;

//Public Interface

void list_init(List *list, void (*destroy)(void *data));
void list_destroy(List *list);
int list_ins_next(List *list, ListElmt *element, const void *data);
int list_rem_next(List *list, ListElmt *element, void **data);


#define list_size(list) ((list)->size)
#define list_head(list) ((list)->head)
#define list_tail(list) ((list)->tail)

#define list_is_head(list, element) ((list)->head == (element) ? 1: 0)
#define list_is_tail(list, element) ((element)->next == NULL ? 1: 0)
#define list_data(element) ((element)->data)
#define list_next(element) ((element)->next)

#endif /* list_h */
