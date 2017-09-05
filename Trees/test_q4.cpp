#include <iostream>
#include <cstring>
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

char* pop(stack& S)
{
    if(isempty(S))
        cout<<"Underflow Error";
    else 
        return S.elements[S.top--];
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

stack S;
void pre_to_post(char pre[], int size)
{
	if(size == -1)
		return;
	int is_op = 0;
    char op[]={'+','-','/','*'};
    for(int i=0; i<4; i++)
    	if(pre[size] == op[i])
    	{
    		is_op = 1;
    		break;
    	}
    if(is_op == 1)
	{
		char *opnd1 = pop(S), *opnd2 = pop(S), a[2];
		a[0] = pre[size];
    	a[1] = '\0';
		char *str = strcat(opnd1, strcat(opnd2, a));
		push(S, str);
	}
	else 
	{
		char c[2];
		c[0] = pre[size];
		c[1] = '\0';
		push(S, c);
	}
    pre_to_post(pre, size - 1);
}   

int main()
{
	init_stack(S);
    char expression[max_size], output[max_size];
    cout<<"Enter Prefix Expression : ";
    cin>>expression;
   	int len = strlen(expression);
    pre_to_post(expression, len-1);
    cout<<pop(S);
    return 0;
}
