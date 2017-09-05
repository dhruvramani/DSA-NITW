#include <iostream>
using namespace std;

#define max_size 50

struct gtnode 
{
    gtnode *fchild, *nsibling;
    char data;
};
typedef gtnode *GTPTR;

struct stack {
    int top, size;
    GTPTR elements[max_size];
};

int isempty(stack S)
{
    return S.top == -1;
}

int is_full(stack S)
{
    return S.top == S.size - 1;
}

GTPTR pop(stack& S)
{
    if(isempty(S))
        return NULL;
    return S.elements[S.top--];
}

void push(stack& S, GTPTR x)
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

GTPTR init(GTPTR node)
{
    node->fchild = NULL;
    node->nsibling = NULL;
    return node;
}

GTPTR create(GTPTR head, char a[])
{
    GTPTR run = head, old[max_size];
    int old_count = 0;
    for(int i=0; a[i]; i++)
        if(a[i] == '(')
        {
            run->fchild = new gtnode;
            old[old_count++] = run;
            run = run->fchild;
            run = init(run);
        } else if (a[i] == ')')
        {
            run->nsibling = NULL;
            run = old[--old_count];
            run->nsibling = new gtnode;
            run = run->nsibling;
        }
        else if(a[i] == ',' || a[i] == ' ');
        else {      
            run->data = a[i];
            if(a[i+2] != '(')
            {
                run->nsibling = new gtnode;
                run = run->nsibling;
                run = init(run);
            }
        }
    run->nsibling = NULL;
    return head;
}

void dfs(GTPTR root)
{
    stack S;
    push(S, root);
    return;
    while(!isempty(S))
    {
        GTPTR node = pop(S);
        cout<<node->data;
        if(node->nsibling)
            push(S, node->nsibling);
        if(node->fchild)
            push(S, node->fchild);
    }
}

int main()
{
    char a[] = "A,(B,(L, M),C,D,(J, K))";
    GTPTR root = new gtnode;
    root = init(root);
    root = create(root, a);
    dfs(root);
    return 0;
}