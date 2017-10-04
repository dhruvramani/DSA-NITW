#include <iostream>
using namespace std;

# define n 7

struct fields
{
    int visited, cost, previous;
};

void init(fields filed[n])
{
    for(int i=0; i<n; i++)
    {
        filed[i].visited = 0;
        filed[i].cost = 100000;
        filed[i].previous = -1;
    }
}

void shortest_path(int G[][n], int source, int des)
{   
    fields filed[n];
    init(filed);
    int finished = 0, current = source;
    filed[source].cost = 0;
    while(finished == 0)
    {
        for(int i=0; i<n; i++)
        {
            if(G[current][i] != 0 && filed[i].visited == 0)
                if(filed[i].previous == -1 || (filed[i].previous != -1 && filed[i].cost > filed[current].cost + G[current][i])) {
                    filed[i].cost = filed[current].cost + G[current][i];
                    filed[i].previous = current;
                }
        }
        
        filed[current].visited = 1;
        int min = 1000000, ind;
        for(int i=0; i<n; i++)
            if(filed[i].cost < min && filed[i].visited == 0)
            {
                ind = i;
                min = filed[i].cost;
            }

        int ones = 0;
        for(int i=0; i<n; i++)
            if(filed[i].visited == 1)
                ones ++;
        if(ones == n)
            finished = 1;
        else 
            current = ind;
    }
    current = des;
    while(current != -1)
    {
        cout<<current + 1<<" ";
        current = filed[current].previous;
    }
}

int main()
{
    int G[n][n] = {{0, 2, 0, 1, 0, 0, 0}, {0, 0, 0, 4, 10, 0, 0}, {4, 0, 0, 0, 0, 5, 0}, {0, 0, 2, 0, 2, 8, 4}, {0, 0, 0, 0, 0, 0, 6}, {0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 1, 0}}, s, d;
    cout<<"Enter Source & Destination : ";
    cin>>s>>d;
    shortest_path(G, s - 1, d - 1);
    return 0;
}