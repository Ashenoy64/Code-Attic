#include<string.h> 
#include<limits.h>
#include<stdio.h>
#include<stdlib.h>
# define MAX 100
 
struct Stack { 
    int top; 
    int maxSize;
    int* array; 
}; 
 
struct Stack* create(int max) 
{ 
    struct Stack* stack = (struct Stack*)malloc(sizeof(struct Stack)); 
    stack->maxSize = max; 
    stack->top = -1; 
    stack->array = (int*)malloc(stack->maxSize * sizeof(int));
    return stack; 
} 
 
int isFull(struct Stack* stack) 
{ 
    if(stack->top == stack->maxSize - 1){
        printf("Will not be able to push maxSize reached\n");
    }
    return stack->top == stack->maxSize - 1; 
} 
 
int isEmpty(struct Stack* stack) 
{ 
    return stack->top == -1; 
}
 
void push(struct Stack* stack, char item) 
{ 
    if (isFull(stack)) 
        return; 
    stack->array[++stack->top] = item; 
}
 
int pop(struct Stack* stack) 
{ 
    if (isEmpty(stack)) 
        return INT_MIN; 
    return stack->array[stack->top--]; 
} 
 
int peek(struct Stack* stack) 
{ 
    if (isEmpty(stack)) 
        return INT_MIN; 
    return stack->array[stack->top]; 
} 
 
int checkIfOperand(char ch) 
{ 
    return (ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z')||(ch>='0'&&ch<='9'); 
} 
 
int precedence(char ch) 
{ 
    switch (ch) 
    { 
    case '+': 
    case '-': 
        return 1; 
 
    case '*': 
    case '/': 
        return 2; 
 
    case '^': 
        return 3; 
    } 
    return -1; 
} 
 
int getPostfix(char* expression) 
{ 
    int i, j; 
 
    
    struct Stack* stack = create(strlen(expression)); 
    if(!stack) 
        return -1 ; 
 
    for (i = 0, j = -1; expression[i]; ++i) 
    {  
        if (checkIfOperand(expression[i])) 
            expression[++j] = expression[i]; 
 
        else if (expression[i] == '(') 
            push(stack, expression[i]); 
 
         
        else if (expression[i] == ')') 
        { 
            while (!isEmpty(stack) && peek(stack) != '(') 
                expression[++j] = pop(stack); 
            if (!isEmpty(stack) && peek(stack) != '(') 
                return -1;             
            else
                pop(stack); 
        } 
        else 
        { 
            while (!isEmpty(stack) && precedence(expression[i]) <= precedence(peek(stack))) 
                expression[++j] = pop(stack); 
            push(stack, expression[i]); 
        } 
 
    } 
 
    while (!isEmpty(stack)) 
        expression[++j] = pop(stack); 
 
    expression[++j] = '\0'; 
    
}
 
void reverse(char *exp){
 
    int size = strlen(exp);
    int j = size, i=0;
    char temp[size];
 
    temp[j--]='\0';
    while(exp[i]!='\0')
    {
        temp[j] = exp[i];
        j--;
        i++;
    }
    strcpy(exp,temp);
}
void brackets(char* exp){
    int i = 0;
    while(exp[i]!='\0')
    {
        if(exp[i]=='(')
            exp[i]=')';
        else if(exp[i]==')')
            exp[i]='(';
        i++;
    }
}
void InfixtoPrefix(char *exp){
 
    int size = strlen(exp);
    reverse(exp);
    brackets(exp);
    getPostfix(exp);
    printf("The Postfix expression:");
    printf("%s\n",exp);
    reverse(exp);
}
 
int main()
{    
    printf("Enter infix expression: ");
    char expression[20];
    scanf("%s",expression);
    
    InfixtoPrefix(expression); 
    printf("The prefix expression: ");
    printf("%s\n",expression);
 
    return 0; 
}
