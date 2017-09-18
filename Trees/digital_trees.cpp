#include <iostream>
#include <cstring>

using namespace std;
#define max_size 50

struct btnode 
{
    btnode *lchild, *rchild;
    char data[max_size];
};
typedef btnode *BTPTR;

BTPTR init(BTPTR node)
{
    node->lchild = NULL;
    node->rchild = NULL;
    return node;
}

int count = 0;
BTPTR add(BTPTR root, char a[])
{
    if(root != NULL)
    {
        if(a[::count++] == '0')
            root->lchild = add(root->lchild, a);
        else 
            root->rchild = add(root->rchild, a);
    } else {
        root = new btnode;
        root = init(root);
        strcpy(root->data, a);
    }
    return root;
}

int len(char a[])
{
    int i =0;
    while(i<strlen(a))
        if(a[i] == '0' || a[i] == '1')
            i++;
    return i;
}

int count3=0;
int search(BTPTR root, char a[])
{
    if(root != NULL)
    {
        while(a[::count3] == root->data[::count3] && (a[::count3] == '0' || a[::count3] == '1'))
            ::count3++;
        if(::count3 == len(a))
            return 1;
        if(a[::count3] == '0')
            return search(root->lchild, a);
        else 
            return search(root->rchild, a);
    }
    return 0;
}

void preorder(BTPTR root)
{
    if(root != NULL)
    {
        cout<<root->data<<" ";
        preorder(root->lchild);
        preorder(root->rchild);
    }
}

int main()
{
    int n;
    cout<<"Enter Number : ";
    cin>>n;
    BTPTR root = NULL;
    for(int i=0; i<n; i++)
    {
        ::count=0;
        char a[max_size];
        cout<<"Enter Bits : ";
        cin>>a;
        root = add(root, a);
    }
    char a[max_size];
    preorder(root);
    cout<<endl<<"Enter Bit to search : ";
    cin>>a;
    cout<<search(root, a);
    return 0;
}