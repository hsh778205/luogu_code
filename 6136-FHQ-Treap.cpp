/**************************************************************
 * Problem: 6136-FHQ-Treap
 * Author: Vanilla_chan
 * Date: 20210306
**************************************************************/
#include<iostream>
#include<algorithm>
#include<cstdio>
#include<cstring>
#include<cmath>
#include<map>
#include<set>
#include<queue>
#include<vector>
#include<limits.h>
#define IL inline
#define re register
#define LL long long
#define ULL unsigned long long
#ifdef TH
#define debug printf("Now is %d\n",__LINE__);
#else
#define debug 
#endif
#ifdef ONLINE_JUDGE
char buf[1<<23],* p1=buf,* p2=buf,obuf[1<<23],* O=obuf;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
#endif
using namespace std;

template<class T>inline void read(T& x)
{
	char ch=getchar();
	int fu;
	while(!isdigit(ch)&&ch!='-') ch=getchar();
	if(ch=='-') fu=-1,ch=getchar();
	x=ch-'0';ch=getchar();
	while(isdigit(ch)) { x=x*10+ch-'0';ch=getchar(); }
	x*=fu;
}
inline int read()
{
	int x=0,fu=1;
	char ch=getchar();
	while(!isdigit(ch)&&ch!='-') ch=getchar();
	if(ch=='-') fu=-1,ch=getchar();
	x=ch-'0';ch=getchar();
	while(isdigit(ch)) { x=x*10+ch-'0';ch=getchar(); }
	return x*fu;
}
int G[55];
template<class T>inline void write(T x)
{
	int g=0;
	if(x<0) x=-x,putchar('-');
	do { G[++g]=x%10;x/=10; } while(x);
	for(int i=g;i>=1;--i)putchar('0'+G[i]);putchar('\n');
}
#define N 1100010
int tot,root;
int sze[N],ls[N],rs[N],val[N],key[N];
void upd(int p)
{
	sze[p]=sze[ls[p]]+sze[rs[p]]+1;
}
int node(int v)
{
	tot++;
	sze[tot]=1;
	key[tot]=rand();
	val[tot]=v;
	return tot;
}
void split(int i,int k,int& x,int& y)
{
	if(!i)
	{
		x=y=0;
		return;
	}
	if(val[i]<=k)
	{
		x=i;
		split(rs[i],k,rs[i],y);
	}
	else
	{
		y=i;
		split(ls[i],k,x,ls[i]);
	}
	upd(i);
}
int merge(int x,int y)
{
	if(!x||!y) return x^y;
	if(key[x]<=key[y])
	{
		rs[x]=merge(rs[x],y);
		upd(x);
		return x;
	}
	else
	{
		ls[y]=merge(x,ls[y]);
		upd(y);
		return y;
	}
}
void insert(int v)
{
	int x,y;
	split(root,v,x,y);
	root=merge(x,merge(node(v),y));
}
void del(int v)
{
	/*
	int x,y,z;
	split(root,v-1,x,y);
	split(y,v,y,z);
	y=merge(ls[y],rs[y]);
	root=merge(x,merge(y,z));
	*/
	int x,y,z;
	split(root,v,x,z);
	split(x,v-1,x,y);
	y=merge(ls[y],rs[y]);
	root=merge(merge(x,y),z);
}
int rnk(int v)
{
	int x,y;
	split(root,v-1,x,y);
	int ans=sze[x]+1;
	root=merge(x,y);
	return ans;
}
int kth(int k)
{
	int p=root;
	while(1)
	{
		if(k<=sze[ls[p]])
		{
			p=ls[p];
		}
		else if(k==sze[ls[p]]+1)
		{
			return p;
		}
		else
		{
			k-=sze[ls[p]]+1;
			p=rs[p];
		}
	}
}
int pre(int v)
{
	int x,y,p;
	split(root,v-1,x,y);
	p=x;
	while(rs[p]) p=rs[p];
	merge(x,y);
	return p;
}
int nxt(int v)
{
	int x,y,p;
	split(root,v,x,y);
	p=y;
	while(ls[p]) p=ls[p];
	merge(x,y);
	return p;
}
int n,m;
int op,x,ans,lastans;
int main()
{
	n=read();
	m=read();
	for(int i=1;i<=n;i++)
	{
		insert(read());
	}
	while(m--)
	{
		op=read();
		x=read()^lastans;
		if(op==1)
		{
			insert(x);
		}
		else if(op==2)
		{
			del(x);
		}
		else if(op==3)
		{
			lastans=rnk(x);
		}
		else if(op==4)
		{
			lastans=val[kth(x)];
		}
		else if(op==5)
		{
			lastans=val[pre(x)];
		}
		else lastans=val[nxt(x)];
		if(op>=3) ans^=lastans;
	}
	write(ans);
	return 0;
}

