#include<stdio.h>
#include<stdio.h>
#define max_size 50

typedef enum{
    head,
    entry
}tagfield;

typedef struct
{
    int row,col,val;
}entrynode;

struct mn
{
    struct mn *down;
    struct mn *right;
    tagfield tag;
    union{
        struct mn *next;
        entrynode entry;
    }u;
}

typedef struct mn *matricepointer;

matricepointer hdnode[max_size];

matricepointer readsparce()
{
    int numrows,numcols,numterms,numheads,i,col,row,val,currentrow;
    matricepointer temp,last,node;
    printf("Enter the number of rows and columns\n");
    scanf("%d %d ",&numrows,&numcols);
    numheads=(numcols>numrows)?numcols:numrows;
    node=(matricepointer)malloc(sizeof(struct mn));
    node->tag=entry;
    node->u.entry.row=numrows;
    node->u.entry.col=numcols;
    if(numheads==0)
        node->right=node;
    else
    {
        for(i=0;i<numheads;i++)
        {
            temp=(matricepointer)malloc(sizeof(struct mn));
            hdnode[i]=temp;
            hdnode[i]->tag=head;
            hdnode[i]->
            //
            //
            //
        }
        currentrow=0;
        last=hdnode[0];
        for(i=0;i<numterms;i++)
        {

        }
    }
}
void printsparce(matricepointer node)
{
    int i;
    matricepointer temp,head;
    head=node->right;
    printf("Numrows=%d Numcols=%d\n",node->u.entry.row,node->u.entry.col);
    printf("The matrix by row col and val are\n ");
    for(i=0;i<node->u.entry.row;i++)
    {
        for(temp=head->right;temp!=head;temp=temp->right)
        printf("%5d %5d %5d\n",temp->u.entry.row,temp->u.entry.col,temp->u.entry.val);
        head=head->u.next;
        printf("\n");
    }
}
int main()
{
    matricepointer p;
    p=readsparce();
    printsparce(p);
    return 0;
}