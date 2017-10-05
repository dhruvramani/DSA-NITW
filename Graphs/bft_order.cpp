#include <iostream>
using namespace std;

# define n 5    

int index(int a[], int m, int b)
{
    for(int i=0; i<m; i++)
        if(a[i] == b)
            return i;
    return -1;
}

int visited[n] = {0}, visit = 1;
void print_order(int G[][n], int start)
{
    int init_visit = ::visit;
    if(::visit >= n)
    {
        for(int j=0; j< ::visit; j++)
            cout<<visited[j] + 1<<" ";
        cout<<endl;
        return ;
    }
    
    int to_go[n], count = 0;
    for(int i=0; i<n; i++)
        if(G[start][i] && index(::visited, ::visit, i) == -1 && i != start)
            to_go[count++] = i;
    for(int i=0; i<count; i++)
    {   
        for(int j=0; j<count; j++)
            ::visited[::visit++] = to_go[j];
        print_order(G, to_go[0]);
        int k = to_go[0];
        for(int j=1; j<count; j++)
            to_go[j-1] = to_go[j];
        to_go[count-1] = k;
        for(int j=0; j<count; j++)
            ::visited[index(::visited, ::visit, to_go[j])] = -1;
        ::visit -= count;
    }
}

int main()
{
    int G[n][n] = {{1, 1, 1, 1, 0}, {1, 1, 1, 0, 1}, {1, 1, 1, 1, 0}, {1, 0, 1, 1, 1}, {0, 1, 0, 1, 1}}, start;
    cout<<"Enter Start Node ("<<n<<") : ";
    cin>>start;
    ::visited[0] = start-1;
    print_order(G, start-1);
    /*
    for(int i=0; i<n; i++)
    {
        ::visited[0] = i; 
        ::visit = 1;
        print_order(G, i);
    }*/
    return 0;
}