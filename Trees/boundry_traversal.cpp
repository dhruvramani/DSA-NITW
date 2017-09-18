#include <iostream>
using namespace std;

#define max_size 50

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

void left_view(BTPTR root)
{
    if(root != NULL)
    {
        while(root->lchild && root->lchild->lchild)
        {
            cout<<root->data<<" ";
            left_view(root->lchild);
        }
    }
}

void right_view(BTPTR root)
{
    if(root != NULL)
    {
        while(root->rchild && root->rchild->rchild)
        {
            right_view(root->rchild);
            cout<<root->data<<" ";
        }
    }
}

void leaf_nodes(BTPTR root)
{
    if(root != NULL)
    {
        if(root->lchild == NULL && root->rchild == NULL)
            cout<<root->data<<" ";
        leaf_nodes(root->lchild);
        leaf_nodes(root->rchild);
    }
}

void boundry(BTPTR root)
{
    leaf_nodes(root);
    leaf_nodes(root);
    right_view(root);
}

int main()
{
    char a[] = "AMI..QC.P...LB.R..K..";
    BTPTR root = new btnode;
    root = init(root);
    create(root, a);
    boundry(root);
    return 0;
}