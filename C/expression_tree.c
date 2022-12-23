#include<stdio.h>
#include<stdlib.h>

typedef struct node{
    struct node *left,*right;
    char ch;
}node;

typedef struct tree{
    node *head;
}tree;


void convert(tree *t,char *s)
{   
    node* buff[100];
    int ind=-1;
    for(int i=0;s[i];i++)
    {
        if(s[i]>='0' && s[i]<='9')
            { 
                buff[++ind]=(node *)malloc(sizeof(node));
                buff[ind]->left=NULL;
                buff[ind]->right=NULL;
                buff[ind]->ch=s[i];

           }
        else{
            node* ch1=buff[ind--];
            node* ch2=buff[ind--];
            buff[++ind]=(node *)malloc(sizeof(node));
            buff[ind]->ch=s[i];
            buff[ind]->left=ch1;
            buff[ind]->right=ch2;

        }
    }
    t->head=buff[ind];
}

void inorder(node *head)
{
    if(head==NULL) return;
    printf("%d ",head->ch);
    inorder(head->left);
    inorder(head->right);
}

int evaluate(node *head){
    if(head==0) return 0;
    switch(head->ch)
    {
        case '+':   return evaluate(head->left) + evaluate(head->right);
        case '-':   return evaluate(head->left) - evaluate(head->right);
        case '/':   return evaluate(head->left) / evaluate(head->right);
        case '*':   return evaluate(head->left) * evaluate(head->right);
        case '^':   return evaluate(head->left) ^ evaluate(head->right);
        default:
            return head->ch-'0';
    }
}


int main()
{
    tree t;
    t.head=NULL;
    char s[100]={'2','3','*'};
    convert(&t,s);
    inorder(t.head);
    printf("\n%d",evaluate(t.head));
}