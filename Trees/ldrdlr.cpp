#include <iostream>
using namespace std;

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

int index_of(char a[], int n, char c)
{
    for(int i=0; i<n; i++)
        if(a[i] == c)
            return i;
    return -1;
}

int pos = 1;
BTPTR create(BTPTR node, char ldr[], char dlr[])
{
    if(::pos == strlen(dlr) - 1)
        return NULL;
    node->data = dlr[::pos-1];
    if((index_of(ldr, strlen(ldr), dlr[::pos-1]) == 0 && ::pos != 1) || index_of(ldr, strlen(ldr), dlr[::pos]) == index_of(ldr, strlen(ldr), dlr[::pos-1] + 1))
        node->lchild = NULL;
    else if(index_of(ldr, strlen(ldr), dlr[::pos]) == index_of(ldr, strlen(ldr), dlr[::pos-1] + 1) || (index_of(ldr, strlen(ldr), dlr[::pos-1]) == strlen(ldr) - 1 && ::pos != strlen(ldr) - 1))
        node->rchild = NULL;
    else if(index_of(ldr, strlen(ldr), dlr[::pos-1]) > index_of(ldr, strlen(ldr), dlr[::pos]))
    {
        node->lchild = new btnode;
        ::pos++;
        node->lchild = create(node->lchild, ldr, dlr);
    }
    if(index_of(ldr, strlen(ldr), dlr[::pos-1]) < index_of(ldr, strlen(ldr), dlr[::pos]))  
    {
        node->rchild = new btnode;
        ::pos++;
        node->rchild = create(node->rchild, ldr, dlr);
        if(node != NULL && node->rchild != NULL)
        cout<<node->data<<" "<<node->rchild->data<<endl;
    }
    return node;
}


void inorder(BTPTR node)
{
    if(node != NULL)
    {
        inorder(node->lchild);
        cout<<node->data<<" ";
        inorder(node->rchild);
    }
}

int main()
{
    char ldr[] = "JBMRCPLERG", dlr[] = "PBJRMCREG";
    BTPTR root = new btnode;
    root = init(root);
    root = create(root, ldr, dlr);
    inorder(root);
    return 0;
}