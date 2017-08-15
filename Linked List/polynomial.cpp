#include <iostream>
using namespace std;

struct lnode 
{
    int c, exp;
    lnode *next;
};
typedef lnode *lptr;
lptr add(lptr l, int k, int exp)
{

    if(l == NULL)
    {
        l = new lnode;
        l->c = k;
        l->exp = exp;
        l->next = NULL;
    } else {
        lptr t = l;
        while(t->next != NULL)
            t = t->next;
        t->next = new lnode;
        t->next->next = NULL;
        t->next->c = k;
        t->next->exp = exp;
        t = t->next;
    }
    return l;
}

lptr remove(lptr l, int exp)
{
    if(l == NULL)
        return NULL;
    lptr t=l;
    if(t->exp == exp)
    {
        if(t->next == NULL)
            return NULL;
        else 
        {
            l = l->next;
            return l;
        }
    }
    while(t->next->exp != exp)
        t = t->next;
    lptr k = t->next;
    t->next = t->next->next;
    delete k;
    return l;
}

int exp_search(lptr l, int k)
{
    while(l != NULL)
    {
        if(l->exp == k)
            return 1;
        l = l->next;
    }
    return 0;
}

void sum(lptr l1, lptr l2)
{
    while(l1 != NULL)
    {
        if(exp_search(l2, l1->exp) == 1)
        {
            l1->c = l1->c + l2->c;
            l2 = remove(l2, l1->exp);
        }
        cout<<l1->c<<"*X^"<<l1->exp<<" + ";
        l1 = l1->next;
    }
    while(l2 != NULL){
        cout<<l2->c<<"*X^"<<l2->exp<<" + ";
        l2 = l2->next;
    }
}

int main()
{
    lptr l1 = NULL, l2 = NULL;
    int n;
    cout<<"Enter Number of Elements in Eqn1 : ";
    cin>>n;
    for(; n>0; n--)
    {
        int c, exp;
        cout<<"Enter Constant and Exp : ";
        cin>>c>>exp;
        l1 = add(l1, c, exp);
    }
    cout<<"Enter Number of Elements in Eqn1 : ";
    cin>>n;
    for(; n>0; n--)
    {
        int c, exp;
        cout<<"Enter Constant and Exp : ";
        cin>>c>>exp;
        l2 = add(l2, c, exp);
    }
    sum(l1, l2);
    return 0;
}