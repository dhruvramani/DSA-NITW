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

lptr merge(lptr l1, lptr l2, lptr r)
{
    lptr l3 = r;
    while(l1 != NULL && l2 != NULL)
        if(l1->data >= l2->data)
        {
            l3 = add(l3, l1->data);
            l1 = l1->next;
            l3 = l3->next;
        } else {
            l3 = add(l3, l2->data);
            l2 = l2->next;
            l3 = l3->next;
        }

    while(l1 != NULL) 
    {
            l3 = add(l3, l1->data);
            l1 = l1->next;
            l3 = l3->next;
    } 

    while(l2 != NULL) 
    {
            l3 = add(l3, l2->data);
            l2 = l2->next;
            l3 = l3->next;
    } 

    return r;       
}

void print(lptr l)
{
    while(l != NULL)
    {
        cout<<l->data<<" -> ";
        l = l->next;
    }
    cout<<"NULL\n";
}

int main()
{
    lptr l1 = NULL, l2 = NULL, l3;
    int n;
    cout<<"Enter No. of Elements for L1 : ";
    cin>>n;
    for(; n>0; n--)
    {
        int k;
        cout<<"Enter Value : ";
        cin>>k;
        l1 = add(l1, k);
    }
    cout<<"Enter No. of Elements for L2 : ";
    cin>>n;
    for(; n>0; n--)
    {
        int k;
        cout<<"Enter Value : ";
        cin>>k;
        l2 = add(l2, k);
    }
    l3 = merge(l1, l2, l3);
    print(l3);
    return 0;
}