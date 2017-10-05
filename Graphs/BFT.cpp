#include <iostream>
using namespace std;

# define n 5

int visited[n] = {0};
void BFT(int G[][n], int start)
{
    int br = 1;
    for(int i=0; i<n && br == 1; i++)
        if(visited[i] == 0)
            br = 0;
    if(br == 1)
        return;
    for(int i=0; i<n; i++)
        if(G[start][i] && ::visited[i] == 0 && i != start)
        {
            cout<<i + 1<<" ";
            ::visited[i] = 1;
        }
    for(int i=0; i<n; i++)
        if(G[start][i] && i != start)
            BFT(G, i);
}       

int main()
{
    int G[n][n] = {{1, 1, 1, 1, 0}, {1, 1, 1, 0, 1}, {1, 1, 1, 1, 0}, {1, 0, 1, 1, 1}, {0, 1, 0, 1, 1}}, start;
    cout<<"Enter Start Node ("<<n<<") : ";
    cin>>start;
    ::visited[start-1] = 1;
    cout<<start<<" ";
    BFT(G, start-1);
    return 0;
}