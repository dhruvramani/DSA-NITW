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

lptr insertion_sort(lptr h)
{
    lptr l = h;
    while(l != NULL)
    {
        lptr t = h;
        while(t != l && t->data <= l->data)
            t = t->next;
        if(t != l)
        {
            lptr m = t;
            int k = l->data, p=m->data;
            while(m->next != l)
            {
                int f = m->next->data;
                m->next->data = p;
                p = f;
                m = m->next;
            }
            t->data = k;
        }
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
    l1 = insertion_sort(l1);
    print(l1);
    return 0;
}