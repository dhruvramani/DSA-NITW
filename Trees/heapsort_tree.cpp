#include <iostream>
using namespace std;

#define max_size 50

struct hnode 
{
    hnode *lchild, *rchild, *parent;
    int data;
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
    node->lchild = NULL;
    node->rchild = NULL;
    node->parent = NULL;
    return node;
}

int height(HPTR node)
{
    if(node == NULL)
        return -1;
    int lh = height(node->lchild), rh = height(node->rchild);
    if(lh > rh)
        return 1 + lh;
    return 1 + rh;
}

HPTR heap_end(HPTR root){
    if(root == NULL)
        return NULL;
    queue q;
    enqueue(q, root);
    HPTR curr = root, last = root;
    while(curr != NULL)
    {
        curr = dequeue(q);
        if(curr->lchild != NULL){
            enqueue(q, curr->lchild);
            last = curr->lchild;
        }
        else
            break;
        if(curr->rchild != NULL){
            enqueue(q, curr->rchild);
            last = curr->rchild;
        }
        else
            break;
    }
    return last;
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
    end->lchild = new hnode;
    end->lchild = init(end->lchild);
    end->lchild->parent = end;
    end = end->lchild;
    end->data = n;
    root = perculate(root);
    return root;
}

int* heap_sort(HPTR root)
{
    static int arr[max_size], count = 0;
    while(height(root) > 1)
    {
        arr[count++] = root->data;
        HPTR end = heap_end(root);
        if(end->parent->lchild == end)
            end->parent->lchild = NULL;
        else if(end->parent->rchild == end)
            end->parent->rchild = NULL;
        root->data = end->data;
        delete end;
        root = perculate(root);
    }
    arr[count++] = root->data;
    return arr;
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