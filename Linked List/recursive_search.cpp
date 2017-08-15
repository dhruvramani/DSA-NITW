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

int search(lptr l, int k)
{
    if(l ==  NULL)
        return 0;
    if(l->data == k)
        return 1;
    int a = search(l->next, k);
    return a || 0;
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
    cout<<"Search For Element : ";
    cin>>n;
    if(search(l1, n))
        cout<<"Found";
    else cout<<"Not Found";
    return 0;
}