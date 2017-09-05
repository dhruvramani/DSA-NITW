#include <iostream>
using namespace std;

#define max_size 50

struct btnode 
{
    btnode *lchild, *mid, *rchild;
    char data;
};
typedef btnode *BTPTR;

BTPTR init(BTPTR node)
{
    node->lchild = NULL;
    node->mid = NULL;
    node->rchild = NULL;
    return node;
}

BTPTR create(BTPTR root)
{
	BTPTR head = root;
	head->lchild = new btnode;
	head->mid = new btnode;
	head->rchild = new btnode;
	BTPTR left = head->lchild;
	left = init(left);
	left->rchild = new btnode;
	left = left->rchild;
	left = init(left);
	left->data = 'b';
	BTPTR mid = head->mid;
	mid = init(mid);
	mid->mid = new btnode;
	mid = mid->mid;
	mid = init(mid);
	mid->data = 'a';
	BTPTR right = head->rchild;
	right = init(right);
	right->lchild = new btnode;
	right = right->lchild;	
	right = init(right);
	right->lchild = new btnode;
	right = right->lchild;	
	right = init(right);
	right->data = 'c';
	return head;
}

int count = 0, a[100];
void print_node(BTPTR node)
{
	if(node->lchild != NULL)
	{
		a[count++] = 0;
		print_node(node->lchild);
		count--;
	}
	if(node->mid != NULL)
	{
		a[count++] = 1;
		print_node(node->mid);
		count--;	
	}
	if(node->rchild != NULL)
	{
		a[count++] = 2;
		print_node(node->rchild);
		count--;
	}
	if(node->lchild == NULL && node->rchild == NULL && node->mid == NULL)
	{
		cout<<node->data<<" : ";
		for(int i=0; i<count; i++)
			cout<<a[i];
		cout<<endl;
	}

}

int main()
{
    BTPTR root = new btnode;
    root = create(root);
    print_node(root);
    return 0;
}
