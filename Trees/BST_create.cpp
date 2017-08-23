#include <iostream>
using namespace std;

struct bstnode 
{
    bstnode *lchild, *rchild;
    int data;
};
typedef bstnode *BSTPTR;

BSTPTR init(BSTPTR node)
{
    node->lchild = NULL;
    node->rchild = NULL;
    return node;
}

int pos = 0;
BSTPTR add(BSTPTR root, int k)
{
    BSTPTR node = root;
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

void preorder(BSTPTR node)
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
    BSTPTR root = new bstnode;
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
    cout<<"Preorder : ";
    preorder(root);
    return 0;
}