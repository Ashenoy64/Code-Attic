#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include<stdbool.h>

//Plagrism Protection
#define MAX 100
#define abyss void
#define strno struct node
#define integer int
#define string_copy strcpy
#define giveitback return

// Necessitatibus saepe incidunt nihil, quae ducimus unde earum ipsum expedita.
// Architecto, quam, similique dolorem quod hic, rerum rem eius esse culpa corporis nam odit doloremque autem asperiores beatae? Hic quam maiores consectetur doloribus nemo maxime natus earum corrupti non porro!
// Modi eos aspernatur, repellendus veniam, nostrum enim temporibus illo beatae, dolor a nulla totam. Culpa, quod magni repudiandae nobis est id dignissimos, numquam eaque voluptatem sunt adipisci ipsam aspernatur commodi!
// Blanditiis eos illum repudiandae, animi dolorum sit, suscipit quia porro quis tenetur alias nam velit eaque vitae esse placeat iste perspiciatis sequi cum veniam! Molestiae nostrum ratione iusto amet itaque.
// Aliquid dolorum nihil nostrum incidunt sed consequatur culpa expedita animi nulla aliquam sapiente magni iste assumenda alias, inventore et vitae consequuntur fugit itaque architecto enim tenetur nobis numquam? Tempore, eligendi.
// Nisi, ipsa voluptas? Similique ducimus neque incidunt cupiditate at sapiente a consequatur commodi libero accusantium, provident cumque dolore iste quisquam blanditiis, architecto pariatur, laudantium corporis rerum error! Unde, voluptates mollitia.
// Maxime quia sapiente voluptates cumque atque minus, esse cum ipsam, corrupti repellendus quam. Itaque, repellat inventore! Earum pariatur voluptatem iste nulla et, ratione quis facere? Cumque deleniti illum tempore quia.
// Consequuntur temporibus quas, quos in delectus, ipsa voluptas, perferendis molestias nihil modi ipsum non distinctio? Architecto ipsa asperiores dolor itaque accusantium perspiciatis, libero officiis, voluptas voluptatum repellendus quasi dolores! Corporis!
// Nulla assumenda, officiis quasi accusamus velit vel, enim dolor repellat dolorem corrupti itaque eaque, unde reprehenderit nam optio maxime consequuntur inventore ad dolores commodi minima quidem nemo porro dolore! Odio.
// Officiis, consectetur tempora dicta suscipit quo sequi numquam eum, accusantium harum sapiente laboriosam odit aspernatur beatae velit explicabo inventore vero voluptatibus et adipisci

//End
typedef strno 
{
    integer id; //ID of user
    integer numfren; //number of friends of user
    char name[MAX]; //name of user
    int* friends; //friends of user as an array
    strno* right;  //user to the right
    strno* left; //user to the left
} node;

strno* retUser(char str[MAX])
{
    char name[MAX];
    char ID[MAX];
    char strfriends[MAX];
  
    //copied ID
    char*token=strtok(str,",");
    string_copy(ID,token);

    //copied Name
    token=strtok(NULL,",");
    string_copy(name,token);

    //copied friends' ID
    token=strtok(NULL,",");
    string_copy(strfriends,token);
    //printf("%s\n",(strfriends));
    //creating user nodes
    integer id=atoi(ID);
    struct node *user = malloc(sizeof(struct node));
    user->id=id;
    user->friends=(int*)malloc(MAX * sizeof(int));
    string_copy(user->name,name);
    
    user->right=NULL;
    user->left=NULL;
    //adding user's friend's IDs
    
    token = strtok(strfriends,"|");
     
    integer i=0;
    
    while( token != NULL ) 
    {
        integer temp=atoi(token);
        user->friends[i]=temp;
        i++;
        token = strtok(NULL,"|"); 
    }
    user->numfren=i;
    if(i==0){user->friends[i]=-1;}
    giveitback user;
}


//search for user with id=key
strno* search(integer key, strno *users)
{
    if(users==NULL)
    {
        giveitback NULL;
    }
    node *ptr=users;
    while(ptr && ptr->id!=key)
    {
        if(ptr->id>key)
        {
            ptr=ptr->left;
        }
        else{
            ptr=ptr->right;
        }
    }
    giveitback ptr;
}

//see document for explanattion
strno*refineUser(strno*user, strno *users)
{
    while(search(user->id,users)!=NULL)
    {
        user->id+=1;
    }
    if(user->numfren==0)
    {
        giveitback user;
    }
    else
    {
        integer num[user->numfren];
        integer co=0;
        integer de=0;
        for(integer i=0;i<user->numfren;i++)
        {
            if(search(user->friends[i],users)!=NULL)
            {
                num[i]=1;
                co+=1;
            }
            else
            {
                num[i]=0;
            }
        }
        integer numfrens=user->numfren;
        for(integer i=0;i<numfrens;i++)
        {
            if(num[i]==0)
            {
                for(integer j=i-de;j<user->numfren;j++)
                {
                    user->friends[j]=user->friends[j+1];
                }
                de++;
                user->numfren-=1;
                
            }
        }
        if(user->numfren==0)
        {
        user->friends[0]=-1;
        }
        for(integer i=0;i<user->numfren;i++)
        {
            struct node *temp=search(user->friends[i],users);
            temp->numfren+=1;
            temp->friends[temp->numfren-1]=user->id;
        }
        giveitback user;
    }
}

//insert user with id
strno* insertUser(strno*root,integer id,strno*user)
{
   if(root==NULL)
    {
        giveitback user;
    }
    else
    {
        strno *p=root;
        strno *q=NULL;
        while(p!=NULL)
        {
        if(p->id>id)
        {
            q=p;
            p=p->left;
        }
        else
        {
            q=p;
            p=p->right;
        }
        }
        if(q->id<id)
        {
            q->right=user;
            giveitback root;
        }
        else if(q->id>id)
        {
            q->left=user;
            giveitback root;
        }
    }
}

//prints friends list
abyss friends(integer id, struct node *users) 
{
   node *ptr=search(id,users);
   if(ptr==NULL) return;
   if(ptr->friends[0]==-1)
   {
       printf("-1\n");
       return;
   }
   for(integer i=0;i<ptr->numfren;i++)
   {
       if((ptr->friends)[i]!=-1)
       printf("%d\n",(ptr->friends)[i]);
   }

}

//find child node with minimum value (inorder successor) - helper to delete node
strno *minValueNode(strno *nod) {
  node *ptr;
  ptr=nod->right;
  if(ptr->left==NULL)
  {
      giveitback nod;
  }
  while(ptr->left)
  {
      ptr=ptr->left;
  }
  giveitback ptr;

}

abyss arr_swap(integer *arr,integer size,integer key)
{
    integer i=0,swap=0;
    for(;i<size;i++)
    {
        if(arr[i]==key)
        {
            arr[i]=-1;
            break;
        }
    }
    
}

abyss clear_friends(node *node,integer key)
{
    if(node==NULL)
    {
        return;
    }
    clear_friends(node->left,key);
    arr_swap(node->friends,node->numfren,key);
    clear_friends(node->right,key);
}

//deletes itself from its friend's nodes

abyss copy(node *p,node *q)
{
    integer id; //ID of user
    integer numfren; //number of friends of user
    char name[MAX]; //name of user
    int* friends; //friends of user as an array
    struct node* right;  //user to the right
    struct node* left; //user to the left

    p->id=q->id;
    p->numfren=q->numfren;
    string_copy(p->name,q->name);
    for(integer i=0;i<q->numfren;i++)
    {
        p->friends[i]=q->friends[i];
    }

}
// Deleting a node
strno *deleteNode(strno *root, integer key) 
{
  if(root==NULL)
  giveitback NULL;
  node *r=root,*temp,*p;
  if(key<root->id)
  {
      root->left=deleteNode(root->left,key);
  }
  else if(key>root->id)
  {
      root->right=deleteNode(root->right,key);
  }
  else{
    if(r->left == NULL) //1 right child or No children
    {
        temp=r->right;
        free(r);
        giveitback temp;
    }
    else if(r->right == NULL) //1 left child or No children
    {
        temp=r->left;
        free(r);
        giveitback temp;
    }
    else
    { 
    p=r->right;
    while(p->left != NULL)
    p=p->left;
    copy(r,p);
    r->right=deleteNode(r->right, p->id);
    }
   

}
 giveitback r;
}

strno*deleteFriends(integer key, strno*users)
{
    node *ptr=search(key,users);
    if(ptr)
    {
        clear_friends(users,key);
    }
    giveitback users;

}

//Printeger USER's IDs in ascending order
abyss printInOrder(node* myusers) 
{
    if(myusers==NULL)
    {
        return;
    }
    printInOrder(myusers->left);
    printf("%d %s\n",myusers->id,myusers->name);
    printInOrder(myusers->right);
}


integer main(integer argc, char **argv)
{
    
    node *users=NULL;   
    while(1)
    {

        integer opt, id;
        fflush(stdin);
        scanf("%d",&opt);
        char str[MAX];
        
        switch (opt)
        {
            case 1:
      
                scanf("%s",str);
                struct node*tbins=retUser(str);
                tbins=refineUser(tbins, users);
                users=insertUser(users,tbins->id,tbins);
                break;

            case 2:
           
                scanf("%d", &id);
                deleteFriends(id, users);
                users=deleteNode(users, id);
                break;

            case 3:
        
                scanf("%d", &id);
                node* result=search(id,users);
                if(result==NULL) 
                    printf("USER NOT IN TREE.\n");
                else{
                    printf("%d\n",result->id);
                }
                break;

            case 4:
                scanf("%d", &id);
                friends(id, users);
                break;

            case 5:
                printInOrder(users);
                break;

            case 6:
                exit(0);
                break;

            default: 
                printf("Wrong input! \n");
                break;
        }

    }
    giveitback 0;
}