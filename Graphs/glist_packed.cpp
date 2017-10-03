#include <iostream>
using namespace std;

# define n 5

struct data
{
    int a;
    char b;
};

struct vertex
{
    data *dat; 
    int count;
    vertex *adjacent[n];
}; 

typedef vertex *VTPTR;

int index(int a[], int m, int l)
{
    for(int i=0; i<m; i++)
        if(a[i] == l)
            return i;
    return -1;
}

VTPTR from_matrix(int G[][n])
{
    VTPTR vertices[n];
    for(int i=0; i<n; i++)
    {
        vertices[i] = new vertex;
        vertices[i]->dat = new data;
        vertices[i]->dat->a = i + 1;
        vertices[i]->dat->b = 'A' + i;
        vertices[i]->count = 0;
        for(int j=0; j<n; j++)
            vertices[i]->adjacent[j] = NULL;
    }
    for(int i=0; i<n; i++)
        for(int j=0; j<n; j++)
            if(i != j && G[i][j] != 0)
                vertices[i]->adjacent[vertices[i]->count++] = vertices[j];

    return vertices[0];
}


int V[n] = {0}, A[n*(n-1)] = {0}, a_count=0, v_count=0;
int visited[n] = {0}, count = 0;

void packed_array(VTPTR ver)
{
    if(::count < n)
    {
        if(index(::visited, ::count, ver->dat->a) == -1)
        {
            ::visited[::count++] = ver->dat->a;
            ::V[::v_count++] = ::a_count;
            for(int i=0; i < ver->count; i++)
                if(ver->adjacent[i])
                    ::A[::a_count++] = ver->adjacent[i]->dat->a;
            for(int i=0; i < ver->count; i++)
                 packed_array(ver->adjacent[i]);
        }
    }
}

int main()
{
    int G[n][n] = {{0, 1, 0, 0, 0}, {0, 0, 1, 0, 1}, {1, 0, 0, 1, 0}, {1, 0, 0, 0, 0}, {0, 0, 0, 1, 0}};
    VTPTR ver = from_matrix(G);
    packed_array(ver);
    for(int i=0; i< ::v_count; i++)
        cout<<::V[i]<<" ";
    cout<<endl;
    for(int i=0; i< ::a_count; i++)
        cout<<::A[i]<<" ";
    return 0;
}