#include <iostream>
using namespace std;

struct lnode
{
    int data;
    lnode *next;    
};

struct dlnode
{   
    int tag;
    lnode *down;
    dlnode *left, *right;
};

typedef lnode *lptr;
typedef dlnode *dlptr;

int pow(int x, int p) {
  if (p == 0) return 1;
  if (p == 1) return x;
  return x * pow(x, p-1);
}

dlptr radix_add(dlptr m, int number, int base)
{
    dlptr l = m;
    int index = (number % pow(10, base)) / pow(10, base-1), count = 0;
    while(l->tag != index)
        l = l->next;
    while(l->down != NULL)
        l = l->down;
    l->down = new lnode;
    l = l->down;
    l->data = number;
    l->next = NULL;
    return m;
}

dlptr radix_remove(int a[], mlptr m)
{   
    int count = 0;
    dlptr k = m;
    for(int i=0; i<10; i++)
    {
        lptr l = k->down;
        while(l != NULL)
        {
            a[count++] = l->data;
            lptr p = l;
            l = l->down;
            p = NULL;
        }
        k = k->next;
    }
    return m;
}

dlptr create_arch(dlptr m)
{
    m = new dlnode;
    dlptr l = m;  
    for(int i=0; i<10; i++)
    {
        l->tag = i;
        l->down = NULL;
        l->right = new mlnode;
        l->right->left = l;
        l = l->right;
    }
    return m;
}

void radix_sort(int a[], int n, int base, dlptr m)
{
    int go = 0, j=0;
    for(int i=0; i<n; i++)
        if(a[i]/pow(10, base) != 0)
            go = 1;
    if(go == 0 && base != 1)
        return ;   
    for(int i=0; i<n; i++)
        m = radix_add(m, a[i], base);
    m = radix_remove(a, m);
    radix_sort(a, n, base + 1, m);
}

int main()
{
    dlptr m = NULL;
    m = create_arch(m);
    int n, a[max_size];
    cout<<"Enter number of elements : ";
    cin>>n;
    for(int i=0; i<n; i++)
    {
        cout<<"Enter Number : ";
        cin>>a[i];
    }
    radix_sort(a, n, 1, m);
    for(int i=0; i<n; i++)
        cout<<a[i]<<" ";
    return 0;
}