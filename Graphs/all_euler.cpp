#include<iostream>
using namespace std;
int n,V[100],ip[100];
struct arr
{
	int elements[100];
	int top;
};
void insert(arr &a,int x)
{
	a.elements[a.top++]=x;
}
void create(int G[][100],int i,int j)
{
	G[i][j]=1;	G[j][i]=1;
}
int degree(int G[100][100],int v)
{
	int cnt=0;
	for(int i=1;i<=n;i++)
		if(G[v][i]==1)
			cnt++;
	return cnt;
}
void get(int G[100][100],arr &Ve,int i)
{
	for(int j=1;j<=n;j++)
		if(G[i][j]==1)
			insert(Ve,j);
}
void dec_degree(int G[100][100],int i,int s)
{
	 	G[s][i]=0;
}
void inc_degree(int G[100][100],int i,int s)
{
		G[s][i]=1;	G[i][s]=1;
}
void DFT(int G[100][100],int i,int V[100],int &cnt)
{
	cnt++;	V[i]=0;
	for(int j=1;j<=n;j++)
	{
		if(G[i][j]==1 && V[j]!=0)
			DFT(G,j,V,cnt);
	}
}
int check_bridge(int G[100][100],int s,int i)
{
	G[s][i]=0;	G[i][s]=0;	int cnt=0;	
	for(int j=1;j<=n;j++)	V[j]=j;
	DFT(G,s,V,cnt);
	if(cnt==n || degree(G,s)==0)	return 0;
	else
	{	G[s][i]=1; G[i][s]=1;	return 1;	}
}
void print(arr V)
{
	for(int i=1;i<V.top;i++)
		cout<<char(ip[V.elements[i]])<<" ";
	cout<<endl;
}
int check(int G[100][100])
{
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)
			if(G[i][j]==1)
				return 0;
	return 1;
}
void euler(int G[100][100],arr Ve,arr seq,int s)
{
	Ve.top=1;	
	get(G,Ve,s);
	if(check(G))
	{
		cout<<"printing :- ";	print(seq);
	}
	else
	{
		for(int i=1;i<Ve.top;i++)
		{
			if(!check_bridge(G,s,Ve.elements[i]))
			{
				insert(seq,Ve.elements[i]);
				euler(G,Ve,seq,Ve.elements[i]);
				inc_degree(G,Ve.elements[i],s);
				seq.top--;
			}
		}
	}
}
int main()
{
	int G[100][100]={0},i,j,flag=1;	arr Ve,seq;
	cout<<"how many vertices are there in graph? : ";	cin>>n;
	for(i=1;i<=n;i++)
	{	ip[i]=i+64;	}
	while(flag)
	{
		cout<<"enter the values of 2 vertices : ";	cin>>i>>j;
		create(G,i,j);
		cout<<"do you want to continue? ";	cin>>flag;
	}
	for(i=1;i<=n;i++)
	{
		if(degree(G,i)%2==1)
		{
			cout<<"euler's cycle is not possible !"<<endl;	break;
		}
	}
	if(i==n+1)
	{
		for(j=1;j<=n;j++)
		{
			seq.top=1;
			insert(seq,j);
			euler(G,Ve,seq,j);
		}
	}
	return 0;
}

