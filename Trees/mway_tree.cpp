#include <iostream>
using namespace std;

#define max_size 5

struct mtnode 
{
    int keys[max_size], keys_count;
    mtnode **children;
};
typedef mtnode *MTPTR;

MTPTR init(MTPTR node)
{
    node->keys_count = -1;
    node->children = new mtnode*[max_size];
    for(int i=0; i<max_size; i++)
        node->children[i] = NULL;
    for(int i=0; i<max_size; i++)
        node->keys[i] = -1;
    return node;
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

MTPTR add(MTPTR root, int a)
{
    if(root != NULL) {
        if(root->keys_count < max_size-1)
        {
            root->keys[++root->keys_count] = a;
            sort_it(root->keys, root->keys_count);
        } else {
            if(a < root->keys[0])
                root->children[0] = add(root->children[0], a);
            else if(a > root->keys[root->keys_count])
                root->children[root->keys_count] = add(root->children[root->keys_count], a);
            else 
                for(int i=0; root->keys_count - 1; i++)
                    if(a > root->keys[i] && a < root->keys[i + 1])
                    {
                        root->children[i+1] = add(root->children[i+1], a);
                        break;
                    }
        }
    } else {
        root = new mtnode;
        root = init(root);
        root->keys[++root->keys_count] = a;
    }
    return root;
}

void preorder(MTPTR node)
{
    if(node != NULL)
    {
        for(int i=0; i<=node->keys_count; i++)
            if(node->keys[i] != -1)
                cout<<node->keys[i]<<" ";
        
        int count = 0;
        for(int i=0; i<=node->keys_count; i++)
            if(node->children[i] != NULL)
                count++;
        if(count != 0)
            cout<<endl;
        
        for(int i=0; i<=node->keys_count; i++)
            preorder(node->children[i]);
    }
}

int main()
{
    int n, a;
    MTPTR root = NULL;
    cout<<"Enter the number of elements to be added : ";
    cin>>n;
    for(int i=0; i<n; i++)
    {
        cout<<"Enter a value : ";
        cin>>a;
        root = add(root, a);
    }
    preorder(root);
}