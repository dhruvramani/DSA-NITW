#include <iostream>
using namespace std;


#define max_size 30
struct lnode 
{
    int data;
    lnode *next;
};
typedef lnode *lptr;

struct stack {
    int top, size;
    lptr elements[max_size];
};

int isEmpty(stack S)
{
    return S.top == -1;
}

int is_full(stack S)
{
    return S.top == S.size - 1;
}

lptr pop(stack& S)
{
    if(isEmpty(S))
    {
        cout<<"Underflow Error";
        return NULL;
    }
    else 
        return S.elements[S.top--];
}

void push(stack& S, lptr &x)
{
    if(is_full(S))
    {
        cout<<"Stack is full."<<endl;
        return;
    }
    S.elements[++S.top] = x;    
}

void print(lptr l)
{
    while(l != NULL)
    {
        cout<<l->data<<" ";
        l = l->next;
    }
}

lptr l3, l4;
lptr create(lptr l, int type, stack& s)
{
    lptr l1 = l;
    if(type == 1)
    {
        l1->data = 5;
        l1->next = new lnode;
        push(s, l1);
        l1 = l1->next;
        l1->data = 8;
        l3 = new lnode;
        l4 = new lnode;
    } else {
        l1->data = 3;
        l1->next = new lnode;
        push(s, l1);
        l1 = l1->next;
        l1->data = 6;
        l1->next = new lnode;
        push(s, l1);
        l1 = l1->next;
        l1->data = 1;
    }
    l1->next = l3;
    push(s, l1);
    l1 = l1->next;
    l1->data = 4;
    l1->next = new lnode;
    push(s, l1);
    l1 = l1->next;
    l1->data = 9;
    l1->next = NULL;
    push(s, l1);
    return l;

}

int main()
{
    lptr l1 = NULL, l2 = NULL;
    l1 = new lnode;
    l2 = new lnode;
    stack s1, s2;
    create(l1, 1, s1);
    create(l2, 2, s2);
    print(l1);
    cout<<endl;
    print(l2);
    cout<<endl;
    while(!isEmpty(s2))
    {
        l1 = pop(s1);
        l2 = pop(s2);
        if(l1 == l2)
            cout<<"Same : "<<l1->data<<endl;
        else 
            cout<<"Diff : "<<l1->data<<", "<<l2->data<<endl;
    }
    return 0;
}