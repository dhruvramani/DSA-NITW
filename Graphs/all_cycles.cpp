#include <iostream>
using namespace std;

# define n 5

int index(int a[], int m, int l)
{
    for(int i=0; i<m; i++)
        if(a[i] == l)
            return i;
    return -1;
}

int visited[n] = {0};
void BFT(int G[][n], int start)
{
    for(int i=0; i<n; i++)
        if(G[start][i] && ::visited[i] == 0)
        {
            cout<<i<<" ";
            ::visited[i] = 1;
        }
    for(int i=0; i<n; i++)
        if(G[start][i])
            BFT(G, i);
}       

int main()
{
    int G[n][n] = {{0, 1, 0, 0, 0}, {0, 0, 1, 0, 1}, {1, 0, 0, 1, 0}, {1, 0, 0, 0, 0}, {0, 0, 0, 1, 0}};
    int visited[n];
    for(int i=0; i<n; i++)
        visited[i] = -1;
    cycle(G, visited, 0);
    cout<<::count<<endl;
    return 0;
}