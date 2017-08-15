#include <iostream>
#include <string>
using namespace std;

#define max_size 50

struct stack {
    int top, size;
    char elements[max_size][max_size];
};

int isempty(stack S)
{
    return S.top == -1;
}

int is_full(stack S)
{
    return S.top == S.size - 1;
}

void pop(stack& S, char ret[])
{
    if(isempty(S))
        cout<<"Underflow Error";
    else 
        strcpy(ret, S.elements[S.top--]);
}

char* peep(stack& S)
{
    if(isempty(S))
        return "\0";
    return S.elements[S.top];
}

void push(stack& S, char* x)
{
    if(is_full(S))
    {
        cout<<"Stack is full."<<endl;
        return;
    }
    strcpy(S.elements[++S.top], x);    
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

void postfix_to_prefix(char postfix[])
{
    char operators[]={'+','-','/','*','%'}, a[2];
    stack s1;
    init_stack(s1);
    a[1] = '\0';
    for(int i=0; postfix[i]; i++)
    {
        a[0] = postfix[i];
        if(index_of(operators, postfix[i], 5) == -1)
            push(s1, a);
        else
        {
            char op1[max_size], op2[max_size]; 
            pop(s1, op1);
            pop(s1, op2);
            push(s1, strcat(strcat(a, op2), op1));
            continue;
        }
    }
    strcpy(postfix, peep(s1));
}

int main()
{
    char expression[10];
    cout<<"Enter Postfix Expression : ";
    cin>>expression;
    postfix_to_prefix(expression);
    cout<<expression;
    return 0;
}
