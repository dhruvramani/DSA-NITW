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

int count = 0;
BTPTR a[100];
void print(BTPTR node)
{
	if(node->lchild == NULL && node->rchild == NULL)
	{
		for(int i=0; i<count; i++)
			cout<<a[i]->data;
		cout<<node->data<<endl;
	} else {
		a[count++] = node;
		if(node->lchild)
			print(node->lchild);
		if(node->rchild)
			print(node->rchild);
		count--;		
	}
}

int main()
{
    char a[] = "A.BC..DE...";
    BTPTR root = new btnode;
    root = init(root);
    root = create(root, a);
    print(root);
    return 0;
}
