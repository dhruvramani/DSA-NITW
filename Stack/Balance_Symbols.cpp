#include <iostream>
using namespace std;

#define max_size 50
struct stack
{
    int top, size;
    char elements[max_size];
};

int isEmpty(stack s)
{
    return s.top == -1;
}

int isFull(stack s)
{
    return s.top == s.size - 1;
}

char pop(stack &s)
{
    if(isEmpty(s))
        return '\0';
    return s.elements[s.top--];
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

int main()
{
    stack s;
    s.top= -1; s.size = max_size;
    int error=0;
    char open_symbols[] = {'{','[', '('}, closed_symbols[] = {'}', ']', ')'}, expression[max_size];
    cout<<"Enter Expression ";
    cin>>expression;
    for(int i=0; expression[i]; i++)
    {
        if(index_of(open_symbols, expression[i], 3) != -1)
            push(s, expression[i]);
        else if(index_of(closed_symbols, expression[i], 3) != -1)
            if(index_of(open_symbols, pop(s), 3) == index_of(closed_symbols, expression[i], 3))
                continue;
            else {
                error=1;
                break;
            } 
        else continue;
    }
    if(error)
        cout<<"ERROR - Symbols aren't balanced";
    else
        cout<<"Symbols are balanced";
    return 0;
}