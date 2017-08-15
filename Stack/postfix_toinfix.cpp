#include <iostream>
#include <string>
using namespace std;

#define max_size 50

struct stack {
    int top, size;
    char elements[max_size];
};

int isempty(stack S)
{
    return S.top == -1;
}

int is_full(stack S)
{
    return S.top == S.size - 1;
}

char pop(stack& S)
{
    if(isempty(S))
        return '\0';
    return S.elements[S.top--];
}

void push(stack& S, char x)
{
    if(is_full(S))
    {
        cout<<"Stack is full."<<endl;
        return;
    }
    S.elements[++S.top] = x;    
}

void init_stack(stack &S)
{
    S.size = max_size;
    S.top = -1;
}

int index_of(char elements[], char elem, int n)
{
    for(int i=0; i<n; i++)
        if(elements[i] == elem)
            return i;
    return -1;
}

void reverse(char str[])
{
    int n=0;
    for(; str[n]; n++);
    for(int i=0; i < n/2; i++)
    {
        char a=str[i];
        str[i] = str[n-i-1];
        str[n-i-1] = a;
    }
}


void postfixToInfix(char s[])
{
    reverse(s);
    char operators[]={'+','-','/','*','%'};
    stack s1, s2;
    init_stack(s1);
    init_stack(s2);
    for(int i=0; s[i]; i++)
        if(index_of(operators, s[i], 5) == -1)
            push(s1, s[i]);
        else
            push(s2, s[i]);
    
    while(!isempty(s2))
    {
        char od1 = pop(s1), opr = pop(s2);
        cout<<od1<<opr;
    }
    cout<<pop(s1);
}

int main()
{
    char expression[max_size];
    cout<<"Enter Postfix Expression : ";
    cin>>expression;
    postfixToInfix(expression);
    return 0;
}
