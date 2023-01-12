#include "dll.h"
#include <stdio.h>
#include <stdlib.h>
 
list_t* create_list()  // return a newly created empty doubly linked list
{
	// DO NOT MODIFY!!!
	list_t* l = (list_t*) malloc(sizeof(list_t));
	l->head = NULL;
	l->tail = NULL;
	l->size = 0;
	return l;
}

void insert_front(list_t* list, int data)  // TODO: inserts data to the beginning of the linked list
{
	node_t *t=(node_t*)malloc(sizeof(node_t));
    t->data=data;
    t->next=NULL;
    t->prev=NULL;
    if(list->head==NULL)
    {
        list->head=t;
        list->tail=t;
    }
    else
    {
        t->next=list->head;
        list->head->prev=t;
        list->head=t;

    }
    list->size++;
}

void insert_back(list_t* list, int data) // TODO: inserts data to the end of the linked list
{
	node_t *t=(node_t*)malloc(sizeof(node_t));
    t->data=data;
    t->next=NULL;
    t->prev=NULL;
    if(list->head==NULL)
    {
        list->head=t;
        list->tail=t;
    }
    else{
        t->prev=list->tail;
        list->tail->next=t;
        list->tail=t;
    }
    list->size++;
}

void insert_after(list_t* list, int data, int prev) // TODO: inserts data after the node with data “prev”. Do not insert or do anything if prev doesn't exist
{
	node_t *t=(node_t*)malloc(sizeof(node_t));
    t->data=data;
    t->next=NULL;
    t->prev=NULL;
    if(list->head==NULL)
    {
        list->head=t;
        list->tail=t;
    }
    else
    {
        node_t *p=list->head;
        while(p && p->data!=prev)
        {
            p=p->next;
        }
        if(p==NULL)
        {
            return;
        }
        else if(p->data==prev)
        {
            if(p->next==NULL)
            {
                list->tail=t;
                p->next=t;
                t->prev=p;
            }
            else{
                t->next=p->next;
                t->prev=p;
                p->next->prev=t;
                p->next=t;
            }
        }

    }
    list->size++;
}

void delete_front(list_t* list) // TODO: delete the start node from the linked list.
{
	node_t *t=list->head;
    if(t==NULL)
    {
        return;
    }
    if(t->next!=NULL)
        {
            list->head=t->next;
            t->next->prev=NULL;
        }
    else
        {list->head=NULL;
        list->tail=NULL;}
    free(t);
}

void delete_back(list_t* list) // TODO: delete the end node from the linked list.
{
	node_t *p=list->head;
    if(p==NULL)
    {
        return;
    }
    if(list->head==list->tail)
    {
        free(p);
        list->head=NULL;
        list->tail=NULL;
        list->size--;
        return;
    }
    
    p=list->tail;
    list->tail=p->prev;
    list->tail->next=NULL;
    list->size--;
    free(p);
    
}

void delete_node(list_t* list, int data) // TODO: delete the node with “data” from the linked list.
{
	node_t *p=list->head;
    if(p==NULL)
    {
        return;
    }
    while(p && p->data!=data)
    {
        p=p->next;
    }
    if(p==NULL)
    {
        return;
    }
    else{
        if(list->head==p && list->tail==p)
        {
            //printf("%d\n",p->data);
            free(p);
            list->head=NULL;
            list->tail=NULL;
        }
        else if(p==list->head)
        {
            list->head=p->next;
            list->head->prev=NULL;
            list->size--;
            free(p);
        }
        else if(p==list->tail)
        {
            list->tail=p->prev;
            list->tail->next=NULL;
            list->size--;
            free(p);
        }
        else{
            p->prev->next=p->next;
            p->next->prev=p->prev;
            list->size--;
            free(p);
        }
    }
}

node_t* search(list_t* list, int data) // TODO: returns the pointer to the node with “data” field. Return NULL if not found.
{	
    if(list->head==NULL)
    {
        return NULL;
    }
	node_t *p=list->head;
    while(p)
    {
        if(p->data==data)
        return p;
        p=p->next;
    }
    return NULL;
}

int is_empty(list_t* list) // return true or 1 if the list is empty; else returns false or 0
{
	// DO NOT MODIFY!!!
	return list->size == 0;
}

int size(list_t* list) // returns the number of nodes in the linked list.  
{
	// DO NOT MODIFY!!!
	return list->size;
}

void delete_nodes(node_t* head) // helper
{
	// DO NOT MODIFY!!!
	if(head == NULL)
		return;
	delete_nodes(head->next);
	free(head);	
}

void delete_list(list_t* list) // free all the contents of the linked list
{
	// DO NOT MODIFY!!!
	delete_nodes(list->head);
	free(list);
}

void display_list(list_t* list) // print the linked list by separating each item by a space and a new line at the end of the linked list.
{
	// DO NOT MODIFY!!!
	node_t* it = list->head;
	while(it != NULL)
	{
		printf("%d ", it->data);
		it = it->next;
	}
	printf("\n");
}


