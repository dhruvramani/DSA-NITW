#include <iostream>
#include <cstring>
using namespace std;

#define n 3
char alpha[n+1] = {'A', 'B', 'C', ' '};

struct tnode
{
    int tag;
    tnode **ptr;
    char key[n];
};

typedef tnode *TPTR;

int c_count = 0, f_count = 0, d_count = 0;
void init_vars()
{
    ::c_count = 0;
    ::d_count = 0;
    ::f_count = 0;
}

TPTR init_index(TPTR node)
{
    node->tag = 1;
    node->ptr = new tnode*[n+1];
    for(int i=0; i<n+1; i++)
        node->ptr[i] = NULL;
    return node;
}

TPTR init_leaf(TPTR node, char *key)
{
    node->tag = 0;
    strcpy(node->key, key);
    return node;
}

int index(char a[], char m, int l)
{
    for(int i=0; i<l; i++)
        if(a[i] == m)
            return i;
    return -1;
}

TPTR create(TPTR node, char key[])
{
    if(node == NULL) 
    {
        node = new tnode;
        node = init_leaf(node, key);
    }
    if(node->tag == 1) 
    {
        int ind = index(alpha, key[::c_count++], n+1);
        if(ind == -1)
            ind = n;
        if(node->ptr[ind] == NULL || node->ptr[ind]->tag == 1)
            node->ptr[ind] = create(node->ptr[ind], key);
        else { 
            TPTR leaf_node = node->ptr[ind];
            int leaf_index = index(alpha, leaf_node->key[::c_count], n+1);
            node->ptr[ind] = new tnode;
            node->ptr[ind] = init_index(node->ptr[ind]);
            node->ptr[ind]->ptr[leaf_index] = leaf_node;
            node->ptr[ind] = create(node->ptr[ind], key);
        }
    }
    return node;
}

void print(TPTR t)
{
    if(t->tag == 0)
        cout<<t->key<<" ";
    else {
        for(int i=0; i<n+1; i++)
            if(t->ptr[i])
            {
                cout<<::alpha[i]<<" ( ";
                print(t->ptr[i]);
                cout<<" ) ";
            }
    }
}

int find(TPTR t, char key[])
{
    if(t == NULL)
        return 0;
    if(t->tag == 0) {
        if(!strcmp(key, t->key))
            return 1;
        return 0;
    }
    int ind = index(alpha, key[::f_count++], n+1);
    if(ind == -1)
        ind = n;
    return find(t->ptr[ind], key);
}

TPTR delete_key(TPTR t, char key[])
{
    if(t->tag == 0)
    {
        t = NULL;
        return t;
    }

    int ind = index(alpha, key[::f_count++], n+1);
    if(ind == -1)
        ind = n;
    t->ptr[ind] = delete_key(t->ptr[ind], key);
    int is_null = 1;
    for(int i=0; i<n+1 && is_null == 1; i++)
        if(t->ptr[i] != NULL)
            is_null = 0;
    if(is_null == 1)
        t = NULL;
    return t;
}

int main()
{
    TPTR node = new tnode;
    node = init_index(node);
    init_vars();
    node = create(node, "AAB");
    init_vars();
    node = create(node, "ABBBC");
    init_vars();
    node = create(node, "BAA");
    init_vars();
    node = create(node, "BCCAA");
    print(node);
    init_vars();
    cout<<find(node, "BCCAA")<<endl;
    init_vars();
    node = delete_key(node, "BCCAA");
    cout<<find(node, "BCCAA")<<endl;
    return 0;
}