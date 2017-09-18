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

BTPTR add(BTPTR root, int k)
{
    if(root != NULL) {
        if(k < root->data)
            root->lchild = add(root->lchild, k);
        else 
            root->rchild = add(root->rchild, k);
    } else {
        root = new bstnode;
        root = init(root);
        root->data = k;
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

BTPTR search(BTPTR root, int to_search)
{
    if(root != NULL)
    {
        if(root->data == to_search)
            return root;
        else if(to_search < root->data)
            return search(root->lchild, to_search);
        else 
            return search(root->rchild, to_search);
    }
    return NULL;
}

BTPTR preorder_add(BTPTR root, BTPTR node, int k)
{
    if(node != NULL)
    {
        if(node->data != k)
        {
            if(k < root->data)
                root->lchild = add(root->lchild, node->data);
            else
                root->rchild = add(root->rchild, node->data);
        }
        node->lchild = preorder_add(root, node->lchild, k);
        node->rchild = preorder_add(root, node->rchild, k);
    }
    return node;
}

BTPTR splay(BTPTR root, int k)
{
    //BTPTR node = search(root, k);
    BTPTR new_root = NULL;
    new_root = add(new_root, k);
    new_root = preorder_add(new_root, root, k);
    return new_root;
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
    do {
        cout<<"Enter Number to Splay (-1 to quit) : ";
        cin>>n;
        if(n == -1)
            break;
        root = splay(root, n);
        preorder(root);
        cout<<"\n";
    } while(n != -1);
    return 0;
}
