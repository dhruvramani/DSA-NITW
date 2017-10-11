#include <iostream>
using namespace std;

# define n 6

void insert(int G[][n], int row, int column, int weight=1)
{ 
    G[row-1][column-1] = weight;
    G[column-1][row-1] = weight;
}

int visited[n] = {0}, count=0;
int is_cycle(int G[][n], int original,  int start)
{
    int br = 1;
    cout<<original + 1<<" "<<start + 1<<endl;
    for(int i=0; i<n && br == 1; i++)
        if(start != i && G[start][i] && visited[i] == 0)
            br = 0;
    if(br == 1)
    {
        ::visited[start] = 1;
        return 0;
    }
    ::count++;
    if(start != original && G[start][original] && ::count > 2)
        return 1;
    for(int i=0; i<n; i++)
        if(G[start][i] && i != start && ::visited[i] == 0 && start != original)
        {
            if(i != original) 
            {
                ::visited[i] = 1;
                is_cycle(G, original, i);
            }
        }
}

int main()
{
    int G[n][n];
    for(int i=0; i<n; i++)
        for(int j=0; j<n; j++)
            G[i][j] = 0;

    insert(G, 1, 2);
    insert(G, 1, 3);
    insert(G, 2, 4);
    insert(G, 3, 4);
    insert(G, 1, 5);
    insert(G, 5, 6);
    cout<<is_cycle(G, 0, 0);
    return 0;
}