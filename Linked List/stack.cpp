#include <iostream>
using namespace std;

struct lnode 
{
    int data;
    lnode *next;
};
typedef lnode *lptr;

struct stack {
    lptr top;
};

lptr push(stack s, int l)
{ 
    if(s.top == NULL)
    {
        s.top = new lnode;
        s.top->data = l;
        s.top->next = NULL;
    } else {
        lptr k = new lnode;
        k->next = s.top;
        k->data = l;
        s.top = k;
    }
    return s.top;
}

lptr pop(stack s, int &data)
{
    if(s.top == NULL)
    {
        data = -1;
        cout<<"Underflow ";
        return NULL;
    }
    else {
        data = s.top->data;
        s.top = s.top->next;
    }
    return s.top;
}

void print(stack s)
{
    int data;
    while(s.top != NULL)
    {
        s.top = pop(s, data);
        cout<<data<<" ";
    }
}

int main()
{
    stack s;
    s.top = NULL;
    int op, i;
    do {
        cout<<"\n1. Push in Stack\n2. Pop from Stack\n0. Quit\nChoose one : ";
        cin>>op;
        switch(op)
        {
            case 1:
                cout<<"Enter Value : ";
                cin>>i;
                s.top = push(s, i);
                break;
            case 2:
            {
                s.top = pop(s, i);
                cout<<endl<<i<<endl;
                break;
            }
            case 0:
                cout<<"Quiting.";
                break;
            default :
                cout<<"Bad Choice";
        }
    } while(op != 0);
    return 0;
}