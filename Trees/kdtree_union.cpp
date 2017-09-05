#include <iostream>
using namespace std;

#define max_size 50
int d = 1, tags[max_size];

union data {
	int k1;
	char k2;
};

struct ktnode 
{
    ktnode *lchild, *rchild;
    data keys[max_size];
};
typedef ktnode *KTPTR;

KTPTR init(KTPTR node)
{
    node->lchild = NULL;
    node->rchild = NULL;
    return node;
}

int level = 0;
KTPTR add(KTPTR root, data newdat[])
{
	if(root != NULL) {
		int old_level = ::level;
		::level = (::level + 1) % d;
		if(tags[old_level] == 0) {
			if(root->keys[old_level].k1 > newdat[old_level].k1)
				root->lchild = add(root->lchild, newdat);
			else 
				root->rchild = add(root->rchild, newdat);
		} else if(tags[old_level] == 1) {
			if(root->keys[old_level].k2 > newdat[old_level].k2)
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
int search(KTPTR root, data to_search[])
{
	if(root != NULL)
	{
		int to_return = 1;
		for(int i=0; i<d; i++)
		{
			if(tags[i] == 0)
			{
				if(root->keys[i].k1 != to_search[i].k1)
					to_return = 0;		
			} else if(tags[i] == 1)
			{
				if(root->keys[i].k2 != to_search[i].k2)
					to_return = 0;
			}
		}
		if(to_return == 1)
			return 1;
		int old_level = level_2;
		level_2 = (level_2 + 1)%d;
		if(tags[old_level] == 0) {
			if(root->keys[old_level].k1 > to_search.k1)
				return search(root->lchild, newdat);
			else 
				return search(root->rchild, newdat);
		} else if(tags[old_level] == 1) {
			if(root->keys[old_level].k2 > to_search.k2)
				return search(root->lchild, newdat);
			else 
				return search(root->rchild, newdat);
		}
	}
	return 0;
}

void preorder(KTPTR node)
{
    if(node != NULL)
    {
    	for(int i=0; i<d; i++) {
    		if(tags[i] == 0)
    			cout<<node->keys[i].k1<<" ";
    		else
    			cout<<node->keys[i].k2<<" ";
    	}
    	cout<<" | ";
        preorder(node->lchild);
        preorder(node->rchild);
    }
}

int main()
{
	cout<<"Enter Number of Keys (d) (<50): ";
	cin>>d;
	for(int i =0; i<d; i++)
	{
		cout<<"Do you want key ("<<i<<") to be an integer (0) or char (1) : ";
		cin>>tags[i];
	}
	int n;
	cout<<"Enter No. of Elements : ";
	cin>>n;
    KTPTR root = NULL;
    for(int i=0; i<n; i++)
    {
    	data a[max_size];
    	for(int j=0; j<d; j++)
    	{
    		if(tags[j] == 0) {
    			cout<<"Enter int : ";
    			cin>>a[j].k1;
    		} else if(tags[j] == 1) {
    			cout<<"Enter char : ";
    			cin>>a[j].k2;
    		}    		
    	}
		::level = 0;
		root = add(root, a);
	}
    preorder(root);
    data to_search[max_size];
    cout<<"To Search"
    for(int j=0; j<d; j++)
    {
    	if(tags[j] == 0) {
    		cout<<"Enter int : ";
    		cin>>to_search[j].k1;
    	} else if(tags[j] == 1) {
    		cout<<"Enter char : ";
    		cin>>to_search[j].k2;
    	}
		
    }
    cout<<endl<<search(root, to_search);
    return 0;
}
