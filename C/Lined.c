#include <stdio.h>
#include <stdlib.h>

typedef struct data
{
    int co;
    int pow_x;
    int pow_y;
} data;

typedef struct node
{
    data d;
    struct node *l;
} node;

typedef struct HEAD
{
    node *head;
} HEAD;

void init(HEAD *p)
{
    p->head = NULL;
}
data get_info()
{
    struct data d;
    printf("\nPower of X: ");
    scanf("%d", &d.pow_x);
    printf("\nPower of Y: ");
    scanf("%d", &d.pow_y);
    printf("\nCoefficient: ");
    scanf("%d", &d.co);

    return d;
}

void append(HEAD *p, data dat)
{
    node *t = (node *)malloc(sizeof(node));
    t->l = NULL;
    t->d = dat;

    node *s = p->head;

    if (p->head == NULL)
    {
        p->head = t;
    }
    else
    {
        node *prev = NULL;
        while (s != NULL)
        {
            prev = s;
            s = s->l;
        }
        prev->l = t;
    }
}

void create(HEAD *h)
{
    init(h);
    data dat;
    int n, wish, pos;
    while (1)
    {
        printf("(1) Append \n(2) Exit\n:");
        scanf("%d", &wish);
        switch (wish)
        {
        case 1:
            dat = get_info();
            append(h, dat);
            break;
        case 2:
        default:
            n = 5;
        }
        if (wish == 5)
        {
            break;
        }
    }
}

void create_add(HEAD *p, node *n)
{
    node *pres = p->head;
    while (pres->l != NULL)
    {
        pres = pres->l;
    }
    node *t = (node *)malloc(sizeof(node));
    t->d = n->d;
    t->l = NULL;
    pres->l = t;
}
void add(HEAD *l1, HEAD *l2)
{
    node *p1 = l1->head;
    node *p2 = l2->head;
    int flag = 0;
    p2 = l2->head;
    while (p2)
    {
        while (p1)
        {
            if (p1->d.pow_x == p2->d.pow_x && p1->d.pow_y == p2->d.pow_y)
            {
                p1->d.co += p2->d.co;

                flag = 1;
                break;
            }
            else
            {
                p1 = p1->l;
            }
        }
        if (flag == 0)
        {
            create_add(l1, p2);
        }
        flag = 0;
        p2 = p2->l;
        p1 = l1->head;
    }
}
void display_equation(HEAD *p)
{
    node *s = p->head;
    while (s)
    {
        printf("%dX^%dY^%d+", s->d.co, s->d.pow_x, s->d.pow_y);
        s = s->l;
    }
    printf("\n");
}
int main()
{
    HEAD h1;
    create(&h1);
    HEAD h2;
    create(&h2);

    add(&h1, &h2);
    display_equation(&h1);
}