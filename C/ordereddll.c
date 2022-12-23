#include<stdio.h>
#include<stdlib.h>
struct node{
    int data;
    struct node *prev;
    struct node *next;
};      

struct node* head = NULL;
struct node* tail = NULL;

void insert(int data) {
    struct node *ptr = (struct node*)malloc(sizeof(struct node));
    ptr->data = data;
        
    if(head == NULL) {
        head = tail = ptr;
        head->prev = NULL;
        tail->next = NULL;
    }
    else {
        tail->next = ptr;
        ptr->prev = tail;
        tail = ptr;
        tail->next = NULL;
    }
}

void sort() {
    struct node *cur = NULL, *in = NULL;
    int temp;
    if(head == NULL) {
        return;
    }
    else {
        for(cur = head; cur->next != NULL; cur= cur->next) {
            for(in = cur->next; in != NULL; in= in->next) {
                if(cur->data > in->data) {
                    temp = cur->data;
                cur->data = in->data;
                in->data = temp;
            }
            }
        }
    }
}

void display() {
    struct node *cur = head;
    if(head == NULL) {
        printf("List is empty\n");
        return;
    }
    while(cur!= NULL) {
        printf("%d ",cur->data);
        cur = cur->next;
    }
    printf("\n");
}

void search()  
{  
    struct node *ptr;  
    int item,i=0,flag;  
    ptr = head;   
    if(ptr == NULL)  
    {  
        printf("\nList is Empty\n");  
    }  
    else  
    {   
        printf("\nEnter Search Element:\n");   
        scanf("%d",&item);  
        while (ptr!=NULL)  
        {  
            if(ptr->data == item)  
            {  
                printf("\nFound at:%d ",i+1);  
                flag=0;  
                break;  
            }   
            else  
            {  
                flag=1;  
            }  
            i++;  
            ptr = ptr -> next;  
        }  
        if(flag==1)  
        {  
            printf("\nNo such Items\n");  
        }  
    }     
          
} 

int main()  
{
    insert(-6);
    insert(-9);
    insert(420);
    insert(0);
    insert(69);
    insert(1000);
    insert(9);
    insert(32);
    
   
    printf("Before Sorting:");
    display();

    sort();

    printf("After sorting:");
    display();

    search();
   
    return 0;
}  