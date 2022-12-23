#include<stdio.h>
#include<stdlib.h>
#define SIZE 100

int queue[SIZE];
int rear=-1;
int front=-1;

void enq(int a)
{
    if(rear==-1 && front==-1)
    {
        front++;
        queue[++front]=a;
    }
    else if(rear==SIZE-1 && front>=1)
    {
        queue[0]=a;
        rear=0;
    }
    else if(rear+1==front || (rear==SIZE-1 && front==0))
    {
        printf("Queue is Full\n");
    }
    else{
        queue[++rear]=a;
    }
}

int deq()
{
    if(front==-1)
    {
        printf("Empty!!!\n");
    }
    else if(front==rear)
    {
        int ch=queue[front];
        front=-1;
        rear=-1;
        return ch;
    }
    else if(front==SIZE-1)
    {
        int ch=queue[front];
        front=0;
    }
    else{
        return queue[front++];
    }
}

void display()
{
    int i;
    if(front==-1)
    {
        printf("Empty!!!\n");
    }
    else{
        for( i=front;i!=rear;i++)
        {
            if(front==SIZE)
            {
                i=0;
            }
            printf("%d ",queue[i]);
        }
        printf("%d ",queue[i]);
    }
}

int main()
{
    
}