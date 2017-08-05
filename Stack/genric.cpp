#include <iostream>
using namespace std;

#define max_size 50
union genric
{
    int i;
    float f;
    char c;
    char st[max_size];
};

struct stack
{
    int top, size, tag[max_size];
    union genric elements[max_size];
};

int isEmpty(stack s)
{
    return s.top == -1;
}

int isFull(stack s)
{
    return s.top == s.size - 1;
}

genric pop(stack &s)
{
    if(!isEmpty(s)) 
        return s.elements[s.top--];
}
void push(stack &s, genric elem, int tag)
{
    if(isFull(s))
        cout<<"Stack is full";
    else
    {
        s.elements[++s.top] = elem;
        s.tag[s.top] = tag;
    }
}

void peep(stack s)
{
        switch(s.tag[s.top] + 1)
        {
            case 1:
                cout<<s.elements[s.top].i<<endl;
                break;
            case 2:
                cout<<s.elements[s.top].f<<endl;
                break;
            case 3:
                cout<<s.elements[s.top].c<<endl;
                break;
            case 4:
                cout<<s.elements[s.top].st<<endl;
                break;
        }
}

void print(stack s)
{
    for(int i = s.top; i>=0; i--)
    { 
        switch(s.tag[i] + 1)
        {
            case 1:
                cout<<s.elements[i].i<<'\t';
                break;
            case 2:
                cout<<s.elements[i].f<<'\t';
                break;
            case 3:
                cout<<s.elements[i].c<<'\t';
                break;
            case 4:
                cout<<s.elements[i].st<<'\t';
                break;
        }   
    }
}

int main()
{
    stack s;
    s.top= -1;
    s.size = max_size;
    int n;
    cout<<"Enter Number of Elements to push : ";
    cin>>n;
    for(int i=0; i<n; i++)
    {
        int op, tag;
        union genric oo;
        cout<<"1. Integer\n2. Float\n3. Char\n4. String\nChoose one : ";
        cin>>op;
        tag = op-1;
        switch(op)
        {
            case 1:
                cout<<"Enter Value : ";
                cin>>oo.i;
                break;
            case 2:
                cout<<"Enter Value : ";
                cin>>oo.f;
                break;
            case 3:
                cout<<"Enter Value : ";
                cin>>oo.c;
                break;
            case 4:
                cout<<"Enter Value : ";
                cin>>oo.st;
                break;
            default :
                cout<<"Bad Choice";
        }
        push(s, oo, tag);
    }
    cout<<"Last Value : ";
    peep(s);
    cout<<"Whole Stack : ";
    print(s);
    return 0;
}