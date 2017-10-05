#include <iostream>
using namespace std;

# define n 5

int visited[n] = {0};
void DFT(int G[][n], int start)
{
    int br = 1;
    for(int i=0; i<n && br == 1; i++)
        if(start != i && G[start][i] && visited[i] == 0)
            br = 0;
    if(br == 1)
    {
        ::visited[start] = 1;
        cout<<start + 1<<" ";
        return;
    }
    ::visited[start] = 1;
    cout<<start + 1<<" ";
    for(int i=0; i<n; i++)
        if(G[start][i] && i != start && ::visited[i] == 0)
            DFT(G, i);
}       

int main()
{
    int G[n][n] = {{1, 1, 1, 1, 0}, {1, 1, 1, 0, 1}, {1, 1, 1, 1, 0}, {1, 0, 1, 1, 1}, {0, 1, 0, 1, 1}}, start;
    cout<<"Enter Start Node ("<<n<<") : ";
    cin>>start;
    DFT(G, start-1);
    return 0;
}