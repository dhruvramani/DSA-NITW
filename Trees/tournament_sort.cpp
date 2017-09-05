#include <iostream>
using namespace std;

#define max_size 50

struct btnode 
{
    btnode *lchild, *rchild;
    int data;
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

BTPTR create(int a[], int size)
{
    queue Q;
    init_queue(Q);
    for(int i=0; i<size; i++)
    {
        BTPTR node = new btnode;
        node->data = a[i];
        node->lchild = NULL;
        node->rchild = NULL;
        enqueue(Q, node);
    }
    cout<<"Tree Order -> Lchild : Data : Rchild.\nBottom to Top\n\n";
    while(size != 1)
    {
        BTPTR node = new btnode;
        node->lchild = dequeue(Q);
        node->rchild = dequeue(Q);
        if(node->lchild->data > node->rchild->data)
            node->data = node->lchild->data;
        else
            node->data = node->rchild->data;
        cout<<node->lchild->data<<" "<<node->data<<" "<<node->rchild->data<<endl;
        enqueue(Q, node);
        size--;
    }
    return dequeue(Q);
}

void inorder(BTPTR node)
{
    if(node != NULL)
    {
        inorder(node->lchild);
        cout<<node->data<<" ";
        inorder(node->rchild);
    }
}

int main()
{
    int a[] = {20, 30, 10, 2, 5, 1, 12, 11};
    BTPTR root = create(a, 8);
    //inorder(root);
    return 0;
}