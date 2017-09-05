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

int height(BTPTR node)
{
	if(node == NULL)
		return -1;
	int lh = height(node->lchild), rh = height(node->rchild);
	if(lh > rh)
		return 1 + lh;
	return 1 + rh;
}

int main()
{
    char a[] = "AMI..Q..L..";
    BTPTR root = new btnode;
    root = init(root);
    create(root, a);
    cout<<height(root);
    return 0;
}
