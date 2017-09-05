#include <iostream>
using namespace std;

#define max_size 50

struct btnode 
{
    btnode *lchild, *rchild;
    char data;
    int count;
};
typedef btnode *BTPTR;

BTPTR init(BTPTR node)
{
    node->lchild = NULL;
    node->rchild = NULL;
    return node;
}

void sort(BTPTR a[], int n)
{
    for(int i=0; i<n-1; i++)
    {
        for(int j=0; j<n-i-1; j++)
            if(a[j]->count > a[j+1]->count)
            {
                BTPTR k = a[j];
                a[j] = a[j+1];
                a[j+1] = k;
            }
    }
}

void add_node(BTPTR a[], BTPTR node, int &n)
{
    for(int i=2; i<n; i++)
        a[i-2] = a[i];
    int i=n-2;
    for(; i >=0 && node->count < a[i]->count; i--)
        a[i+1] = a[i];
    a[i+1] = a[i];
    a[i] = node;
    n--;
}

BTPTR create(BTPTR a[], int n)
{
    while(n != 1)
    {
        sort(a, n);
        BTPTR node = new btnode;
        node->count = a[0]->count + a[1]->count;
        node->lchild = a[0];
        node->rchild = a[1];
        node->data = ' ';
        add_node(a, node, n);
    }
    return a[0];
}

int arr[max_size], count = 0, start=0;
void print(BTPTR node)
{
    if(node != NULL)
    {
        if(node->data != ' ')
        {
            cout<<node->data<<" ";
            for(int i=::start; i < ::count; i++)
                cout<<::arr[i];
            cout<<endl;
        }
        if(node->lchild != NULL)
        {
            ::arr[::count++] = 0;
            print(node->lchild);
        }
        if(node->lchild != NULL)
        {
            ::arr[::count++] = 1;
            print(node->rchild);
        }
    }
}

int main()
{
    int counts[] = {5, 9, 12, 13, 16, 45};
    BTPTR a[max_size];
    for(int i=0; i<6; i++)
    {
        BTPTR node = new btnode;
        node = init(node);
        node->data = char('a' + i);
        node->count = counts[i];
        a[i] = node;
    }
    BTPTR root = create(a, 6);
    print(root);
    return 0;
}