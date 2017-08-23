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

void level_order(BTPTR root)
{
    queue Q;
    init_queue(Q);
    enqueue(Q, root);
    BTPTR next_line = new btnode;
    next_line->data = '\n';
    next_line->lchild = NULL;
    next_line->rchild = NULL;
    root = preorder(root);
    for(int i=0; i < ::count; i++)
        ::arr[i]->x = i;
    while(!isempty(Q))
    {
        BTPTR node = dequeue(Q);
        if(node->rchild != NULL && node->lchild != NULL)
            enqueue(Q, next_line);
        if(node->data != '\n')
            for(int i=0; i<node->x; i++)
                cout<<" ";
        cout<<node->data;
        if(node->lchild != NULL)
            enqueue(Q, node->lchild);
        if(node->rchild !=  NULL)
            enqueue(Q, node->rchild);
    }
}

void print_subtrees(BTPTR node)
{
    if(node != NULL)
    {        
        level_order(node);
        cout<<"\n\n";
        print_subtrees(node->lchild);
        cout<<"\n\n";
        print_subtrees(node->rchild);
        cout<<"\n\n";
    }

}

int main()
{
    char a[] = "AMI..Q..L..";
    BTPTR root = new btnode;
    root = init(root);
    create(root, a);
    print_subtrees(root);
    return 0;
}