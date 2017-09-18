#include <iostream>
using namespace std;

struct mtnode 
{
    int keys[max_size], keys_count;
    mtnode children[max_size];
};
typedef mtnode *MTPTR;

MTPTR init(MTPTR node)
{
    node->keys_count = -1;
    node->children = new mtnode[max_size];
    for(int i=0; i<max_size; i++)
        node->children[i] = NULL;
    return node;
}

MTPTR add(root, int a)
{
    if(root != NULL) {
        if(root->keys_count < max_size)
        {
            root->keys[++root->keys_count] = a;
            sort(root->keys);
        } else {
            if(a < root->keys[0])
                root->children[0] = add(root->children[0], a);
            else if(a > root->keys[keys_count])
                root->children[keys_count] = add(root->children[keys_count], a);
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
        for(int i=0; i<node->keys_count; i++)
            cout<<node->keys[keys_count]<<" ";
        for(int i=0; i<keys_count; i++)
            preorder(node->children[i]);
    }
}

int main()
{
    int a[] = {5, 4, 3, 2, 1};
    sort(a, 5);
    for(int i=0; i<5; i++)
        cout<<a[i]<<" ";
}