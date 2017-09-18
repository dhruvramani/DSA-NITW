#include <iostream>
using namespace std;

#define max_size 50
int d = 3;

struct data {
	int k1;
	char k2;
	int k3;
};
struct ktnode 
{
    ktnode *lchild, *rchild;
    data keys;
};
typedef ktnode *KTPTR;


KTPTR init(KTPTR node)
{
    node->lchild = NULL;
    node->rchild = NULL;
    return node;
}

int level = 0;
KTPTR add(KTPTR root, data newdat)
{
	if(root != NULL) {
		int old_level = ::level;
		::level = (::level + 1) % d;
		if(old_level == 0) {
			if(root->keys.k1 > newdat.k1)
				root->lchild = add(root->lchild, newdat);
			else 
				root->rchild = add(root->rchild, newdat);
		} else if(old_level == 1) {
			if(root->keys.k2 > newdat.k2)
				root->lchild = add(root->lchild, newdat);
			else 
				root->rchild = add(root->rchild, newdat);
		} else {
			if(root->keys.k3 > newdat.k3)
				root->lchild = add(root->lchild, newdat);
			else 
				root->rchild = add(root->rchild, newdat);
		}
		
	} else {
		root = new ktnode;
		root = init(root);
		root->keys = newdat;
	}
	return root;
}

int level_2 = 0;
int search(KTPTR root, data to_search)
{
	if(root != NULL)
	{
		if(to_search.k1 == root->keys.k1 && to_search.k2 == root->keys.k2 && to_search.k3 == root->keys.k3)
			return 1;
		int old_level = level_2;
		level_2 = (level_2 + 1)%d;
		if(old_level == 0) {
			if(root->keys.k1 > to_search.k1)
				return search(root->lchild, to_search);
			else 
				return search(root->rchild, to_search);
		} else if(old_level == 1) {
			if(root->keys.k2 > to_search.k2)
				return search(root->lchild, to_search);
			else 
				return search(root->rchild, to_search);
		} else {
			if(root->keys.k3 > to_search.k3)
				return search(root->lchild, to_search);
			else 
				return search(root->rchild, to_search);
		}
	}
	return 0;
}

void preorder(KTPTR node)
{
    if(node != NULL)
    {
    	cout<<node->keys.k1<<" "<<node->keys.k2<<" "<<node->keys.k3<<" | ";
        preorder(node->lchild);
        preorder(node->rchild);
    }
}

int main()
{
    data a[] = {{1, 'a', 20}, {10, 'c', 2}, {31, 'f', 19}, {24, 'g', 12}, {7, 'k', 91}}, to_search = {7, 'k', 91};
    KTPTR root = NULL;
    for(int i=0; i<5; i++)
    {
		::level = 0;
		root = add(root, a[i]);
	}
    preorder(root);
    cout<<endl<<search(root, to_search);
    return 0;
}
