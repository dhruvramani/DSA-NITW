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

int count = 0, visit = 0, max = -1, sumOweights = 0;
void cycle(int G[][n], int visited[], int start, int current=0)
{
    if(G[current][start] != 0 && start != current)
    {
        ::sumOweights += G[current][start];
        if(::sumOweights > ::max)
            ::max = ::sumOweights;
        ::count++;
        ::sumOweights -= G[current][start];
    }

    for(int i=0; i<n; i++)
        if(G[current][i] != 0 && current != i && index(visited, ::visit, i) == -1)
        {
            visited[::visit++] = current;
            ::sumOweights += G[current][i];
            cycle(G, visited, start, i);
            ::sumOweights -= G[current][i];
            ::visit--;
        }
}

int main()
{
    int G[n][n] = {{0, 2, 0, 0, 0}, {0, 0, 5, 0, 3}, {7, 0, 0, 1, 0}, {1, 0, 0, 0, 0}, {0, 0, 0, 1, 0}};
    int visited[n];
    for(int i=0; i<n; i++)
        visited[i] = -1;
    cycle(G, visited, 0);
    cout<<::max<<endl;
    return 0;
}