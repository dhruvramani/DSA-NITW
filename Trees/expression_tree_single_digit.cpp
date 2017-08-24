#include <iostream>
using namespace std;

#define max_size 50

struct btnode 
{
    btnode *lchild, *rchild;
    char data;
};
typedef btnode *BTPTR;

struct stack {
    int top, size;
    BTPTR elements[max_size];
};

int isempty(stack S)
{
    return S.top == -1;
}

int is_full(stack S)
{
    return S.top == S.size - 1;
}

BTPTR pop(stack& S)
{
    if(isempty(S))
        return NULL;
    return S.elements[S.top--];
}

void push(stack& S, BTPTR x)
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

BTPTR init(BTPTR node)
{
    node->lchild = NULL;
    node->rchild = NULL;
    return node;
}

BTPTR create(char a[])
{
    stack S;
    init_stack(S);
    for(int i=0; a[i]; i++)
    {
        if(a[i] >= '0' && a[i] <= '9')
        {
            BTPTR operand = new btnode;
            operand = init(operand);
            operand->data = a[i];
            push(S, operand);
        } else {
            BTPTR operate = new btnode;
            operate->data = a[i];
            operate->rchild = pop(S);
            operate->lchild = pop(S);
            push(S, operate);
        }
    }
    return pop(S);
}

int calculate(int a, char op, int b)
{
    switch(op)
    {
        case '+':
            return a + b;
        case '-':
            return a - b;
        case '*':
            return a * b;
        case '/':
            return a / b;
    }
    return 0;
}

int evaluate(BTPTR node)
{
    if(node->lchild != NULL && node->rchild != NULL)
        return calculate(evaluate(node->lchild), node->data, evaluate(node->rchild));
    else 
        return int(node->data - '0') ;
}

int main()
{
    char a[] = "532*+82/-6+";
    BTPTR root = create(a);
    cout<<evaluate(root);
    return 0;
}