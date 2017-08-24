#include <iostream>
#include <string>
using namespace std;

#define max_size 50

union u
{
    char operate;
    int number;
};
struct btnode 
{
    btnode *lchild, *rchild;
    int tag;
    u data;
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

int split(char a[], char spl[][max_size]) 
{
    char str[max_size] = "";
    int count = 0, counts = 0;
    for(int i = 0; a[i]; i++)
    {
        if(a[i] == ' ')
        {
            strcpy(spl[count++], str);
            strcpy(str, "  ");
            counts = 0;
        } else 
            str[counts++] = a[i];
    }
    return count;
}

BTPTR create(char a[])
{
    stack S;
    init_stack(S);
    char spl[max_size][max_size];
    int count = split(a, spl);
    for(int i=0; i<count; i++)
    {
        if(spl[i][0] >= '0' && spl[i][0] <= '9')
        {
            BTPTR operand = new btnode;
            operand = init(operand);
            operand->tag = 1;
            operand->data.number = stoi(spl[i]);
            push(S, operand);
        } else {
            BTPTR operate = new btnode;
            operate->tag = 0;
            operate->data.operate = spl[i][0];
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
        return calculate(evaluate(node->lchild), node->data.operate, evaluate(node->rchild));
    else 
        return node->data.number;
}

int main()
{
    char a[] = "15 30 2 * + 18 2 / - 6 + ";
    BTPTR root = create(a);
    cout<<evaluate(root);
    return 0;
}