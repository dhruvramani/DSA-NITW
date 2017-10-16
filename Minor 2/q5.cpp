#include <iostream>
using namespace std;

# define n 4

struct fields
{
    int visited, cost, previous[n], prev_count;
};

void insert(int G[][n], int row, int column, int weight=1)
{ 
     G[row-1][column-1] = weight; 
     G[column-1][row-1] = weight;
}

void init(fields filed[n])
{
    for(int i=0; i<n; i++)
    {
        filed[i].visited = 0;
        filed[i].cost = 100000;
        filed[i].prev_count = 0;
        for(int j=0; j<n; j++)
            filed[i].previous[j] = -1;
    }
}

fields filed[n];
void shortest_path(int G[][n], int source, int des)
{   
    init(::filed);
    int finished = 0, current = source;
    ::filed[source].cost = 0;
    while(finished == 0)
    {
        for(int i=0; i<n; i++)
        {
            if(G[current][i] != 0 && ::filed[i].visited == 0)
                if(::filed[i].prev_count == 0 || (::filed[i].prev_count > 0 && ::filed[i].cost >= ::filed[current].cost + G[current][i])) {
                    ::filed[i].cost = ::filed[current].cost + G[current][i];
                    ::filed[i].previous[::filed[i].prev_count++] = current;
                }
        }
        
        ::filed[current].visited = 1;
        int min = 1000000, ind;
        for(int i=0; i<n; i++)
            if(::filed[i].cost < min && ::filed[i].visited == 0)
            {
                ind = i;
                min = ::filed[i].cost;
            }

        int ones = 0;
        for(int i=0; i<n; i++)
            if(::filed[i].visited == 1)
                ones ++;
        if(ones == n)
            finished = 1;
        else 
            current = ind;
    }
}

int visited[n] = {0}, vist_count=0;
void print(int s, int curr)
{
    ::visited[::vist_count++] = curr;
    if(curr == s)
    {
        for(int i=0; i< ::vist_count; i++)
            cout<<::visited[i] + 1<<" ";
        cout<<endl;
    }
    for(int i=0; i< ::filed[curr].prev_count; i++)
        print(s, ::filed[curr].previous[i]);
    ::vist_count--;
}

int main()
{
    int G[n][n], s, d;
    for(int i=0; i<n; i++)
        for(int j=0; j<n; j++)
            G[i][j] = 0;

    insert(G, 1, 2, 2);
    insert(G, 2, 4, 2);
    insert(G, 1, 3, 2);
    insert(G, 3, 4, 2);

    cout<<"Enter Source & Destination : ";
    cin>>s>>d;
    shortest_path(G, s - 1, d - 1);
    print(s-1, d-1);
    return 0;
}