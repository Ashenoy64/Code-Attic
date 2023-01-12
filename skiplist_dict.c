#include<stdio.h>
#include<stdlib.h>

typedef struct node{
    int val;
    int level;
    struct node *next;
    struct node *down;
}node;

void display(node **levels,int level)
{
    node *p=levels[level];
    while(p)
    {
        printf("[Data=%d:Level=%d]->",p->val,p->level);
        p=p->next;
    }
    printf("\n");
}
int g=0;
void search(node **levels,int n)
{   
    int level=3,found=0;
    node *p;
    while(level>=0)
    {
        if(levels[level]==NULL)
        {
            level--;
        }
        else{
            break;
        }
    }
    p=levels[level];
    while(level>=0)
    {   
        while(p->val!=n&&p->next&&p->next->val<=n)
        {
            p=p->next;
            g++;
        }
        if(p->val==n)
        {
            found=1;
            break;
        }
        else if(p->next==NULL && level>0)
        {
            p=p->down;
            level--;
        }
        else if(p->next==NULL && level==0)
        {
            break;
        }
        else
        {
            p=p->down;
            level--;
        }
    }
    if(found)
    {
        printf("Element Found %d\n",g);
    }
    else
    {
        printf("Element NOt Found\n");
    }

}

void insert(node **levels,int data,int level)
{
    node *p;
    node *prev;
    node *temp;
    node *down=NULL;
    for(int i=0;i<=level;i++)
    {
        p=levels[i];
        prev=NULL;
        temp=(node*)malloc(sizeof(node));
        temp->val=data;
        temp->level=level;
        temp->next=NULL;
        temp->down=down;
        down=temp;
        while(p&&p->val<data)
        {
            prev=p;
            p=p->next;
        }
        if(prev==NULL)
        {
            temp->next=p;
            levels[i]=temp;
        }
        else if(p==NULL)
        {
            prev->next=temp;
        }
        else{
            temp->next=p;
            prev->next=temp;
        }
    }
}

void delete(node **levels,int data)
{
    
}

void create(node **levels)
{
    int wish;
    int n,level;
    printf("Enter Your Wish\n");
    while(1)
    {
        printf("1. Insert\n2. Delete\n3. Display\n4. Search\n5. Exit\n");
        scanf("%d",&wish);
        switch(wish)
        {
            case 1:
            printf("Enter Value and Level:");
            scanf("%d %d",&n,&level);
            printf("\n");
            insert(levels,n,level);
            break;
            case 2:
            printf("Enter Value:");
            scanf("%d",&n);
            printf("\n");
            delete(levels,n);
            break;
            case 3:
            printf("Enter Level:");
            scanf("%d",&level);
            printf("\n");
            display(levels,level);
            break;
            case 4:
            printf("Enter Value:");
            scanf("%d",&n);
            printf("\n");
            search(levels,n);
            break;
            case 5:
            goto end;
        }
    }
    end:return;
}


int main()
{
    node *Levels[4]={NULL};
    create(Levels);
}