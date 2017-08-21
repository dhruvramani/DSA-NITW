#include <iostream>
using namespace std;

struct lnode 
{
    int data;
    lnode *next;
};
typedef lnode *lptr;

void print(lptr l)
{
    while(l != NULL)
    {
        cout<<l->data<<" ";
        l = l->next;
    }
}

lptr l3, l4;
lptr create(lptr l, int type)
{
    lptr l1 = l;
    if(type == 1)
    {
        l1->data = 5;
        l1->next = new lnode;
        l1 = l1->next;
        l1->data = 8;
        l3 = new lnode;
        l4 = new lnode;
    } else {
        l1->data = 3;
        l1->next = new lnode;
        l1 = l1->next;
        l1->data = 6;
        l1->next = new lnode;
        l1 = l1->next;
        l1->data = 1;
    }
    l1->next = l3;
    l1 = l1->next;
    l1->data = 4;
    l1->next = new lnode;
    l1 = l1->next;
    l1->data = 9;
    l1->next = NULL;
    return l;

}

int main()
{
    lptr l1 = NULL, l2 = NULL;
    l1 = new lnode;
    l2 = new lnode;
    create(l1, 1);
    create(l2, 2);
    print(l1);
    cout<<endl;
    print(l2);
    return 0;
}