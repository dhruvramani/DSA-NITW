#include <iostream>
using namespace std;

#define max_size 50
struct lnode 
{
    int data;
    lnode *down;
};

struct mlnode 
{
    lnode *down;
    mlnode *next;
};

typedef mlnode *mlptr;
typedef lnode *lptr;

int pow(int x, int p) {
  if (p == 0) return 1;
  if (p == 1) return x;
  return x * pow(x, p-1);
}

mlptr radix_add(mlptr m, int number, int base)
{
    mlptr l = m;
    int index = (number % pow(10, base)) / pow(10, base-1), tag=0;
    while(tag++ != index)
        l = l->next;
    if(l->down == NULL)
    {   
        l->down = new lnode;
        lptr k = l->down;
        k->data = number;
        k->down = NULL;
    } else {
        lptr k = l->down;
        while(k->down != NULL)
            k = k->down;
        k->down = new lnode;
        k = k->down;
        k->data = number;
        k->down = NULL;
    } 
    return m;
}

mlptr radix_remove(int a[], mlptr m)
{   
    int count = 0;
    mlptr k = m;
    for(int i=0; i<10; i++)
    {
        if(k->down != NULL)
        {
            lptr l = k->down;
            while(l != NULL)
            {
                a[count++] = l->data;
                lptr p = l;
                l = l->down;
                p = NULL;
            }
        }
        k = k->next;
    }
    return m;
}

mlptr create_arch(mlptr m)
{
    m = new mlnode;
    mlptr l = m;  
    for(int i=0; i<10; i++)
    {
        l->down = NULL;
        l->next = new mlnode;
        l = l->next;
    }
    return m;
}

void radix_sort(int a[], int n, int base, mlptr m)
{
    int go = 0, j=0;
    for(int i=0; i<n; i++)
        if((a[i]/pow(10, base)) != 0)
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
    mlptr m = NULL;
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
    return 0;
}