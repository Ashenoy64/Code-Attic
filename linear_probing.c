#include<stdio.h>
#include<stdlib.h>
#define SIZE 100

typedef struct node{
    int key;
    char name[30];
}node;


void init(node *arr[SIZE]){
    for(int i=0;i<SIZE;i++){
        arr[i]=NULL;
    }
}

void insert(node *arr[SIZE],int n)
{
    node *ptr=(node*)malloc(sizeof(node));
    printf("Enter the key\n");
    scanf("%d",&ptr->key);
    printf("Enter the name:\n");
    scanf("%s",ptr->name);;


    int key=ptr->key;
    while(arr[key%n]!=NULL)
    {
        key++;
    }
    arr[key%n]=ptr;
}

void display(node *arr[SIZE],int n)
{
    for(int i=0;i<n;i++)
    {
        if(arr[i]==NULL)
        continue;
        printf("NAME:%s\n",arr[i]->name);
        printf("KEY:%d\n\n\n",arr[i]->key);
    }
}

void search(node *arr[SIZE],int n){
    int key;
    printf("Enter the key:\n");
    scanf("%d",&key);
    for(int i=0;i<n;i++)
    {
        if(arr[i]==NULL)
        continue;
        else if(arr[i]->key==key)
        {
            printf("Found!!\n");
            printf("NAME:%s\n",arr[i]->name);
            printf("KEY:%d\n\n\n",arr[i]->key);
            return;
        }
    }
    printf("Not Found!!\n");
}

void delete(node *arr[SIZE],int n)
{
    int key;
    printf("Enter the key:\n");
    scanf("%d",&key);
    for(int i=0;i<n;i++)
    {
        if(arr[i]==NULL)
        continue;
        else if(arr[i]->key==key)
        {
            printf("Entered");
            free(arr[i]);
            printf("Entered");
            arr[i]=NULL;
            printf("Entered");
            return;
        }
    }
    printf("Not Found!!\n");
}

int main(){
    node *arr[SIZE];
    init(arr);
    int n;
    printf("Enter the Number of Keys:\n");
    scanf("%d",&n);
    if(n>SIZE){
        printf("Size exceeds the size\n");
        exit(0);
    }
    int wish;
    do{
        printf("\n\nEnter your wish\n1-Insert\n2-Display\n3-Search\n4-Delete\n5-exit\n:");
        scanf("%d",&wish);
        switch(wish)
        {
            case 1:
            insert(arr,n);
            break;
            case 2:
            display(arr,n);
            break;
            case 3:
            search(arr,n);
            break;
            case 4:
            delete(arr,n);
            break;
            default:
            exit(0);
        }
    }while(wish<6);
    return 0;
}