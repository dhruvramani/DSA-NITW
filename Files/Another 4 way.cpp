#include<iostream>
#include<fstream>
#include<cstdlib>
using namespace std;
int curr[4]={0};
void merge(int a[4][3],int c[],fstream &f,int itr[],int flag[])
{
	int citr=0,pos=-1,min=10000;
	cout<<"\nflags are : ";
	for(int i=0;i<4;i++)
	cout<<flag[i]<<endl;
	cout<<"\niterators are : \n";
	for(int i=0;i<4;i++)
	{
		cout<<itr[i]<<endl;
	}
	cout<<"\nall arrays are : \n";
	for(int i=0;i<4;i++)
	{
		for(int j=0;j<itr[i];j++)
		cout<<a[i][j]<<" ";
		cout<<endl;
	}
	while(1)
	{
	cout<<"\nin function";
	min=100000;
	
	
	
	for(int i=0;i<4;i++)
	{
		if(curr[i]>=itr[i])
		{
			cout<<"\ncurr is greater than itr for : "<<i<<" and flag is : "<<flag[i];
			if(flag[i]==0)//did not reach end
			{
			pos=i;
			goto there;
		    }
		}
		else
		{
			int x=a[i][ curr[i] ];
		//	cout<<"\nx is : "<<x;
			if(x<min)
			{
				min=x;
				pos=i;
			}
		}
	}
	if(min==100000)
	{
		for(int i=0;i<citr;i++)
	    {
		cout<<"\nwriting : "<<c[i];
		f<<c[i]<<",";
	    }
		return;
	}
	cout<<"\n\ngot : "<<min<<" with : "<<pos<<" curr is : "<<curr[pos];
	c[citr++]=min;	
//	a[pos][ curr[pos] ]=999999;
	curr[pos]++; 
	cout<<"\nnow i's curr is : "<<curr[pos];
	if(citr>=3)
	{
		for(int i=0;i<3;i++)
		{
		cout<<"\nwriting : "<<c[i];
		f<<c[i]<<",";
	    }
		citr=0;
	}	 
    }
	there:
	for(int i=0;i<citr;i++)
	{
	cout<<"\nwriting : "<<c[i];
	f<<c[i]<<",";		
    }
    cout<<endl<<pos<<"'s itertor is 0 now";
	itr[pos]=0;
	curr[pos]=0;
}
void sort(char a1[4][50],char b1[4][50])
{
	fstream in[4];
	fstream out[4];
	for(int i=0;i<4;i++)
	{
		in[i].open(a1[i],ios::in);
		out[i].open(b1[i],ios::out);
	}
	
	int focount=0;//fo=full over
	for(int i=0;i<4;i++)
	{
		char ch;
		in[i].get(ch);
		if(ch=='#'||ch=='|')
		{
			focount++;
		}
		in[i].seekg(0,ios::beg);
	}
	if(focount>=3)
	return;
	
	int over[4]={0};
	int a[4][3],c[3];
	int towrite=0;
	char buf[50];
	int itr[4]={0};
	
	while(1)//for all sp's
	{
		int overcount=0;
		for(int i=0;i<4;i++)
		{
			if(over[i])
			overcount++;
		}
		if(overcount>=4)
		break;
		
		int flag[4]={0};
		for(int i=0;i<4;i++)
		{
			if(over[i]==1)//its used in a lot of places
			flag[i]=1;
		}
		cout<<"\nout";	
		while(1)//for a single sp
		{
			int fcount=0;//exit condition
			for(int i=0;i<4;i++)
			{
				if(flag[i]!=0 || over[i]!=0)
				fcount++;
			}
			if(fcount>=4)
			break;
			cout<<"\nhere";
			for(int i=0;i<4;i++)//going throught ith partition of all files
			{
				cout<<"\nin";
				if(flag[i]==1 || over[i]==1 || itr[i]>=3)
				continue;
				in[i].getline(buf,50,',');
				if(buf[0]=='|' || buf[0]=='*')
				{
					flag[i]=1;
					continue;
				}
				else if(buf[0]=='#')
				{
					over[i]=flag[i]=1;
					continue;
				}
				cout<<"\ngot : "<<buf;
				a[i][itr[i]++]=atoi(buf);
			}
			int mcount=0;
			for(int i=0;i<4;i++)
			{
				if(itr[i]>=3 || flag[i]==1)
				mcount++;
			}
			if(mcount==4)
			merge(a,c,out[towrite],itr,flag);
		}
		out[towrite]<<"|,";
		towrite=(towrite+1)%4;
	}
	cout<<"\ncame out";
	for(int i=0;i<4;i++)
	out[i]<<"#,";
	for(int i=0;i<4;i++)
	{
		in[i].close();
		out[i].close();
	}
	sort(b1,a1);
}
int main()
{
	char a[4][50]={"4a.txt","4b.txt","4c.txt","4d.txt"};	
	char b[4][50]={"4aa.txt","4bb.txt","4cc.txt","4dd.txt"};
	
	sort(a,b);
	cout<<"\nFinished successfully";
}
