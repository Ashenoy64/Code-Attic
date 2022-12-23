#include<stdio.h>
#include<stdlib.h>

typedef struct tree{
    int *arr;
    int size;
}tree;


void init(tree *t)
{
    //printf("Enter number of nodes\n");
    //scanf("%d",t->size);
    t->size=10;
    t->arr=(int*)calloc(t->size,sizeof(int));
    return;
}

void insert(tree *t,int data)
{
    if(t->arr[0]==0)
    {
        t->arr[0]=data;
    }
    else{
        int pos=0;
        while(t->arr[pos]!=0)
        {
            if(t->arr[pos]>data) pos=2*pos+1;
            else pos=2*pos+2;
        }
        t->arr[pos]=data;
    }
}

void display(tree t)
{
    for(int i=0;i<t.size;i++)
    {
        printf("%d ",t.arr[i]);
    }
    printf("\n");
}

void traverse(tree t,int i)
{
    if(t.arr[i]==0 || i>=t.size) return;
    
    traverse(t,2*i+1);

   
    traverse(t,2*i+2);

    printf("%d ",t.arr[i]);

}

int main()
{
    tree t;
    init(&t);
    insert(&t,5);
    insert(&t,6);
    insert(&t,1);
    insert(&t,7);
    traverse(t,0);
    return 0;
}