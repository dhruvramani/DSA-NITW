#include <iostream>
using namespace std;

struct lnode 
{
    int element;
    int c;
    lnode **next;
};
typedef lnode *lptr;

lptr init(lptr m)
{
    m = new lnode;
    m->next = NULL;
    return m;
}

truct stack {
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

void push(stack& S, lptr x)
{
    if(is_full(S))
    {
        cout<<"Stack is full."<<endl;
        return;
    }
    S.elements[++S.top] = x;    
}

lptr create(lptr head, stack &s)
{
    lptr l1 = head;
    l1->element = 1;
    l1->c = 1;
    l1->next = new lptr*[l1->c];
    l1->next[0] = new lnode;
    push(s, l1);
    l1 = l1->next[0];
    l1->element = 2;
    l1->c = 1;
    l1->next = new lptr*[l1->c];
    l1->next[0] = new lnode;
    push(s, l1);
    l1 = l1->next[0];
    l1->element = 3;
    l1->c = 2;
    l1->next = new lptr*[l1->c];
    l1->next[0] = new lnode;
    l1->next[1] = new lnode;
    push(s, l1);
    lptr l2 = l1->next[1];
    l2->element = 10;
    l2->c = 2;
    l2->next = new lptr*[l2->c];
    l2->next[0] = new lnode;
    l2->next[1] = new lnode;
    push(s, l2);
    l2 = l2->next[0];
    l3 = l2->next[1];
    l2->element = 11;
    l2->c = 1;
    l2->next = new lptr*[l2->c];
    push(s, l2);
    l2->next[0] = new lnode;
    l2 = l2->next[0];
    l2->element = 12;
    l2->c = 0;
    l2->next = NULL;
    push(s, l2);
    lptr l3->element = 13;
    l3->c = 1;
    l3->next = new lptr*[l3->c];
    l3->next[0] = new lnode;
    push(s, l3);
    l3 = l3->next[0];
    l3->element = 14;
    l3->c = 1;
    l3->next = new lptr*[l3->c];
    l3->next[0] = new lnode;
    push(s, l3);
    l3 = l3->next[0];
    l3->element = 15;
    l3->c = 0;
    l3->next = NULL;
    push(s, l3);
    push(s, l1);
    l1 = l1->next[0];
    l1->element = 4;
    l1->c = 1;
    l1->next = new lptr*[l1->c];
    l1->next[0] = new lnode;
    push(s, l1);
    l1 = l1->next[0];
    l1->element = 5;
    l1->c = 2;
    l1->next = new lptr*[l1->c];
    l1->next[0] = new lnode;
    l1->next[1] = new lnode;
    push(s, l1);
    l2 = l1->next[1];
    l2->element = 8;
    l2->c = 1;
    l2->next = new lptr*[l2->c];
    l2->next[0] = new lnode;
    push(s, l2);
    l2 = l2->next[0];
    l2->element = 9;
    l2->c = 1;
    l2->next = NULL;
    push(s, l2);
    l1 = l1->next[0];
    l1->element = 6;
    l1->c = 1;
    l1->next = new lptr*[l1->c];
    l1->next[0] = new lnode;
    l1 = l1->nex[0];
    push(s, l1);
    l1->element = 7;
    l1->c = 0;
    l1->next = NULL;
    push(s, l1);
    return head;
}

void print(stack &s)
{
    while(!isEmpty(s))
    {
        lptr k = pop(s);
        cout<<k->data;
        delete k;
    }
}

int main()
{
    lptr head;
    stack s;
    s.top = -1; s.size = 50;
    s.elements = new lptr[];
    head = init(head);
    head = create(head);
    print(head);
    return 0;
}