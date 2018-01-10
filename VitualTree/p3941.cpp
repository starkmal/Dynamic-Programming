#include<stdio.h>
#include<string.h>
#include<algorithm>
#include<queue>
#include<stack>
#include<vector>
using namespace std;
const int N=300005,M=N<<1;

typedef vector<int> vt;
typedef vt::iterator vi;
vt G[N];

int n,T;
int vtt,Dfn[N],Dep[N],Fa[N][22];
void Dfs(int x){
	Dfn[x]=++vtt;
	Dep[x]=Dep[Fa[x][0]]+1;
	for(int i=1;i<=20;i++)Fa[x][i]=Fa[Fa[x][i-1]][i-1];
	for(vi nxt=G[x].begin();nxt!=G[x].end();nxt++)
		if(!Dfn[*nxt]){
			Fa[*nxt][0]=x;
			Dfs(*nxt);
		}
}
int LCA(int x,int y){
	if(Dep[x]>Dep[y])swap(x,y);
	int t=Dep[y]-Dep[x],i;
	for(i=0;i<=20;i++)
		if((1<<i)&t)y=Fa[y][i];
	if(x==y)return x;
	for(i=20;i>=0;i--)
		if(Fa[x][i]!=Fa[y][i])
			x=Fa[x][i],y=Fa[y][i];
	return Fa[x][0];
}

int Tote,Last[N],Next[M],End[M],Len[M];
void Ins(int x,int y,int z){
	End[++Tote]=y;
	Len[Tote]=z;
	Next[Tote]=Last[x];
	Last[x]=Tote;

	End[++Tote]=x;
	Len[Tote]=z;
	Next[Tote]=Last[y];
	Last[y]=Tote;
}
bool Mark[N];

int m,g[N];
bool cmp(int x,int y){return Dfn[x]<Dfn[y];}
void VT(){
	int i,j,k,t,x,y;
	for(i=1;i<=m;i++)Mark[g[i]]=1;
	sort(g+1,g+1+tot,cmp);
	stack<int>s;
	s.push(0);
	Tote=0;
	for(i=1;i<=m;i++){
		t=LCA(s.top(),g[i]);
		while(t!=s.top()&&Dep[t]<=Dep[s.top()]){
			x=s.top(),s.pop();
			if(Dep[t]>Dep[s.top()])Ins(x,t,Dep[x]-Dep[t]);
			else Ins(x,s.top(),Dep[x]-Dep[s.top()]);
		}
		if(s.top()!=t)s.push(t);
		s.push(g[i]);
	}
	for(x=s.top(),s.pop();!s.empty();x=s.top(),s.pop())
		Ins(x,s.top(),Dep[x]-Dep[s.top()]);
}
int main(){
	int i,j,k,x,y,z;
	scanf("%d",&n);
	for(i=1;i<n;i++){
		scanf("%d%d",&x,&y);
		G[x].push_back(y);
		G[y].push_back(x);
	}
	Dfs(1);
	scanf("%d",&T);
	while(T--){
		scanf("%d",&m);
		for(i=1;i<=m;i++)scanf("%d",&g[i]);
		VT();
		DP(0,0);
		printf("%d\n",Ans);
		Clear(0,0);
	}
}
