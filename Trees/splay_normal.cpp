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

BTPTR splay(BTPTR root, int k)
{
    if(root != NULL)
    {
        int shift = -1;
        //shift: right rotation-0, left rotation-1
        if(root->lchild && root->lchild->data == k)
            shift = 0;
        else if(root->rchild && root->rchild->data == k)
            shift = 1;
    
        if(shift == -1)
        {
            if(k < root->data)
                root->lchild = splay(root->lchild, k);
            else
                root->rchild = splay(root->rchild, k);
            root = splay(root, k);
        }
        if(shift == 1)
        {        
            BTPTR k1 = root, b = root->rchild->lchild;
            root = root->rchild;
            k1->rchild = b;
            root->lchild = k1;
        }
        if(shift == 0)
        {
            BTPTR k3 = root, b = root->lchild->rchild;
            root = root->lchild;
            k3->lchild = b;
            root->rchild = k3;
        }
    }
    return root;
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
