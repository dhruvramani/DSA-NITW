#include <iostream>
#include <cstring>
using namespace std;

#define n 3
char alpha[n+1] = {'A', 'B', 'C', ' '};

struct tnode
{
    int tag;
    tnode **ptr;
};

typedef tnode *TPTR;

int c_count = 0, f_count = 0, d_count = 0 , p_count;
char p_array[n+1], f_array[n+1];
void init_vars()
{
    ::c_count = 0;
    ::d_count = 0;
    ::f_count = 0;
    ::p_count = 0;
}

TPTR init_index(TPTR node)
{
    node->tag = 0;
    node->ptr = new tnode*[n+1];
    for(int i=0; i<n+1; i++)
        node->ptr[i] = NULL;
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
        node = init_index(node);
    }

    int ind = index(alpha, key[::c_count++], n+1);
    if(ind == -1)
        ind = n;
    if(strlen(key) + 1 == ::c_count)
        node->tag = 1;
    else
    {
        node->tag = 0;
        node->ptr[ind] = create(node->ptr[ind], key);
    }
    return node;
}


void print(TPTR t)
{
    if(t != NULL)
    {
        if(t->tag == 1)
        {
            for(int i=0; i< ::p_count; i++)
                cout<<p_array[i];
            cout<<endl;
        } else {
            for(int i=0; i < n+1; i++)
                if(t->ptr[i] != NULL)
                {
                    p_array[::p_count++] = alpha[i];
                    print(t->ptr[i]);
                    ::p_count--;
                }
        }
    }
}


int find(TPTR t, char key[])
{
    if(t != NULL)
    {
        if(t->tag == 1 && !strcmp(f_array, key))
            return 1;
        
        if(f_count >= strlen(key))
            return 0;

        int ind = index(alpha, key[::f_count], n+1);
        if(ind == -1)
            ind = n;
        f_array[f_count++] = alpha[ind];
        return find(t->ptr[ind], key);
    }  
}

int main()
{
    TPTR node = new tnode;
    node = init_index(node);
    init_vars();
    node = create(node, "AAB");
    init_vars();
    node = create(node, "AAC");
    init_vars();
    node = create(node, "BAC");
    init_vars();
    node = create(node, "BBA");
    init_vars();
    print(node);
    return 0;
}