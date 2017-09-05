#include <iostream>
using namespace std;

#define max_size 50

struct bstnode 
{
    bstnode *lchild, *rchild;
    int data;
};
typedef bstnode *BTPTR;

BTPTR init(BTPTR node)
{
    node->lchild = NULL;
    node->rchild = NULL;
    return node;
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

int pos = 0;
BTPTR add(BTPTR root, int k)
{
    BTPTR node = root;
    while(true)
    {
        if(k <= node->data)
        {
            if(node->lchild != NULL)
                node = node->lchild;
            else {
                node->lchild = new bstnode;
                node->lchild = init(node->lchild);
                node->lchild->data = k;
                return root;
            }
        }
        else if(k > node->data)
        {
            if(node->rchild != NULL)
                node = node->rchild;
            else {
                node->rchild = new bstnode;
                node->rchild = init(node->rchild);
                node->rchild->data = k;
                return root;
            }
        }
    }
}


BTPTR AVL(BTPTR root)
{
	int lh = -1, rh = -1;
	if(root->lchild)
	{
		root->lchild = AVL(root->lchild);
		lh = height(root->lchild);
	}
	if(root->rchild)
	{
		root->rchild = AVL(root->rchild);
		rh = height(root->rchild);
	}
	if(lh - rh >= 2 || rh - lh >= 2)
	{
		int left_shift = 0, right_shift = 0;
		if(root->rchild && root->rchild->rchild)
			left_shift = 1;
		if(root->lchild && root->lchild->lchild)
			right_shift = 1;
		
		if(left_shift == 1 && right_shift == 0)
		{
			
			BTPTR k1 = root, b = root->rchild->lchild;
			root = root->rchild;
			k1->rchild = b;
			root->lchild = k1;
		}
		if(left_shift == 0 && right_shift == 1)
		{
			BTPTR k3 = root, b = root->lchild->rchild;
			root = root->lchild;
			k3->lchild = b;
			root->rchild = k3;
		}								
	}
	return root;
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
    BTPTR root = new bstnode;
    root = init(root);
    int n;
    cout<<"Enter the Value of Root : ";
    cin>>root->data;
    do {
        cout<<"Enter Number (-1 to quit) : ";
        cin>>n;
        if(n == -1)
            break;
        root = add(root, n);
    } while(n != -1);
    root = AVL(root);
    cout<<"Preorder : ";
    preorder(root);
    return 0;
}
