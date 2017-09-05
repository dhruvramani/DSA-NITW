#include <iostream>
using namespace std;

#define max_size 50

struct ttnode 
{
    ttnode *lchild, *rchild;
    char k1;
    int k2;
};
typedef ttnode *TTPTR;

TTPTR init(TTPTR node)
{
    node->lchild = NULL;
    node->rchild = NULL;
    return node;
}

int height(TTPTR node)
{
    if(node == NULL)
        return -1;
    int lh = height(node->lchild), rh = height(node->rchild);
    if(lh > rh)
        return 1 + lh;
    return 1 + rh;
}

TTPTR AVL(TTPTR root)
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
            
            TTPTR k1 = root, b = root->rchild->lchild;
            root = root->rchild;
            k1->rchild = b;
            root->lchild = k1;
        }
        if(left_shift == 0 && right_shift == 1)
        {
            TTPTR k3 = root, b = root->lchild->rchild;
            root = root->lchild;
            k3->lchild = b;
            root->rchild = k3;
        }                               
    }
    return root;
}

// Insert according to BST and then do left/right rotation like normal AVL. 
// This ensures heap property is maintained.
TTPTR add(TTPTR root, TTPTR to_add)
{
    TTPTR node = root, old = root;
    while(node != NULL)
    {
        old = node;
        if(to_add->k1 < node->k1)
            node = node->lchild;
        else node = node->rchild;
    }
    if(to_add->k1 < old->k1)
        old->lchild = to_add;
    else 
        old->rchild = to_add;
    root = AVL(root);
    return root;
}

void preorder(TTPTR node)
{
    if(node != NULL)
    {
        cout<<node->k1<<" "<<node->k2<<"   ";
        preorder(node->lchild);
        preorder(node->rchild);
    }
}

int main()
{
    char a[] = "GBAHECD";
    int b[] = {4, 7, 10, 5, 24, 25, 9};
    TTPTR root = new ttnode;
    root = init(root);
    root->k1 = a[0];
    root->k2 = b[0];
    for(int i=1; i<7; i++)
    {
        TTPTR node = new ttnode;
        node = init(node);
        node->k1 = a[i];
        node->k2 = b[i];
        root = add(root, node);
    }
    preorder(root);
    return 0;
}