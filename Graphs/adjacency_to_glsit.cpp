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

int main()
{
    int G[n][n] = {{0, 1, 0, 0, 0}, {0, 0, 1, 0, 1}, {1, 0, 0, 1, 0}, {1, 0, 0, 0, 0}, {0, 0, 0, 1, 0}};
    VTPTR ver = from_matrix(G);
    cout<<ver->adjacent[0]->dat->b<<endl;
    return 0;
}