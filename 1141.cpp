#include<iostream>
#include<algorithm>
#include<cstdio>
#include<cstring>
#include<cmath>
#include<map>
#include<set>
#include<queue>
#include<vector>
#define IL inline
#define re register
#define LL long long
#define ULL unsigned long long
#ifdef TH
#define debug printf("Now is %d\n",__LINE__);
#else
#define debug
#endif
using namespace std;

template<class T>inline void read(T&x)
{
	char ch=getchar();
	int fu;
	while(!isdigit(ch)&&ch!='-') ch=getchar();
	if(ch=='-') fu=-1,ch=getchar();
	x=ch-'0';ch=getchar();
	while(isdigit(ch)){x=x*10+ch-'0';ch=getchar();}
	x*=fu;
}
inline int read()
{
	int x=0,fu=1;
	char ch=getchar();
	while(!isdigit(ch)&&ch!='-') ch=getchar();
	if(ch=='-') fu=-1,ch=getchar();
	x=ch-'0';ch=getchar();
	while(isdigit(ch)){x=x*10+ch-'0';ch=getchar();}
	return x*fu;
}
int G[55];
template<class T>inline void write(T x)
{
	int g=0;
	if(x<0) x=-x,putchar('-');
	do{G[++g]=x%10;x/=10;}while(x);
	for(int i=g;i>=1;--i)putchar('0'+G[i]);putchar('\n');
}
int f[9000010],sze[9000010];
int table[9000010];
int n,m;
int getf(int x)
{
	if(f[x]==x) return x;
	return f[x]=getf(f[x]);
}
void merge(int x,int y)
{
//	cout<<"+++"<<x<<" "<<y<<endl;
	x=getf(x);
	y=getf(y);
	if(x!=y)
	{
		sze[x]+=sze[y];
		sze[y]=0;
		f[y]=x;
	}
}
bool ask(int x,int y)
{
	return getf(x)==getf(y);
}
int main()
{
	n=read();
	m=read();
	char ch;
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=n;j++)
		{
			ch=getchar();
			while(ch!='1'&&ch!='0') ch=getchar();
			if(ch=='1') table[i*1000+j]=1;
			sze[i*1000+j]=1;
			f[i*1000+j]=i*1000+j;
		}
	}
	for(int i=1;i<=n;i++)
	for(int j=1;j<=n;j++)
	{
		if(n-j&&table[i*1000+j]!=table[i*1000+j+1]) merge(i*1000+j,i*1000+j+1);
		if(n-i&&table[i*1000+j]!=table[(i+1)*1000+j]) merge(i*1000+j,(i+1)*1000+j);
	}
	while(m--)
	{
		write(sze[getf(read()*1000+read())]);
	}
	return 0;
}


