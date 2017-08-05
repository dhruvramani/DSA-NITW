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
    int priority[]={0, 0, 1, 1, 1}, inside=0;
    char expression[max_size], operators[]={'+','-','/','*','%'}, open_symbols[]={'{','[', '('}, closed_symbols[]={'}', ']', ')'};
    cout<<"Enter Expression ";
    cin>>expression;
    for(int i=0; expression[i]; i++)
        if(index_of(open_symbols, expression[i], 3) != -1)
        {
            push(s, expression[i]);
            inside=1;
        }
        else if(index_of(closed_symbols, expression[i], 3) != -1)
        {
            while(index_of(open_symbols, peep(s), 3) == -1)
                cout<<pop(s)<<" ";
            pop(s);
            inside = 0;
        }
        else if(index_of(operators, expression[i], 5) != -1)
        {
            if(isEmpty(s) || inside == 1)
            {
                push(s, expression[i]);
                inside = 0;
            }
            else 
            {
                if(priority[index_of(operators, expression[i], 5)] > priority[index_of(operators, peep(s), 5)])
                    push(s, expression[i]);
                else if(priority[index_of(operators, expression[i], 5)] < priority[index_of(operators, peep(s), 5)])
                {    
                    do {
                        cout<<pop(s)<<" ";
                    } while(s.top != -1);
                    push(s, expression[i]);
                }
                else {
                    cout<<pop(s)<<" ";
                    push(s, expression[i]);
                }
            }
        }
        else 
            cout<<expression[i]<<" ";
    while(s.top != -1)
        cout<<pop(s)<<" ";
    return 0;
}