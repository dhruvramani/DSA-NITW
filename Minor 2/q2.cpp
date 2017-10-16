#include <iostream>
using namespace std;

struct lnode 
{
    int data;
    lnode *next;
};

typedef lnode *LTPTR;

LTPTR get_mid(LTPTR node, int s, int n)
{
    int i=0;
    while(i < (s+n)/2 && node->next)
    {
        node = node->next;
        i++;
    }
    return node;
}


LTPTR add(LTPTR l, int k)
{

    if(l == NULL)
    {
        l = new lnode;
        l->data = k;
        l->next = NULL;
    } else {
        LTPTR t = l;
        while(t->next != NULL)
            t = t->next;
        t->next = new lnode;
        t->next->next = NULL;
        t->next->data = k;
        t = t->next;
    }
    return l;
}

void quicksort(LTPTR node, int low, int high)
{
    if(node == NULL || node->next == NULL)
        return ;
    int mid = (low + high)/2, count=0;
    LTPTR pivot = node, l = node->next, h = get_mid(node, low, high); 
    while(count < mid)
    {
        while(l->data < pivot->data && l->next)
            l = l->next;
        while(h->data > pivot->data && h->next)
            h = h->next;
        
        int k = l->data;
        l->data = h->data;
        h->data = k;
        count++;
    }
    h = h->next;
    int k = pivot->data;
    pivot->data = l->data;
    quicksort(node, low, mid+1);
    quicksort(get_mid(node, low, high), mid, high);
}

int main()
{   
    int a[] = {15, 8, 1, 27, 32, 9, 4, 22, 11};
    LTPTR node = NULL;
    for(int i=0; i<9; i++)
        node = add(node, a[i]);
    quicksort(node, 0, 9);
    for(int i=0; node; i++)
    {
        cout<<node->data<<" ";
        node = node->next;
    }
    return 0;
}