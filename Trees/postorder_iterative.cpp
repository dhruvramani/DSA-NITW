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

int pos = 0;
BTPTR create(BTPTR node, char a[])
{
    if(a[pos++] != '.')
    {
        node->data = a[pos-1];
        node->lchild = new btnode;
        node->lchild = create(node->lchild, a);
        node->rchild = new btnode;
        node->rchild = create(node->rchild, a);
        return node;
    } else 
        return NULL;
}

void postorder(BTPTR root)
{
    stack S;
    init_stack(S);
    BTPTR node = root;
    push(S, node);
    while(node != NULL)
    {
        push(S, node);
        node = node->lchild;
    }
    while(node != root)
    {
        node = pop(S);
        BTPTR right = node;
        while(right != NULL)
        {
            right = right->rchild;
            if(right != NULL)
                cout<<right->data;
        }
        cout<<node->data;
    }
}

int main()
{
    char a[] = "AMI..Q..L..";
    BTPTR root = new btnode;
    root = create(root, a);
    postorder(root);
    return 0;
}