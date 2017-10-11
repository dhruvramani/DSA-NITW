#include <iostream>
using namespace std;

# define n 6

#define size 7
int s[size];
int find_root(int i)
{
    if(::s[i] == 0)
        return i;
    return find_root(::s[i]);
}

void uni(int i, int j)
{
    if(j == 0)
        ::s[j] = i;
    else if(i == 0)
        ::s[i] = j;
    else 
        ::s[find_root(j)] = i;
}

int find(int a, int b)
{
    return find_root(a) == find_root(b);
}

void insert(int G[][n], int row, int column, int weight=1)
{ 
    G[row-1][column-1] = weight;
}

int heap[n*n], heap_size = 0;
void heap_insert(int k)
{ 
    ::heap_size++;
    int i = ::heap_size - 1;
    ::heap[i] = k;
 
    while (i != 0 && ::heap[(i-1)/2] >= ::heap[i])
    {
       int l = ::heap[(i-1)/2];
       ::heap[(i-1)/2] = ::heap[i];
       ::heap[i] = l;
       i = (i-1)/2;
    }
}

void heapify(int i)
{
    int lchild = 2*i+1;
    int rchild = 2*i+2;
    int smallest = i;
    if(lchild < ::heap_size && ::heap[lchild] <= ::heap[i])
        smallest = lchild;
    if(rchild < ::heap_size && ::heap[rchild] <= ::heap[smallest])
        smallest = rchild;
    if(smallest != i)
    {
        int l = ::heap[smallest];
        ::heap[smallest] = ::heap[i];
        ::heap[i] = l;
        heapify(smallest);
    }
}

int heap_delete()
{
    if(::heap_size <= 0)
        return 10000000;
    if(::heap_size == 1)
    {
        ::heap_size--;
        return ::heap[0];
    }
    int root = ::heap[0];
    ::heap[0] = ::heap[::heap_size-1];
    ::heap_size--;
    heapify(0);
    return root;
}

void search(int G[][n], int a, int visited[n], int visited_count, int &i, int &j)
{
    for(i=0; i<visited_count; i++)
        for(j=0; j<n; j++)
            if(G[visited[i]][j] == a)
                return;
    j = -1;
    i = -1;
}   

void krushka(int G[][n])
{
    int done = 0;
    for(int i=0; i<n; i++)
        for(int j=0; j<n; j++)
            if(G[i][j])
                heap_insert(G[i][j]);

    int visited[n], visit_count=0;
    visited[visit_count++] = 0;
    while(done == 0)
    {
        int r, c, mini, inserted = 0, removed[n], removed_count = 0;
        while(inserted == 0)
        {
            mini = heap_delete();
            if(mini == 10000000 || mini == -1)
                break;
            search(G, mini, visited, visit_count, r, c);
            if(r == -1 || c == -1)
                removed[removed_count++] = mini;
            else
            {
                visited[visit_count++] = c;
                break;
            }
        }
        for(int i=0; i<removed_count; i++)
            heap_insert(removed[i]);
        if(!find(r + 1, c + 1))
            uni(r + 1, c + 1);
        G[r][c] = 0;
        G[c][r] = 0;
        if(::heap_size <= 0)
            done = 1;
    }
    for(int i=1; i<size; i++)
        cout<<i<<" "<<::s[i]<<endl;
}

int main()
{
    int G[n][n];
    for(int i=0; i<n; i++)
        for(int j=0; j<n; j++)
            G[i][j] = 0;

    for(int i=0; i<n*n; i++)
        ::heap[i] = -1;

    insert(G, 1, 2, 2);
    insert(G, 1, 3, 5);
    insert(G, 2, 3, 2);
    insert(G, 2, 4, 3);
    insert(G, 3, 4, 4);
    insert(G, 3, 5, 6);
    insert(G, 4, 6, 8);
    insert(G, 4, 5, 4);
    insert(G, 5, 6, 7);
    krushka(G);
    return 0;   
}