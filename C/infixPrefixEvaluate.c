#include<stdio.h>
#include<stdlib.h>


#define SIZE 100

typedef struct stack{
	int top;
	char items[SIZE];
}stack;

int power(int a,int b)
{
    int sum=1;
    while(b--)
    {
        sum*=a;
    }
    return sum;
}
void push(stack *p,char a)
{
	if(p->top==SIZE-1)
	{
		printf("Stack is FULL\n");
	}
	else
	{
		p->top++;
		p->items[p->top]=a;
	}
	
}

char pop(stack *p)
{
	if(p->top==-1)
	{
		printf("Stack is Empty\n");
	}
	else
	{
		char ch=p->items[p->top];
		(p->top)--;
        return ch;
	}
	
}

void display(stack *p)
{
	for(int i=0;i<=p->top;i++)
	{
		printf("%c ",p->items[i]);
    }
	printf("\n");
}
int isEmpty(stack *p)
{
	return p->top==-1?0:1;
}

int check(char a,char b)
{
    char prio[]={'^','*','/','+','-'};
    int A,B;
    for(int i=0;i<5;i++)
    {
        if(a==prio[i])
        A=i;
        if(b==prio[i])
        B=i;
    }

    if(A>=B)
    {
        return 0;
    }
    else{
        return 1;
    }
}

void convert(char *s,stack *eq)
{
    stack symb={-1};
    int i=0;
    while(s[i])
    {
        if(s[i]<='9' && s[i]>='0')
        {
            push(eq,s[i]);
        }
        else
        {
            if(symb.top==-1)
            {
                push(&symb,s[i]);
            }
            else if(s[i]=='(')
            {
                push(&symb,'(');
            }
            else if(s[i]==')')
            {
                char ch=pop(&symb);
                while(ch!='(')
                {
                    push(eq,ch);
                    ch=pop(&symb);
                }
            }
            else{
                back:if(check(s[i],symb.items[symb.top]) || symb.top==-1)
                {
                    push(&symb,s[i]);
                }
                else{
                    char ch=pop(&symb);
                    push(eq,ch);
                    goto back;
                }
            }
        }
        i++;
    }
    while(symb.top!=-1)
    {
        push(eq,pop(&symb));
    }
}
void prefix(stack *s,stack *p)
{
    p->top=0;
    int i=s->top;
    while(i!=-1)
    {
        p->items[p->top]=s->items[i];
        i--;
        p->top++;
    }
}
int evaluate(stack *s)
{
    stack val={-1};
    int ind=s->top;
    while(ind!=-1)
    {
        if(s->items[ind]>='0' && s->items[ind]<='9')
        {
            push(&val,pop(s));
        }
        else{
            char symb=pop(s);
            int a=pop(&val)-'0',b=pop(&val)-'0',c;
            switch(symb)
            {
                case '^':
                c=power(b,a);

                break;
                case '*':
                c=b*a;
                break;
                case '/':
                c=b/a;
                break;
                case '+':
                c=b+a;
                break;
                case '-':
                c=b-a;
                break;
            }
            push(&val,c+'0');
        }

        ind--;
    }
    return  pop(&val)-'0';
}
int main()
{
    char eq[100];
    stack s={-1};
    printf("Enter the Equation:");
    scanf("%s",eq);
    convert(eq,&s);
    printf("Postfix Expression: ");
    display(&s);
    stack pre={-1};
    prefix(&s,&pre);
    pre.top=s.top;
    int n=evaluate(&pre);
    pre.top=s.top;
    printf("Prefix Expression: ");
    display(&pre);

    printf("Ans=%d\n",n);


}