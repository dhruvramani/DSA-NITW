#include <iostream>
using namespace std;

#define max_size 50

struct gtnode 
{
    gtnode *fchild, *nsibling;
    char data;
};
typedef gtnode *GTPTR;

struct queue {
    int front, rear, size;
    GTPTR elements[max_size];
};

int isempty(queue Q)
{
    return Q.rear == -1 || Q.front == -1;
}

int is_full(queue Q)
{
    return (Q.rear + 1) % Q.size == Q.front;
}

void enqueue(queue& Q, GTPTR x)
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

GTPTR dequeue(queue& Q)
{
    if(isempty(Q))
        return NULL;
    GTPTR x = Q.elements[Q.front];
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

void level_order(GTPTR root)
{
    queue Q;
    init_queue(Q);
    enqueue(Q, root);
    GTPTR next_line = new gtnode;
    next_line->data = '\n';
    next_line->fchild = NULL;
    next_line->nsibling = NULL;
    while(!isempty(Q))
    {
        GTPTR node = dequeue(Q);
        if(node->fchild != NULL && node->nsibling != NULL)
            enqueue(Q, next_line);
        cout<<node->data;
        if(node->nsibling)
            enqueue(Q, node->nsibling);
        if(node->fchild != NULL)
            enqueue(Q, node->fchild);
    }
}

int main()
{
    char a[] = "A,(B,(L, M),C,D,(J, K))";
    GTPTR root = new gtnode;
    root = init(root);
    root = create(root, a);
    level_order(root);
    return 0;
}