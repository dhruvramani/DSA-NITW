#include <iostream>
using namespace std;

#define max_size 50
struct mlnode 
{
    int tag;
    mlnode *down;
    mlnode *next;
};

typedef mlnode *mlptr;

int pow(int x, int p) {
  if (p == 0) return 1;
  if (p == 1) return x;
  return x * pow(x, p-1);
}

mlptr radix_add(mlptr m, int number, int base)
{
    mlptr l = m;
    int index = (number % pow(10, base)) / pow(10, base-1), count = 0;
    while(l->tag != index)
        l = l->next;
    while(l->down != NULL)
        l = l->down;
    l->down = new mlnode;
    l = l->down;
    l->tag = number;
    l->next = NULL;
    l->down = NULL;
    return m;
}

mlptr radix_remove(int a[], mlptr m)
{   
    int count = 0;
    mlptr k = m;
    for(int i=0; i<10; i++)
    {
        mlptr l = k->down;
        while(l != NULL)
        {
            a[count++] = l->tag;
            mlptr p = l;
            l = l->down;
            p = NULL;
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
        l->tag = i;
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