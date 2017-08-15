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

int subseq_sum(lptr l, int k)
{
    lptr m = l;
    while(m->next != NULL)
    {
        lptr n = m;
        int c = 0;
        while(n != NULL)
        {
            c += n->data;
            if(c > k)
                break;
            if(c == k)
                return 1;
            n = n->next;
        }
        m = m->next;
    }
    return 0;
}


int main()
{
    lptr l1 = NULL;
    int n, m;
    cout<<"Enter No. of Elements for L1 : ";
    cin>>n;
    for(; n>0; n--)
    {
        int k;
        cout<<"Enter Value : ";
        cin>>k;
        l1 = add(l1, k);
    }
    cout<<"Number : ";
    cin>>n;
    if(subseq_sum(l1, n))
        cout<<"Yes";
    else cout<<"No";
    return 0;
}