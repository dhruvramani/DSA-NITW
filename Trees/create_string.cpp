#include <iostream>
using namespace std;

struct btnode 
{
    btnode *lchild, *rchild;
    char data;
};
typedef btnode *BTPTR;

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

void preorder(BTPTR node)
{
    if(node != NULL)
    {
        cout<<node->data<<" ";
        preorder(node->lchild);
        preorder(node->rchild);
    }
}

int main()
{
    char a[] = "AMI..Q..L..";
    BTPTR root = new btnode;
    root = init(root);
    create(root, a);
    preorder(root);
    return 0;
}