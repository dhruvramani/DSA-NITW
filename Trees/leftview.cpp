#include <iostream>
using namespace std;

#define max_size 50

struct btnode 
{
    btnode *lchild, *rchild;
    char data;
};
typedef btnode *BTPTR;

struct queue {
    int front, rear, size;
    BTPTR elements[max_size];
};

int isempty(queue Q)
{
    return Q.rear == -1 || Q.front == -1;
}

int is_full(queue Q)
{
    return (Q.rear + 1) % Q.size == Q.front;
}

void enqueue(queue& Q, BTPTR x)
{
    if(is_full(Q))
    {
        cout<<"Queue is full."<<endl;
        return ;
    }
    if(isempty(Q))
        Q.front=0;
    Q.elements[(++Q.rear) % Q.size] = x;
}

BTPTR dequeue(queue& Q)
{
    if(isempty(Q))
        return NULL;
    BTPTR x = Q.elements[Q.front];
    if(Q.front == Q.rear)
    {
        Q.rear = -1;
        Q.front = -1;
    } else 
        Q.front = (Q.front + 1) % Q.size;
    return x;
}

void init_queue(queue &Q)
{
    Q.size = max_size;
    Q.front = -1;
    Q.rear = -1;
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

int count = 0, count2 = 0;
void inorder(BTPTR root)
{
    if(root != NULL)
    {
        ::count2++;
        if(::count2 > ::count)
            cout<<root->data;

        inorder(root->lchild);
        inorder(root->rchild);
    }
}

void left_view(BTPTR root)
{
    BTPTR node = root;
    ::count = 0;
    while(node != NULL)
    {
        cout<<node->data<<" ";
        node = node->lchild;
        ::count++;
    }
    inorder(root->rchild);
    
}

int main()
{
    char a[] = "AMI..QC.P...LB.R..K..";
    BTPTR root = new btnode;
    root = init(root);
    create(root, a);
    left_view(root);
    return 0;
}