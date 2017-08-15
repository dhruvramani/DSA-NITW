#include <iostream>
using namespace std;

struct lnode 
{
    int data;
    lnode *next;
};
typedef lnode *lptr;

lptr add(lptr l, int k)
{

    if(l == NULL)
    {
        l = new lnode;
        l->data = k;
        l->next = NULL;
    } else {
        lptr t = l;
        while(t->next != NULL)
            t = t->next;
        t->next = new lnode;
        t->next->next = NULL;
        t->next->data = k;
        t = t->next;
    }
    return l;
}

lptr middle(lptr l)
{
    lptr t = l; 
    while(t->next->next != NULL)
    {
        l = l->next;
        t = t->next->next;
    }
    return l;
}

int main()
{
    lptr l1 = NULL;
    int n;
    cout<<"Enter No. of Elements for L1 : ";
    cin>>n;
    if(n%2 == 1)
    {
        cout<<"Add Even Number of Elements";
        return 1;
    }
    for(; n>0; n--)
    {
        int k;
        cout<<"Enter Value : ";
        cin>>k;
        l1 = add(l1, k);
    }
    l1 = middle(l1);
    cout<<"Middle Node : "<<l1->data;
    return 0;
}