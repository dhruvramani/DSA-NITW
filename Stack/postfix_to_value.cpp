#include <iostream>
using namespace std;

#define max_size 50
struct stack
{
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
void push(stack &s, int elem)
{
    if(isFull(s))
        cout<<"Stack is full";
    else
        s.elements[++s.top]=elem;
}
int isInt(char elem)
{
    return int(elem - '0') <= 10 && int(elem - '0') >= 0;
}

int perform_operation(int a, int b, char op)
{
    int c;
    switch(op)
    {
        case '+':
            c = a+b;
            break;
        case '-':
            c = a-b;
            break;
        case '/':
            c = a/b;
            break;
        case '*':
            c = a*b;
            break;
    }
    return c;
}

int main()
{
    stack s;
    s.top= -1; s.size = max_size;
    char expression[max_size];
    cout<<"Enter Expression (Operators and Numbers only) : ";
    cin>>expression;
    for(int i=0; expression[i]; i++)
        if(isInt(expression[i]))
            push(s, int(expression[i] - '0'));
        else 
            push(s, perform_operation(pop(s), pop(s), expression[i]));
    cout<<"Value : "<<pop(s);
    return 0;
}