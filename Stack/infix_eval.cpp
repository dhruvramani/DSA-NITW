#include <iostream>
using namespace std;

#define max_size 50

struct stack{
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
char peep(stack s)
{
    if(isEmpty(s))
        return '\0';   
    return s.elements[s.top];
}
void push(stack &s, char elem)
{
    if(isFull(s))
        cout<<"Stack is full";
    else
        s.elements[++s.top]=elem;
}

char perform_operation(char ac, char op, char bc)
{
    int c, a = ac-'0', b = bc-'0';
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
    return char(c);
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
    int priority[]={0, 0, 1, 1, 2};
    char expression[max_size], operators[]={'+','-','/','*','^'}, open_symbols[]={'{','[', '('}, closed_symbols[]={'}', ']', ')'}, max_pr='&';
    cout<<"Enter Expression ";
    cin>>expression;
    for(int i=0; i<strlen(expression) - 1; i++)
        if(index_of(operators, expression[i], 5) == -1)
            push(s, expression[i]);
        else
        {
            if(priority[index_of(operators, expression[i], 5)] == 1)
                push(s, perform_operation(pop(s), expression[i], expression[++i]));
            else 
                push(s, expression[i]);
        }
    do {
        push(s, perform_operation(pop(s), pop(s), pop(s)));
    } while(s.top != 0);
    cout<<pop(s);
    return 0;
}