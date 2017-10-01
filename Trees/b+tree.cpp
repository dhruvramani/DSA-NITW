#include <iostream>
using namespace std;

#define d 1

struct indexnode 
{
    int keys[2*d + 1], keys_count;
    indexnode *pptr, **children;
};
typedef indexnode *INPTR;

INPTR init(INPTR node)
{
    node->keys_count = -1;
    node->pptr = NULL;
    node->children = new indexnode*[2*d + 2];
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

INPTR basic_add(INPTR root, int a, int is_parent=0)
{
    if(root != NULL) 
    {
        if(is_parent == 0)
        {
            root->keys[++root->keys_count] = a;
            sort_it(root->keys, root->keys_count+1);
        } else {
            int i;
            for (i=root->keys_count; i >= 0  && root->keys[i] > a; i--)
                root->keys[i+1] = root->keys[i];
            root->keys[i+1] = a;
            root->children[root->keys_count+2] = root->children[root->keys_count+1];
            for (i=root->keys_count; i >= 0  && root->keys[i] > a; i--)
                root->children[i+1] = root->children[i];
            root->keys_count++;
        }
    }
    return root;
}

INPTR return_root(INPTR node)
{
    while(node->pptr != NULL)
        node = node->pptr;
    return node;
}

INPTR search(INPTR root, int data){
    if(root != NULL)
    {
        int i=0, keys_count = root->keys_count;
        if(data < root->keys[0])
            keys_count++;
        for(i = 0; i < keys_count ; i++){
            if(data == root->keys[i])
                return root;
            if(data < root->keys[i]){
                if(root->children[i] == NULL)
                    return root;
                else
                    return search(root->children[i], data);
            }   
        }
        if(root->children[i + 1] == NULL)
            return root;
        else
            return search(root->children[root->keys_count + 1], data);
    }
    return NULL;
}

INPTR overflow_create(INPTR node, int a)
{
    INPTR overflow = new indexnode;
    overflow = init(overflow);
    int i;
    for(i=0; i<node->keys_count + 1 && node->keys[i] < a; i++)
    {
        overflow = basic_add(overflow, node->keys[i]);
        overflow->children[i] = node->children[i];
    }
    if(i < 2*d + 1)
    {
        i++;
        overflow->children[i] = node->children[i];
        overflow = basic_add(overflow, a);
        for(int j=i-1; node->keys[j] != -1; i++, j++)
        {
            overflow = basic_add(overflow, node->keys[j]);
            overflow->children[i] = node->children[j];   
        }
    }
    overflow->keys_count++;
    return overflow;
}

INPTR add(INPTR root, int a, int is_parent=0, INPTR child1=NULL, INPTR child2=NULL)
{
    if(root != NULL)
    {
        int leaf = 1;
        for(int i=0; i<2*d+2 && leaf == 1; i++)
            if(root->children[i] != NULL)
                leaf = 0;
        if(leaf == 0 && is_parent == 0)
            root = search(return_root(root), a);
        if(root->keys_count == 2*d -1)
        {
            INPTR overflow = overflow_create(root, a), parent = root->pptr, node2 = new indexnode;
            root = init(root);
            root->pptr = parent;
            node2 = init(node2);
            int mid = overflow->keys[overflow->keys_count/2], i=0;
            for(; overflow->keys[i] < mid; i++)
            {
                root = basic_add(root, overflow->keys[i]);
                root->children[i] = overflow->children[i];
            }
            root->children[i] = overflow->children[i];
            i++;
            for(int j=i; j<overflow->keys_count; j++)
            {
                node2 = basic_add(node2, overflow->keys[j]);
                node2->children[j-i] = overflow->children[j];
            }
            parent = add(parent, mid, 1, root, node2);
            root->pptr = parent;
            node2->pptr = parent;
            if(node2->keys[0] == a)
                root = node2;
        } else
            root = basic_add(root, a, is_parent);
    } else {
        root = new indexnode;
        root = init(root);
        root = basic_add(root, a, is_parent);
    }
    if(is_parent == 1)
    {
        int i;
        for(i=0; i<=root->keys_count; i++)
           if(root->keys[i] == a)
                break;
        root->children[i] = child1;
        root->children[i+1] = child2;
    }
    return root;
}

void inorder(INPTR node)
{
    if(node != NULL)
    {
        int i;
        for(i=0; i<=node->keys_count+1; i++)
        {
            if(node->children[i])
                inorder(node->children[i]);
            if(node->keys[i] != -1)
                cout<<node->keys[i]<<" ";
        }
    }
}

void preorder(INPTR node)
{
    if(node != NULL)
    {
        for(int i=0; i<=node->keys_count+1; i++)
            if(node->keys[i] != -1)
                cout<<node->keys[i]<<" ";
        int count = 0;
        for(int i=0; i<2*d+2; i++)
            if(node->children[i] != NULL)
                count++;
        if(count != 0)
            cout<<endl;

        for(int i=0; i<2*d+2; i++)
            if(node->children[i] != NULL)
                inorder(node->children[i]);
    }
}

int main()
{
    int a;
    INPTR root = new indexnode;
    root = init(root);
    do {
        cout<<"Enter a value (-1 to quit) : ";
        cin>>a;
        if(a != -1)
        {
            root = return_root(root);
            root = add(root, a);
            root = return_root(root);
            inorder(root);
            cout<<"\n\n";
        }
    } while(a != -1);
    inorder(root);
}