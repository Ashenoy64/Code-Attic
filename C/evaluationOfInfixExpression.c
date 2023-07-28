#include<stdio.h>
#include<stdlib.h>

typedef struct stack{
    char arr[20];
    int top;
}stack;
stack st;

int precedence(char a)
{
    switch(a)
    {
        case '+':
        case '-':
            return 0;
        case '/':
        case '*':
            return 1;
    }
}

void convert(char *s)
{
    char buff[100]={'\0'};
    int b=0,what;
    char ch;
    for(int i=0;s[i]!='\0';i++)
    {
        if(s[i]>='0' && s[i]<='9')
        {
            buff[b++]=s[i];
            printf("%c operand\n",s[i]);
            continue;
        }
        if(s[i]==')' || s[i]=='(' || s[i]=='^' || st.top==-1 ||st.arr[st.top]=='(')
        {
            if(s[i]=='(' || s[i]=='^' || st.arr[st.top]=='(' || st.top==-1)
            {
                st.arr[++st.top]=s[i];
                printf("%c all\n",s[i]);
            }      
            else{
                while(st.arr[st.top]!='(')
                {
                    buff[b++]=st.arr[st.top--];
                }
                st.top--;
            }
            continue;
        }
        else{
            what =precedence(s[i])-precedence(st.arr[st.top]);
           if(what>0)
           {
                st.arr[++st.top]=s[i];
                printf("%c what\n",s[i]);
           }
           else if(what<0)
           {
                while(what<0)
                {
                    buff[b++]=st.arr[st.top--];
                    if(st.top==-1)
                    break;
                    what =precedence(s[i])-precedence(st.arr[st.top]);
                }
                st.arr[++st.top]=s[i];
           }
           else{
            buff[b++]=st.arr[st.top];
            st.arr[st.top]=s[i];
           }
        }
    }
    while(st.top!=-1)
    {
        buff[b++]=st.arr[st.top--];
    }
    printf("%s", buff);
}

int main()
{
    st.top=-1;
    char ctr[100]={'1','*','3','-','2','+','1','^','1'};
    convert(ctr);
    return 0;
}