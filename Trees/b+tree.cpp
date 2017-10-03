#include <iostream>
using namespace std;

#define d 1

struct blnode 
{
    int type; // 0 : Leaf, 1 : Index
    int keys[2*d + 1], record_keys[2*d + 1], keys_count;
    blnode *pptr, **children, *sibling;
};
typedef blnode *BLPTR;

BLPTR init(BLPTR node)
{
    node->keys_count = -1;
    node->pptr = NULL;
    node->sibling = NULL;
    node->type = 0;
    node->children = new blnode*[2*d + 2];
    for(int i=0; i<2*d+2; i++)
        node->children[i] = NULL;
    for(int i=0; i<2*d + 1; i++)
    {
        node->record_keys[i] = -1;
        node->keys[i] = -1;
    }
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

BLPTR basic_add(BLPTR root, int a, int is_parent=0)
{
    if(root != NULL) 
    {
        if(is_parent == 0 || root->type == 0)
        {
            int i;
            for (i=root->keys_count; i >= 0  && root->keys[i] > a; i--)
                root->keys[i+1] = root->keys[i];
            root->keys[i+1] = a;
            root->record_keys[root->keys_count+1] = root->record_keys[root->keys_count];
            for (i=root->keys_count; i >= 0  && root->keys[i] > a; i--)
                root->record_keys[i+1] = root->record_keys[i];
            root->keys_count++;
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

BLPTR return_root(BLPTR node)
{
    while(node->pptr != NULL)
        node = node->pptr;
    return node;
}

BLPTR search(BLPTR root, int data){
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

BLPTR overflow_create(BLPTR node, int a)
{
    BLPTR overflow = new blnode;
    overflow = init(overflow);
    overflow->type = node->type;
    int i;
    for(i=0; i<node->keys_count + 1 && node->keys[i] < a; i++)
    {
        overflow = basic_add(overflow, node->keys[i]);
        if(node->type == 1)
            overflow->children[i] = node->children[i];
        else
            overflow->record_keys[i] = node->record_keys[i];
    }
    if(i < 2*d + 1)
    {
        i++;
        if(node->type == 1)
            overflow->children[i] = node->children[i];
        else 
            overflow->record_keys[i] = node->record_keys[i];
        overflow = basic_add(overflow, a);
        for(int j=i-1; node->keys[j] != -1; i++, j++)
        {
            overflow = basic_add(overflow, node->keys[j]);
            if(node->type == 1)
                overflow->children[i] = node->children[j];   
            else 
                overflow->record_keys[i] = node->record_keys[i];
        }
    }
    overflow->keys_count++;
    return overflow;
}

BLPTR add(BLPTR root, int a, int is_parent=0, BLPTR child1=NULL, BLPTR child2=NULL)
{
    if(root != NULL)
    {
        int leaf = 1;
        if(root->type != 0)
            for(int i=0; i<2*d+2 && leaf == 1; i++)
                if(root->children[i] != NULL)
                    leaf = 0;
        if(leaf == 0 && is_parent == 0)
            root = search(return_root(root), a);
        if(root->keys_count == 2*d -1)
        {
            BLPTR overflow = overflow_create(root, a), parent = root->pptr, node2 = new blnode;
            root = init(root);
            root->type = overflow->type;
            root->pptr = parent;
            node2 = init(node2);
            node2->type = overflow->type;
            int mid = overflow->keys[overflow->keys_count/2], i=0, j=0;
            for(; overflow->keys[i] < mid; i++)
            {
                root = basic_add(root, overflow->keys[i]);
                if(overflow->type == 1)
                    root->children[i] = overflow->children[i];
                else
                    root->record_keys[i] = overflow->record_keys[i];
            }
            if(overflow->type == 1)
                root->children[i] = overflow->children[i];
            else
                root->record_keys[i] = overflow->record_keys[i];
            i++;
            node2 = basic_add(node2, mid);
            for(j=i; j<overflow->keys_count; j++)
            {
                node2 = basic_add(node2, overflow->keys[j]);
                if(overflow->type == 1)
                    node2->children[j-i] = overflow->children[j];
                else
                    node2->record_keys[j-i] = overflow->record_keys[j];
            }
            parent = add(parent, mid, 1, root, node2);
            root->pptr = parent;
            node2->pptr = parent;
            if(node2->keys[0] == a)
                root = node2;
        } else
            root = basic_add(root, a, is_parent);
    } else {
        root = new blnode;
        root = init(root);
        root = basic_add(root, a, is_parent);
        if(is_parent == 1)
            root->type = 1;
    }
    if(is_parent == 1)
    {
        int i;
        for(i=0; i<=root->keys_count; i++)
           if(root->keys[i] == a)
                break;
        root->type = 1;
        root->children[i] = child1;
        root->children[i+1] = child2;
        if(child1->type == 0 && child2->type == 0)
            child1->sibling = child2;
    }
    return root;
}

void inorder(BLPTR node)
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

void preorder(BLPTR node)
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
    BLPTR root = new blnode;
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