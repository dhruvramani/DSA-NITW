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

void prefix_to_posfix(char prefix[], stack &s, int pos)
{
    if(prefix[pos] == '\0')
    {
        strcpy(prefix, peep(s));
        return ;
    }
    char operators[]={'+','-','/','*','%'}, a[2];
    a[0] = prefix[pos];
    a[1] = '\0';
    if(index_of(operators, prefix[pos], 5) == -1)
        push(s, a);
    else {
        char op1[max_size], op2[max_size]; 
        pop(s, op1);
        pop(s, op2);
        push(s, strcat(strcat(op1, op2), a));
    }
    prefix_to_posfix(prefix, s, pos + 1);
}   

int main()
{
    stack s;
    init_stack(s);
    char expression[max_size];
    cout<<"Enter Postfix Expression : ";
    cin>>expression;
    reverse(expression);
    prefix_to_posfix(expression, s, 0);
    cout<<expression;
    return 0;
}
