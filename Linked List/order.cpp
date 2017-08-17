#include <iostream>
using namespace std;

#define max_size 50

struct stack{
    int top, size;
    int elements[max_size];
};

int isEmpty(stack s)
{
    return s.top == -1;
}

int isFull(stack s)
{
    return s.top == s.size - 1;
}

int pop(stack &s)
{
    if(isEmpty(s))
        return '\0';
    return s.elements[s.top--];
}
int peep(stack s)
{
    if(isEmpty(s))
        return '\0';   
    return s.elements[s.top];
}
void push(stack &s, int elem)
{
    if(isFull(s))
        cout<<"Stack is full";
    else
        s.elements[++s.top]=elem;
}

int order(stack s1, stack s2, int s)
{
    if(s <= 0 || (s < peep(s1) && s < peep(s2)))
        return 0;
    if(peep(s1) == s)
        return 1;
    if(peep(s2) == s)
        return 2;
    int k = 0;
    if(!isEmpty(s1))
    {
        int l = pop(s1);
        k = order(s1, s2, s - l);
        if(k == 0)
            push(s1, l);
        if(k != 0)
        {
            cout<<", "<<k;
            return 1;
        }
    }
    if(!isEmpty(s2))
    {
        if(k == 0 || k == -1)
        {
            int l = pop(s2);
            int k = order(s1, s2, s - l);
            if(k == 0)
                push(s2, l);
            if(k != 0)
            {
                cout<<", "<<k;
                return 2;
            }
        }
    }
}

int main()
{
    stack s1, s2;
    s1.top = -1; s1.size = max_size;
    s2.top = -1; s2.size = max_size;
    int op, i;
    do {
        cout<<"\n1. Insert in Stack 1\n2. Insert in Stack 2\n3. Print Order\n0. Quit\nChoose one : ";
        cin>>op;
        switch(op)
        {
            case 1:
                cout<<"Enter Value : ";
                cin>>i;
                push(s1, i);
                break;
            case 2:
                cout<<"Enter Value : ";
                cin>>i;
                push(s2, i);
                break;
            case 3:
                cout<<"Enter Value : ";
                cin>>i;
                cout<<endl;
                i = order(s1, s2, i);
                cout<<", "<<i;
                break;
            case 0:
                cout<<"Quiting.";
                break;
            default :
                cout<<"Bad Choice";
        }
    } while(op != 0);
    return 0;
    return 0;
}