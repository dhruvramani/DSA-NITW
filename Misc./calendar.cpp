#include <iostream>
using namespace std;

int main()
{
    int yy, month_days[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    string months[] = {"", "January", "Feburary", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December"};
    cout<<"Enter Year : ";
    cin>>yy;
    if(yy%4 == 0 || (yy%100 == 0 && yy%400 == 0))
        month_days[2] = 29;
    int yk = yy-1, start_day = (yy + yk/4 - yk/100 + yk/400) % 7;
    for(int i = 1; i<=12; i++)
    {
        cout<<months[i]<<endl;
        cout<<"S \tM \tT \tW \tT \tF \tS"<<endl;
        cout<<"--\t--\t--\t--\t--\t--\t--"<<endl;
        for(int j=0; j<start_day; j++)
            cout<<"\t";
        for(int j=1; j<=month_days[i]; j++, start_day++)
        {
            if(start_day == 7)
            {
                cout<<endl;
                start_day = 0;
            }
            if(j<10)
                cout<<" "<<j<<"\t";
            else cout<<j<<"\t";
        }
        cout<<endl<<endl;
    }
    return 0;
}