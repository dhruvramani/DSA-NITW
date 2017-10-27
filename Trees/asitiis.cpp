#include <iostream>
using namespace std;

#define max_size 50

struct btnode 
{
    btnode *lchild, *rchild;
    int x;
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


BTPTR arr[max_size];
int count = 0;
BTPTR preorder(BTPTR node)
{
    if(node != NULL)
    {
        preorder(node->lchild);
        ::arr[::count++] = node;
        preorder(node->rchild);
        return node;
    }
}

void print_till_empty(queue &Q2)
{
    cout<<'\n';
    while(!isempty(Q2))
    {
        BTPTR k = dequeue(Q2);
        for(int i=0; i<k->x; i++)
        cout<<" ";
        cout<<k->data;
    }
    cout<<'\n';
}

void level_order(BTPTR root)
{
    queue Q, Q2;
    init_queue(Q);
    init_queue(Q2);
    enqueue(Q, root);
    BTPTR next_line = new btnode;
    next_line->data = '\n';
    next_line->lchild = NULL;
    next_line->rchild = NULL;
    root = preorder(root);
    for(int i=0; i < ::count; i++)
        ::arr[i]->x = i;
    int big_count = ::count;

    while(!isempty(Q))
    {
        BTPTR node = dequeue(Q);
        if(node->rchild != NULL && node->lchild != NULL)
            enqueue(Q, next_line);
        if(node->data != '\n')
        {
            enqueue(Q2, node);
            for(int i=0; i<node->x; i++)
                cout<<" ";
            if(node->x <= big_count/2)
                cout<<"/";
            else
                cout<<"\\";
        }
        if(node->data == '\n')
            print_till_empty(Q2);
        if(node->lchild != NULL)
            enqueue(Q, node->lchild);
        if(node->rchild !=  NULL)
            enqueue(Q, node->rchild);
    }
    print_till_empty(Q2);
}

int main()
{
    char a[] = "AMI..J..Q..L..";
    BTPTR root = new btnode;
    root = init(root);
    create(root, a);
    level_order(root);
    return 0;
}