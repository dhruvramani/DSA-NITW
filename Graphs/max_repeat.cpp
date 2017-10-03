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

int count = 0, visit = 0, repeat[n] = {0};
void cycle(int G[][n], int visited[], int start, int current=0)
{
    if(G[current][start] == 1 && start != current)
    {
        for(int i=0; i < ::visit; i++)
            ::repeat[visited[i]]++;
        ::count++;
    }
    for(int i=0; i<n; i++)
        if(G[current][i] == 1 && current != i && index(visited, ::visit, i) == -1)
        {
            visited[::visit++] = current;
            cycle(G, visited, start, i);
            ::visit--;
        }
}

int main()
{
    int G[n][n] = {{0, 1, 0, 0, 0}, {0, 0, 1, 0, 1}, {1, 0, 0, 1, 0}, {1, 0, 0, 0, 0}, {0, 0, 0, 1, 0}};
    int visited[n];
    for(int i=0; i<n; i++)
        visited[i] = -1;
    cycle(G, visited, 0);
    int max = -1;
    for(int i=0; i<n; i++)
        if(::repeat[i] > max)
            max = i;
    cout<<max + 1<<endl;
    return 0;
}