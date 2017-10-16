#include <iostream>
using namespace std;

# define n 5

void insert(int G[][n], int row, int column, int weight=1)
{  G[row-1][column-1] = weight; }

int visited[n] = {0}, path[n] = {0}, path_count=0;
int DFT(int G[][n], int start, int end)
{
    ::path[::path_count++] = start;
    if(start == end)
        return 1;
    ::visited[start] = 1;
    for(int i=0; i<n; i++)
        if(G[start][i] && ::visited[i] == 0)
            if(DFT(G, i, end))
                return 1;

    return 0;
}       

void ppath(int G[][n], int start, int end)
{
    int ok = DFT(G, start, end);
    cout<<"Possible : "<<ok<<endl;
    if(ok)
        for(int i=0; i< ::path_count; i++)
            cout<<::path[i] + 1<<" ";
}

int main()
{
    int G[n][n];
    for(int i=0; i<n; i++)
        for(int j=0; j<n; j++)
            G[i][j] = 0;

    insert(G, 1, 2);
    insert(G, 2, 4);
    insert(G, 4, 3);
    insert(G, 3, 5);

    ppath(G, 0, 4);
    return 0;
}