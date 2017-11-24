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

BLPTR return_root(BLPTR node)
{
    while(node->pptr != NULL)
        node = node->pptr;
    return node;
}

BLPTR basic_add(BLPTR root, int a, int is_parent=0)
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

BLPTR leftsibling(BLPTR node, int a)
{
    if(node != NULL && node->pptr !=NULL)
    {
        int i=0;
        BLPTR parent = node->pptr;
        for(; i<parent->keys_count+1; i++)
            if(parent->children[i] == node)
                break;
        if(parent->children[i-1] != NULL)
        {
            if(parent->children[i-1]->keys_count < 2*d - 1)
            {
                cout<<"Left!"<<endl;
                BLPTR overflow =  overflow_create(node, a), node1 = new blnode;
                node1 = init(node1);
                parent->children[i-1] = basic_add(parent->children[i-1], parent->keys[i-1]);
                parent->keys[i-1] = overflow->keys[0];
                for(int i=1; i<overflow->keys_count-1; i++)
                    node1 = basic_add(node1, overflow->keys[i]);
                for(int i=0; i<2*d+2; i++)
                    node1->children[i] = overflow->children[i];
                node1->pptr = parent;
                parent->children[i] = node1;
                return return_root(node1);
            } else 
                return NULL;
        }
    }
    return NULL;
}

BLPTR rightsibling(BLPTR node, int a)
{
    if(node != NULL && node->pptr !=NULL)
    {
        int i=0;
        BLPTR parent = node->pptr;
        for(; i<parent->keys_count+1; i++)
            if(parent->children[i] && parent->children[i] == node)
                break;
        if(parent->children[i+1] != NULL)
        {
            if(parent->children[i+1]->keys_count < 2*d - 1)
            {
                cout<<"Right!"<<endl;
                BLPTR overflow =  overflow_create(node, a), node1 = new blnode;
                node1 = init(node1);
                parent->children[i+1] = basic_add(parent->children[i+1], parent->keys[i]);
                parent->keys[i] = overflow->keys[overflow->keys_count-1];
                for(int i=0; i<overflow->keys_count-1; i++)
                    node1 = basic_add(node1, overflow->keys[i]);
                for(int i=0; i<2*d+2; i++)
                    node1->children[i] = overflow->children[i];
                node1->pptr = parent;
                parent->children[i] = node1;
                return return_root(node1);
            } else 
                return NULL;
        }
    }
    return NULL;
}

BLPTR add(BLPTR root, int a, int is_parent=0, BLPTR child1=NULL, BLPTR child2=NULL)
{
    if(root != NULL)
    {
        int leaf = 1;
        for(int i=0; i<2*d+2 && leaf == 1; i++)
            if(root->children[i] != NULL)
                leaf = 0;
        if(leaf == 0 && is_parent == 0)
            root = search(return_root(root), a);
        if(root->keys_count == 2*d - 1) { 
            BLPTR left = leftsibling(root, a), right = NULL;
            if(left == NULL)
                right = rightsibling(root, a);
            if(right == NULL && left == NULL)
            {
                cout<<"Splitting\n";
                BLPTR overflow = overflow_create(root, a), parent = root->pptr, node2 = new blnode;
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
            }
        } else  
            root = basic_add(root, a, is_parent);
    } else {
        root = new blnode;
        root = init(root);
        root = basic_add(root, a);
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

void inorder(BLPTR node)
{
    
    for(int i=0; i<=node->keys_count+1; i++)
        {
            if(node->children[i])
                inorder(node->children[i]);
            if(node->keys[i] != -1)
                cout<<node->keys[i]<<" ";
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