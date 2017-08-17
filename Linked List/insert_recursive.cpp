#include <iostream>
using namespace std;

struct lnode 
{
    int data;
    lnode *next;
};
typedef lnode *lptr;

lptr insert(lptr m, int k)
{
    lptr l = m;
    if(m == NULL)
    {
        m = new lnode;
        m->data = k;
        m->next = NULL;
    }
    else if(l->next == NULL)
    {
        l->next = new lnode;
        l = l->next;
        l->data = k;
        l->next = NULL;
    } else 
        l->next = insert(l->next, k);
    return m;
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
    int op, i;
    do {
        cout<<"\n1. Insert in LL\n2. Print\n0. Quit\nChoose one : ";
        cin>>op;
        switch(op)
        {
            case 1:
                cout<<"Enter Value : ";
                cin>>i;
                l1 = insert(l1, i);
                break;
            case 2:
                print(l1);
                break;
            case 0:
                cout<<"Quiting.";
                break;
            default :
                cout<<"Bad Choice";
        }
    } while(op != 0);
    return 0;
}