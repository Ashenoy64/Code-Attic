#include <stdio.h>
#include <stdlib.h>


typedef struct node{
    int key;
    struct node* link;
}node_t;


typedef struct list{
    node_t* head;
}list_t;


void display(list_t* ptr_list){
    if(ptr_list->head == NULL){
        printf("\n\nList is empty\n");
    }
    else{
        node_t* temp;
        temp = ptr_list->head;
        printf("The list is:  ");
        while(temp != NULL){
            printf("%d ",temp->key);
            temp = temp->link;
        }
        printf("\n\n\n");
    }
}


void initial_list(list_t* ptr_list){
    ptr_list->head = NULL;
}


void delnodes(list_t* ptr_list){
    if(ptr_list->head == NULL){
        printf("The list is empty\n");
    }
    else{
        node_t* present;
        node_t* previous;
        present = ptr_list->head;
        previous = NULL;
        while(present != NULL){
            if(previous == NULL){          
                ptr_list->head = present->link;
            }
            else{
                previous->link = present->link;
            }
            previous = present;
            present = present->link;
        }
    }
}


void insert(list_t* ptr_list, int data){
    node_t* temp = (node_t*)malloc(sizeof(node_t));
    temp->key = data;
    temp->link = NULL;
    if(ptr_list->head == NULL){
        ptr_list->head = temp;
    }
    else{
        node_t *p=ptr_list->head;
        while(p->link)
        {
            p=p->link;
        }
        p->link=temp;
    }
}


void main(){
    list_t l;
    initial_list(&l);
    int choice, ele;
    while(1){
        printf("1. Insert head\n");
        printf("2. Delete alternate nodes\n3. Display\n4. Exit");
        scanf("%d",&choice);
        switch(choice){
            case 1:
                printf("Enter the element: ");
                scanf("%d",&ele);
                printf("\n\n");
                insert(&l,ele);
                break;
            case 2:
                delnodes(&l);
                display(&l);
                break;
            case 3:
                display(&l);
                break;
            default:
            exit(0);
        }
    }
}