#include <iostream>
using namespace std;

#define d 1

struct blnode 
{
    int keys[2*d + 1], keys_count;
    blnode *pptr, **children;
};
typedef blnode *BLPTR;

BLPTR init(BLPTR node)
{
    node->keys_count = -1;
    node->pptr = NULL;
    node->children = new blnode*[2*d + 2];
    for(int i=0; i<2*d+2; i++)
        node->children[i] = NULL;
    for(int i=0; i<2*d + 1; i++)
        node->keys[i] = -1;
    return node;
}

int index(int a[], int n, int b)
{
    for(int i=0; i<n; i++)
        if(a[i] == b)
            return i;
    return -1;
}

void sort_it(int a[], int n)
{
    for(int i=0; i<n-1; i++)
        for(int j=0; j<n-i-1; j++)
            if(a[j] > a[j+1])
            {
                int k = a[j];
                a[j] = a[j+1];
                a[j+1] = k;
            }
}

BLPTR basic_add(BLPTR root, int a)
{
    if(root != NULL) 
    {
        root->keys[++root->keys_count] = a;
        sort_it(root->keys, root->keys_count);
    }
    return root;
}

BLPTR search(BLPTR root, int a)
{
    if(root != NULL)
    {
        for(int i=0; i<root->keys_count+1; i++)
            if(a == root->keys[i])
                return root;
        int cont = 0;
        for(int i=0; i<2*d+1 && cont == 0; i++)
            if(root->children[i] != NULL)
                cont = 1;
        if(cont == 0)
            return root;
        else {
            if(a < root->keys[0] && root->children[0])
                return search(root->children[0], a);
            else if(a > root->keys[root->keys_count] && root->children[root->keys_count+1])
                return search(root->children[root->keys_count+1], a);
            else 
                for(int i=0; root->keys_count - 1; i++)
                    if(a > root->keys[i] && a < root->keys[i + 1] && root->children[i+1])
                        return search(root->children[i+1], a);
        }
    }
    return NULL;
}

BLPTR overflow_create(BLPTR node, int a)
{
    int i=0, j;
    node->keys_count = 2*d+1;
    for (j=node->keys_count-2; j >= 0  && node->keys[j] > a; j--)
       node->keys[j+1] = node->keys[j];
    node->keys[j+1] = a;
    for (i=node->keys_count-2; i >= 0  && i >= j+2; i--)
        if(node->children[j] != NULL)
            node->children[j+1] = node->children[j];
    node->children[i+1] = NULL;
    return node;
}

int root_count = 0;
BLPTR add(BLPTR root, int a, int root_add=0)
{
    if(root != NULL)
    {
        BLPTR node;
        if(root->keys_count != -1 && root_add == 0)
            node = search(root, a);
        else 
            node = root;
        if(node->keys_count == 2*d - 1) { 
            ::root_count = 1;
            BLPTR overflow = overflow_create(node, a), parent = node->pptr, old_parent = node->pptr;
            int mid = overflow->keys[overflow->keys_count/2];
            BLPTR node1 = new blnode, node2 = new blnode;
            node2 = init(node2);
            node1 = init(node1);
            node1->pptr = parent;
            node2->pptr = parent;
            node1->children[0] = overflow->children[0];
            int i=0;
            for(; overflow->keys[i] < mid; i++)
            {
                node1 = basic_add(node1, overflow->keys[i]);
                node1->children[i+1] = overflow->children[i+1];
            }
            for(int j=i+1; j<overflow->keys_count; j++)
            {
                node2 = basic_add(node2, overflow->keys[j]);
                node2->children[j-i-1] = overflow->children[j];
            }
            if(parent == NULL)
            {
                parent = new blnode;
                parent = init(parent);
            }
            root = add(parent, mid, 1);
            parent = search(root, mid);
            i = index(parent->keys, parent->keys_count+1, mid);
            parent->children[i] = node1;
            parent->children[i+1] = node2;
            node1->pptr = parent;
            node2->pptr = parent;
            node = parent;
        } else  {
            if(root_add == 1)
                node = root;
            if(::root_count == 0 || root_add == 1)
            {
                node = basic_add(node, a);
                sort_it(node->keys, node->keys_count+1);
            } else {
                node = search(root, a);
                node = basic_add(node, a);
                sort_it(node->keys, node->keys_count+1);
            }
            if(root_add == 1)
                return root;
        }
        while(node->pptr != NULL)
            node = node->pptr;
        return node;
    }
    return NULL;
}

void preorder(BLPTR node)
{
    if(node != NULL)
    {
        for(int i=0; i<=node->keys_count+1; i++)
            if(node->keys[i] != -1)
                cout<<node->keys[i]<<" ";

        int count = 0;
        for(int i=0; i<=node->keys_count; i++)
            if(node->children[i] != NULL)
                count++;
        if(count != 0)
            cout<<endl;
        
        for(int i=0; i<=node->keys_count+1; i++)
            if(node->children[i])
                preorder(node->children[i]);
    }
}

int main()
{
    int a;
    BLPTR root = new blnode;
    root = init(root);
    do {
        cout<<"Enter a value (-1 to quit) : ";
        cin>>a;
        if(a != -1)
        {
            root = add(root, a);
            preorder(root);
            cout<<"\n\n";
        }
    } while(a != -1);
    preorder(root);
}