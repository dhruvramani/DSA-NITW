#include <iostream>
#include <cstring>
using namespace std;

#define n 4
char alpha[n+1] = {'A', 'B', 'C', 'D', ' '};

struct tnode
{
    int pos;
    tnode **ptr;
    char key[n];
};

typedef tnode *TPTR;

int c_count = 0, d_count = 0;
void init_vars()
{
    ::c_count = 0;
    ::d_count = 0;
}

TPTR init_index(TPTR node)
{
    node->pos = 0;
    node->ptr = new tnode*[n+1];
    for(int i=0; i<n+1; i++)
        node->ptr[i] = NULL;
    return node;
}

TPTR init_leaf(TPTR node, char *key)
{
    node->pos = 0;
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
        return node;
    }

    int ind = index(alpha, key[::c_count++], n+1);
    if(ind == -1)
        ind = n;

    if(node->ptr[ind] && node->ptr[ind]->pos == 0)
    {
        char old_key[n+1];
        strcpy(old_key, node->ptr[ind]->key);
        ::c_count = 0;
        while(old_key[::c_count] == key[::c_count])
            ::c_count++;
        int old_count = ::c_count;   
        node->ptr[ind] = init_index(node->ptr[ind]);
        node->ptr[ind] = create(node->ptr[ind], old_key);
        ::c_count = old_count;
        node->ptr[ind] = create(node->ptr[ind], key);
    } else if(strlen(key) + 1 == ::c_count)
        node->pos = 0;
    else
    {
        node->pos = ::c_count;
        node->ptr[ind] = create(node->ptr[ind], key);
    }
    return node;
}

void print(TPTR t)
{
    if(t->pos == 0)
        cout<<t->key;
    else {
        for(int i=0; i<n+1; i++)
            if(t->ptr[i])
            {
                cout<<::alpha[i]<<"-"<<t->pos<<" : ( ";
                print(t->ptr[i]);
                cout<<" ), ";
            }
    }
}

int find(TPTR t, char key[])
{
    if(t == NULL)
        return 0;
    if(t->pos == 0) {
        if(!strcmp(key, t->key))
            return 1;
        return 0;
    }

    int ind = index(alpha, key[t->pos-1], n+1);
    if(ind == -1)
        ind = n;
    return find(t->ptr[ind], key);
}

int main()
{
    TPTR node = new tnode;
    node = init_index(node);
    init_vars();
    node = create(node, "ABBBC");
    init_vars();
    node = create(node, "ABBBD");
    init_vars();
    print(node);
    return 0;
}