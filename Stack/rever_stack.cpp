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
        return -1000;
    return s.elements[s.top--];
}
int peep(stack s)
{
    if(isEmpty(s))
        return -1000;   
    return s.elements[s.top];
}
void push(stack &s, char elem)
{
    if(isFull(s))
        cout<<"Stack is full";
    else
        s.elements[++s.top]=elem;
}

int index_of(char elements[], char elem, int n)
{
    for(int i=0; i<n; i++)
        if(elements[i] == elem)
            return i;
    return -1;
}

void reverse(stack &s)
{
    if(peep(s) == -1000)
        return ;
    int a = pop(s);
    reverse(s);
    push(s, a);
}

int main()
{
    stack s;
    s.top= -1;
    cout<<"Enter Size (<50) : ";
    cin>>s.size;
    for(int i=0; i<s.size; i++)
    {
        int a;
        cout<<"Enter Elements : ";
        cin>>a;
        push(s, a);
    }
    reverse(s);
    for(int i=0; i<s.size; i++)
        cout<<pop(s)<<" ";
    return 0;

}