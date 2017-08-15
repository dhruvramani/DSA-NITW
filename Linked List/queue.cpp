#include <iostream>
using namespace std;

struct lnode 
{
    int data;
    lnode *next;
};
typedef lnode *lptr;

struct queue {
    lptr front, rear;
};

queue dequeue(queue q, int a)
{ 
    if(q.front == NULL)
    {
        cout<<"Underflow Error\n";
        a = -1;
        return NULL;
    } else 
    {
        lptr t = q.rear;
        while(t->next->next != NULL)
            t = t->next;
        q.front = t;
        a = t->next->data;
    }
    return q;
}

queue enqueue(queue q, int l)
{ 
    if(q.rear == NULL)
    {
        q.rear = new lnode;
        q.rear->data = l;
        q.rear->next = NULL;
        q.front = q.rear;
    } else {
        lptr k = new lnode;
        k->next = q.rear;
        k->data = l;
        q.rear = k;
    }
    return q;
}

int main()
{
    queue 1;
    q.front = NULL;
    q.rear = NULL;
    int op, i;
    do {
        cout<<"\n1. Enqueue\n2. Dequeue\n0. Quit\nChoose one : ";
        cin>>op;
        switch(op)
        {
            case 1:
                cout<<"Enter Value : ";
                cin>>i;
                q = enqueue(q, i);
                break;
            case 2:
            {
                s.top = dequeue(s, i);
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