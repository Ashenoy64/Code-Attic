#include<stdio.h>
#include<stdlib.h>

typedef struct node{
    int data;
    struct node* link;
}node;

typedef struct HEAD{
    node *head;
}HEAD;

void init(HEAD *p)
{
    p->head = NULL;
}

void display(const HEAD *p)
{
    node *t = p->head;
    
    int n=0;
    if(t)
    {
        while(t)
        {
            printf("%d ",t->data);
            t=t->link;
        }
        printf("\n");
    }
    else{
        printf("\n Empty");
    }
}

void append(HEAD *p,int dat)
{
    node *t = (node *)malloc(sizeof(node));
    t->link= NULL;
    t->data =dat;

    node *s = p->head;

    if (p->head == NULL)
    {
        p->head = t;
    }
    else
    {
        while(s->link)
        {
            s=s->link;
        }
        s->link=t;
    }
}

void sort(HEAD *h) 
{
node *head=h->head;
struct node *cur = NULL, *in = NULL;
int temp;
if(head == NULL)
{        
    return;    
}    
else {
    for(cur = head; cur->link != NULL; cur= cur->link) {
            for(in = cur->link; in != NULL; in= in->link) {
            if(cur->data > in->data) {
            temp = cur->data;
            cur->data = in->data;
            in->data = temp;
            }
            }
        }
    }
}

void merge_creating_new(HEAD *h,HEAD *h1,HEAD *h2)
{
    node *t=h->head;
    node *link=h1->head;
    if(t==NULL)
    {
        node *temp=(node*)malloc(sizeof(node));
        temp->data=link->data;
        temp->link=NULL;
        link=link->link;
        h->head=temp;
        t=temp;
    }
    while(link)
    {
        node *temp=(node*)malloc(sizeof(node));
        temp->data=link->data;
        temp->link=NULL;
        t->link=temp;
        link=link->link;
        t=temp;
    }
    link=h2->head;
    while(link)
    {
        node *temp=(node*)malloc(sizeof(node));
        temp->data=link->data;
        temp->link=NULL;
        t->link=temp;
        link=link->link;
        t=temp;
    }
    sort(h);
}

void create(HEAD *h)
{
    int wish;
    do{
        printf("1. ADD\n2. Display\n3. Done\n:");
        scanf("%d",&wish);
        if(wish==1)
        {
            int n;
            printf("Enter the data:");
            scanf("%d",&n);
            printf("\n");
            append(h,n);
        }
        else if(wish==2)
        {
            printf("\nCurrent List: ");
            display(h);
            printf("\n");
        }
        else{
            printf("--------------------------------------------\n");
            return;
        }

    }while(wish==1||wish==2);
} 

int main()
{
    HEAD h1={NULL};
    HEAD h2={NULL};
    HEAD fin={NULL};
    printf("First List:\n");
    create(&h1);
    printf("Second List:\n");
    create(&h2);
    merge_creating_new(&fin,&h1,&h2);
    sort(&h1);
    sort(&h2);

    printf("Linked List One After Sorting:");
    display(&h1);
    
    printf("Linked List two After Sorting:");
    display(&h2);
    printf("\n");

    printf("Linked List Resulted from merging List one and List two:\n");
    display(&fin);

}