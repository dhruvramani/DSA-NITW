#include <iostream>
using namespace std;

int main()
{
    int yy, month_days[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    string months[] = {"", "January", "Feburary", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December"};
    string days[] = {"Sat", "Sun", "Mon", "Tue", "Wed", "Thu", "Fri"};
    cout<<"Enter Year : ";
    cin>>yy;
    for(int i=1; i<=12; i++)
    {
        cout<<months[i]<<endl;
        int k = yy%100, j = yy/100, h = (1 + 13* (i + 1)/5 + k + k/4 + j/4 - 2*j) % 7;
        for(int j=0; j<7; j++)
        {
            cout<<days[j]<<"\t";
            for(int k = j-h; k <= month_days[i]; k += 7) 
                if(k < 0)
                    cout<<"   |\t";
                else 
                    if(k<9)
                        cout<<" "<<k + 1<<" |\t";
                    else cout<<k + 1<<" |\t";
                
            cout<<endl;
        }
        cout<<endl;
    }
    return 0;
}