/**************************************************************
 * Problem: 3674
 * Author: Vanilla_chan
 * Date: 20210321
 * E-Mail: Vanilla_chan@outlook.com
**************************************************************/
#include<iostream>
#include<algorithm>
#include<cstdio>
#include<string>
#include<cstring>
#include<cmath>
#include<map>
#include<set>
#include<queue>
#include<vector>
#include<bitset>
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

namespace oi
{
	inline bool isdigit(const char& ch)
	{
		return ch<='9'&&ch>='0';
	}
	inline bool isalnum(const char& ch)
	{
		return (ch>='a'&&ch<='z')||(ch>='A'&&ch<='Z')||(ch>='0'&&ch<='9');
	}
	struct istream
	{
		char ch;
		bool fu;
		template<class T>inline istream& operator>>(T& d)
		{
			fu=d=0;
			while(!isdigit(ch)&&ch!='-') ch=getchar();
			if(ch=='-') fu=1,ch=getchar();
			d=ch-'0';ch=getchar();
			while(isdigit(ch))
				d=(d<<3)+(d<<1)+(ch^'0'),ch=getchar();
			if(fu) d=-d;
			return *this;
		}
		inline istream& operator>>(string& str)
		{
			str.clear();
			for(;!isdigit(ch);ch=getchar());
			while(isalnum(ch))
				str+=ch,ch=getchar();
			return *this;
		}
	}cin;
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
};
using namespace oi;
#define N 100010
bitset<N>s,t;
bool ans[N];
int n,m;
int a[N];
int block;
struct Ask
{
	int op,l,r,x,id;
	bool operator<(const Ask& z)const
	{
		if(l/block==z.l/block) return r<z.r;
		return l<z.l;
	}
}q[N];
int cnt[N];
void add(int x)
{
	x=a[x];
	if(cnt[x]==0) s[x]=t[n-x]=1;
	cnt[x]++;
}
void del(int x)
{
	x=a[x];
	cnt[x]--;
	if(cnt[x]==0) s[x]=t[n-x]=0;
}
int main()
{
	//freopen(".in","r",stdin);
	//freopen(".out","w",stdout);
	n=read();
	m=read();
	block=sqrt(n);
	for(int i=1;i<=n;i++)
	{
		a[i]=read();
	}
	for(int i=1;i<=m;i++)
	{
		//oi::cin>>q[i].op>>q[i].l>>q[i].r>>q[i].x;
		q[i].op=read();
		q[i].l=read();
		q[i].r=read();
		q[i].x=read();
		q[i].id=i;
	}
	sort(q+1,q+m+1);
	int l=1,r=0,op,x;
	for(int i=1;i<=m;i++)
	{
		while(l>q[i].l) add(--l);
		while(r<q[i].r) add(++r);
		while(l<q[i].l) del(l++);
		while(r>q[i].r) del(r--);
		op=q[i].op;
		x=q[i].x;
		if(op==1)
		{
			ans[q[i].id]=(s&(s<<x)).any();
		}
		else if(op==2)
		{
			ans[q[i].id]=(s&(t>>(n-x))).any();
		}
		else if(op==3)
		{
			for(int j=1;j*j<=x;j++)
			{
				if(x%j==0)
				{
					//cout<<"x="<<x<<" j="<<j<<endl;
					if(s[j]&&s[x/j])
					{
						ans[q[i].id]=1;
						//debug
						break;
					}
				}
			}
		}
		//cout<<"now="<<q[i].id<<" l="<<l<<" r="<<r<<" cnt:"<<endl;
		//for(int i=0;i<=10;i++) cout<<cnt[i]<<" ";
		//cout<<endl;
		//for(int i=1;i<=10;i++) cout<<s[i]<<" ";
		//cout<<endl;
	}
	for(int i=1;i<=m;i++)
	{
		if(ans[i]) cout<<"hana"<<endl;
		else cout<<"bi"<<endl;
	}
	return 0;
}

