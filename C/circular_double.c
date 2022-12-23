#include<stdio.h>
#include<stdlib.h>

typedef struct node{
    int data;
    struct node* next;
    struct node* prev;
}node;

node* createNode(int data)
{
    node *ptr=(node*)malloc(sizeof(node));
    ptr->next=NULL;
    ptr->prev=NULL;
    ptr->data=data;
    return ptr;
}

node* insert(node *head,int data,int pos)//0 begin -1 end 
{
    node *ptr=createNode(data);
    //printf("%d",ptr->data);
    if(head==NULL)
    {
        //printf("%d 1",ptr->data);
        ptr->next=ptr;
        ptr->prev=ptr;
        head=ptr;
        return head;
    }
    if(pos==0)
    {
        ptr->next=head;
        ptr->prev=head->prev;
        head->prev->next=ptr;
        head->prev=ptr;
        head=ptr;
    }
    else if(pos==-1)
    {
        ptr->next=head;
        ptr->prev=head->prev;
        head->prev->next=ptr;
        head->prev=ptr;
    }
    else{
        node *p=head;
        node *q=NULL;
        int count=0;
        while(p!=NULL && count!=pos)
        {
            q=p;
            p=p->next;
            count++;
        }
        if(p==NULL)
        {
            printf("Position does not exist!!");
            return head;
        }
        ptr->next=p;
        ptr->prev=p->prev;
        p->prev->next=ptr;
        p->prev=ptr;
    }
    return head;
}

node* delete(node *head,int data)
{
    if(head==head->next)
    {
        free(head);
        //head=NULL;
        //printf("1\n");
        return NULL;
    }
    node *p=head;
    
    do{
        p=p->next;
    }while(p!=head && p->data!=data);
    printf("%d *\n",p->data);
    p->prev->next=p->next;
    p->next->prev=p->prev;
    if(head==p)
    {
        head=p->next;
        free(p);
        return head;
    }
    free(p);
    return head;
}


void display(node *head)
{
    if(head==NULL) return printf(" Empty");
    node *p=head;
    int count=0;
    //printf("%d",p->data);
    do{
        printf("%d ",p->data);
        p=p->next;
        count++;
        if(count>=10){
            break;
        }
    }while(p!=head);
}

int main()
{
    node *head=NULL;
    head=insert(head,100,1);
    head=insert(head,200,0);
    head=insert(head,300,2);
    head=insert(head,400,3);
    //head=insert(head,200,10);
    //printf("%d",head->data);
    head=delete(head,200);
    head=delete(head,100);
    head=delete(head,300);
    head=delete(head,400);
    display(head);
}