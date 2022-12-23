#include<stdio.h>
#include<stdlib.h>

typedef struct stack{  
int *queue;
int front;
int rear;
int size;
}queue;

void init(queue *s)
{
    s->front=-1;
    s->rear=-1;
    s->queue=(int *)calloc(sizeof(int),5);
    s->size=5;
}

void enqueue(queue *s,int data)
{
    if((s->rear==s->size-1 && s->front==0)||(s->rear+1==s->front))
    {
        printf("full\n");
        return;
    }
    if(s->rear==-1)
    {
        s->front=0;
    }
    s->rear=(s->rear+1)%(s->size);
    s->queue[s->rear]=data;
    //printf("Done");
}

int dequeue(queue *s)
{
    if(s->front==-1)
    {
        printf("Empty!!\n");
    }
    int data=s->queue[s->front];
    s->queue[s->front]=-99;
    if(s->front==s->rear)
    {
        s->rear=-1;
        s->front=-1;
        return data;
    }
    s->front=(s->front+1)%5;
    return data;
}

void display(queue *s)
{
    for(int i=0;i<5;i++)
    {
        printf("%d ",s->queue[i]);
    }
}

int main()
{
    queue s;
    init(&s);
    //printf("%d ",s.rear);
    enqueue(&s,1);
    enqueue(&s,2);
    enqueue(&s,3);
    enqueue(&s,4);
    enqueue(&s,5);
    dequeue(&s);
    dequeue(&s);dequeue(&s);dequeue(&s);dequeue(&s);dequeue(&s);
    // enqueue(&s,7);
    // enqueue(&s,78);
    // enqueue(&s,78);
    //enqueue(&s,2);
    //dequeue(&s);
    display(&s);
}