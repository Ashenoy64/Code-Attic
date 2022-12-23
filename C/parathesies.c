#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct stack{
int top;
int size;
char *item;
}stack;


char pop(stack *p)
{
    if(p->top==-1)
    printf("Empty!!\n");
    else
    {
        char a=p->item[p->top];
        p->top--;
        return a;
    }
}

void push(stack *p,char dat)
{
    if(p->top==p->size-1)
    {
        printf("Overfolw!!");
    }
    else{
        p->top++;
        p->item[p->top]=dat;
    }
}

int main()
{
    char s[100];
    printf("Enter the string:");
    scanf("%s",s);
    stack stk={-1};
    stk.size=strlen(s);
    stk.item=(char*)malloc(sizeof(char)*stk.size);
    int flag=1,ind=0;
    while(flag==1 && s[ind]!='\0')
    {
        char ch=s[ind];
        ind++;
        switch(ch)
        {
            case '(':
            case '{':
            case '[':
            push(&stk,ch);
            break;
            case ')':
            if(pop(&stk)!='(')
            {
                flag=0;
            }
            break;
            case']':
            if(pop(&stk)!='(')
            {
                flag=0;
            }
            break;
            case '}':
            if(pop(&stk)!='{')
            {
                flag=0;
            }
            break;
        }
    }
    if(flag && stk.top==-1)
    {
        printf("valid\n");
    }
    else{
        printf("Invalid\n");
    }

    return 0;
}