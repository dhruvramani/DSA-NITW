#include <iostream>
using namespace std;

#define max_size 50

struct hnode 
{
    hnode *parent, **children;
    int data, count;
};
typedef hnode *HPTR;

struct queue {
    int front, rear, size;
    HPTR elements[max_size];
};

int isempty(queue Q)
{
    return Q.rear == -1 || Q.front == -1;
}

int is_full(queue Q)
{
    return (Q.rear + 1) % Q.size == Q.front;
}

void enqueue(queue& Q, HPTR x)
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

HPTR dequeue(queue& Q)
{
    if(isempty(Q))
        return NULL;
    HPTR x = Q.elements[Q.front];
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

HPTR init(HPTR node)
{
    node->parent = NULL;
    node->children = new hnode*[max_size];
    node->count = 0;
    return node;
}

int height(HPTR node)
{
    if(node == NULL)
        return -1;
    int max = -1;
    for(int i=0; i<node->count; i++)
        if(height(node->children[i]) > max)
            max = height(node->children[i]);
    return 1 + max;
}

HPTR heap_end(HPTR root){
    if(root == NULL)
        return NULL;
    queue q;
    enqueue(q, root);
    while(curr != NULL)
    {
        HPTR curr = dequeue(q);
        if(curr->count == 0)
            return curr;
        for(int i=0; i<curr->count; i++)
            enqueue(q, curr->children[i]);
    }
}

HPTR perculate(HPTR root)
{    
    HPTR end = heap_end(root);
    while(end->parent != NULL && end->parent->data > end->data)
    {
        int k = end->parent->data;
        end->parent->data = end->data;
        end->data = k;
        end = end->parent;
    }
    return root;
}

HPTR insert(HPTR root, int n)
{
    HPTR end = heap_end(root);
    end->children[count++] = new hnode;
    end->children[count] = init(end->children[count]);
    end->children[count]->parent = end;
    end = end->children[count];
    end->data = n;
    root = perculate(root);
    return root;
}

int main()
{
    int a[] = {5, 3, 10, 30, 1, 12};
    HPTR root = new hnode;
    root = init(root);
    root->data = a[0];
    for(int i=1; i<6; i++)
        root = insert(root, a[i]);
     int *arr = heap_sort(root);
    for(int i=0; i<6; i++)
        cout<<arr[i]<<" ";
    return 0;
}