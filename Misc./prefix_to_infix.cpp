#include <iostream>
using namespace std;

#define max_size 50

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

void prefixToInfix(char infix[])
{
    reverse(expression);
    int priority[]={0, 0, 1, 1, 1};
    char operators[]={'+','-','/','*','%'};
    for(int i=1; infix[i]; i++)
        if(index_of(operators, infix[i], 5) != -1)
            for(int j=i, done=0; j>=1 && done==0; j--)
                if(index_of(operators, infix[j], 5) == -1 && index_of(operators, infix[j-1], 5) == -1)
                {   
                    char k=infix[i];
                    for(int l=i-1; l>=j; l--)
                        infix[l+1] = infix[l];
                    infix[j] = k;
                    done = 1;
                }
    reverse(expression);
}

int main()
{
    char expression[max_size];
    cout<<"Enter Postfix Expression : ";
    cin>>expression;
    prefixToInfix(expression);
    cout<<"Infix Expression : "<<expression;
    return 0;
}