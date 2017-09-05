#include <iostream>
using namespace std;

#define max_size 50

struct gtnode 
{
    gtnode *fchild, *nsibling;
    char data;
};
typedef gtnode *GTPTR;

GTPTR init(GTPTR node)
{
    node->fchild = NULL;
    node->nsibling = NULL;
    return node;
}

GTPTR create(GTPTR head, char a[])
{
    GTPTR run = head, old[max_size];
    int old_count = 0;
    for(int i=0; a[i]; i++)
        if(a[i] == '(')
        {
            run->fchild = new gtnode;
            old[old_count++] = run;
            run = run->fchild;
            run = init(run);
        } else if (a[i] == ')')
        {
            run->nsibling = NULL;
            run = old[--old_count];
            run->nsibling = new gtnode;
            run = run->nsibling;
        }
        else if(a[i] == ',' || a[i] == ' ');
        else {      
            run->data = a[i];
            if(a[i+2] != '(')
            {
                run->nsibling = new gtnode;
                run = run->nsibling;
                run = init(run);
            }
        }
    run->nsibling = NULL;
    return head;
}

void preorder(GTPTR root)
{
    if(root != NULL)
    {
        cout<<root->data<<" ";
        preorder(root->fchild);
        preorder(root->nsibling);
    }
}

int main()
{
    char a[] = "A,(B,(L, M),C,D,(J, K))";
    GTPTR root = new gtnode;
    root = init(root);
    root = create(root, a);
    preorder(root);
    return 0;
}