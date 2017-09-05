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

lptr selection_sort(lptr h)
{
    lptr l = h;
    while(l->next != NULL)
    {
        lptr t = l->next, m;
        int min = l->data, k = l->data;
        while(t != NULL)
        {
            if(t->data < min)
            {
                min = t->data;
                m = t;
            }
            t = t->next;
        }
        l->data = min;
        m->data = k;
        l = l->next;
    }
    return h;
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
    lptr l1 = NULL;
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
    l1 = selection_sort(l1);
    print(l1);
    return 0;
}