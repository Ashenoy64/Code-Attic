#include<stdio.h>
#include<stdlib.h>



typedef struct node{
    int data;
    struct node* left,*right;
}node;

typedef struct tree{
    node *head;
}tree;

void init(tree *t){
    t->head=NULL;
}

void insert(tree *t,int data)
{
    node *p=(node*)malloc(sizeof(node));
    p->data=data;
    p->left=NULL;
    p->right=NULL;
    if(t->head==NULL)
    {
       t->head=p;
    }

    else{
        node *ptr=t->head;
        node *prev;
        while(ptr){
            prev=ptr;
            if(ptr->data>data) ptr=ptr->left;
            else ptr=ptr->right;
        }
        if(prev->data>data) prev->left=p;
        else prev->right=p;
    }
}

void inorder(node *p)
{
    if(p==NULL) return;
    inorder(p->left);
    printf("%d ",p->data);
    inorder(p->right);
}


node* delete(node *p,int data)
{   
    if(p==NULL) return NULL;
    if(p->data>data)
        p->left=delete(p->left,data);
    else if(p->data<data)
        p->right=delete(p->right,data);
    else{
        if(p->right==NULL)
        {
            node *temp=p->left;
            free(p);
            return  temp;
        }
        if(p->right==NULL)
        {
            node *temp=p->left;
            free(p);
            return  temp;
        }
        else if(p->left==NULL)
        {
            node *temp=p->right;
            free(p);
            return  temp;
        }
        else{
            node *temp=p->right;
            //printf("%d \n",temp->data);
            while(temp->left)
            {
                temp=temp->left;
            }
            //printf("%d \n",temp->data);
            p->data=temp->data;
            delete(p->right,temp->data);
        }
    }
    return p;
}


void iterativePreorder(node* root)
{
    if (root == NULL)
        return;
    stack<node*> nodeStack;
    nodeStack.push(root);
    while (nodeStack.empty() == false) {
        struct node* node = nodeStack.top();
        printf("%d ", node->data);
        nodeStack.pop();
        if (node->right)
            nodeStack.push(node->right);
        if (node->left)
            nodeStack.push(node->left);
    }
}
 
void inOrder(struct tNode *root)
{
  struct tNode *current = root;
  struct sNode *s = NULL; 
  bool done = 0;
  while (!done)
  {
    if(current !=  NULL)
    {
      push(&s, current);                                              
      current = current->left; 
    }
    else                                                             
    {
      if (!isEmpty(s))
      {
        current = pop(&s);
        printf("%d ", current->data);
        current = current->right;
      }
      else
        done = 1;
    }
  }
}    
 
void postOrderIterative(struct Node* root)
{
    if (root == NULL)
        return;
    struct Stack* s1 = createStack(MAX_SIZE);
    struct Stack* s2 = createStack(MAX_SIZE);
    push(s1, root);
    struct Node* node;
    while (!isEmpty(s1)) {
        node = pop(s1);
        push(s2, node);
        if (node->left)
            push(s1, node->left);
        if (node->right)
            push(s1, node->right);
    }
    while (!isEmpty(s2)) {
        node = pop(s2);
        printf("%d ", node->data);
    }
}


int main()
{
    tree t;
    init(&t);
    insert(&t,10);
    insert(&t,1);
    insert(&t,2);
    insert(&t,19);
    insert(&t,11);
    insert(&t,5);
    insert(&t,16);
    insert(&t,20);
    delete(t.head,19);
    delete(t.head,10);
    inorder(t.head);
    return 0;
}