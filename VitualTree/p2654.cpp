#include<stdio.h>
#include<string.h>
#include<stack>
#include<algorithm>
#include<queue>
#include<vector>
using namespace std;
typedef long long ll;
const int N=250005,M=N<<1;

typedef pair<int,int> pii;
typedef vector<pii> vt;
typedef vt::iterator vi;
#define nd now->first
vt G[N],T[N];

int vtt,Dfn[N],Dep[N],Fa[N][22],Dis[N][22];
void Dfs(int x){
	Dfn[x]=++vtt;
	Dep[x]=Dep[Fa[x][0]]+1;
	for(int i=1;i<=20;i++){
		Fa[x][i]=Fa[Fa[x][i-1]][i-1];
		Dis[x][i]=min(Dis[x][i-1],Dis[Fa[x][i-1]][i-1]);
	}
	for(vi now=G[x].begin();now!=G[x].end();now++)
		if(!Dfn[nd]){
			Fa[nd][0]=x;
			Dis[nd][0]=now->second;
			Dfs(nd);
		}
}
int LCA(int x,int y){
	if(Dep[x]>Dep[y])swap(x,y);
	int i,t=Dep[y]-Dep[x];
	for(i=0;i<=20;i++)
		if((1<<i)&t)y=Fa[y][i];
	if(x==y)return x;
	for(i=20;i>=0;i--)
		if(Fa[x][i]!=Fa[y][i])
			x=Fa[x][i],y=Fa[y][i];
	return Fa[x][0];
}
int GetDis(int x,int y){
	if(Dep[x]>Dep[y])swap(x,y);
	int i,t=Dep[y]-Dep[x],dis=1e9;
	for(i=0;i<=20;i++)
		if((1<<i)&t){
			dis=min(dis,Dis[y][i]);
			y=Fa[y][i];
		}
	return dis;
}

int n,m,tot,g[M];
ll f[N];
bool cmp(int a,int b){return Dfn[a]<Dfn[b];}
int Tote,Last[N],Next[M],End[M];
ll Len[M];
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
void DP(int x,int fa){
	for(int i=Last[x],u;i;i=Next[i])
		if((u=End[i])!=fa){
			DP(u,x);
			if(!Mark[u])f[x]+=min(Len[i],f[u]);
			else f[x]+=Len[i];
		}
}
void Clear(int x,int fa){
	for(int i=Last[x],u;i;i=Next[i])
		if((u=End[i])!=fa)
			Clear(u,x);
	f[x]=0;
	Last[x]=0;
	Mark[x]=0;
}
void VT(){
	int i,j,k,x,y,z,t;
	for(i=1;i<=tot;i++)Mark[g[i]]=1;
	g[++tot]=1;
	sort(g+1,g+1+tot,cmp);
	stack<int>s;
	s.push(g[1]);Tote=0;
	for(i=2;i<=tot;i++){
		t=LCA(s.top(),g[i]);
		while(t!=s.top()&&Dep[t]<=Dep[s.top()]){
			x=s.top(),s.pop();
			if(Dep[t]>Dep[s.top()])Ins(x,t,GetDis(x,t));
			else Ins(x,s.top(),GetDis(x,s.top()));
		}
		if(t!=s.top())s.push(t);
		s.push(g[i]);
	}
	for(t=s.top(),s.pop();!s.empty();t=s.top(),s.pop())
		Ins(t,s.top(),GetDis(t,s.top()));
	DP(1,0);
	printf("%lld\n",f[1]);
	Clear(1,0);
}
int tmain(){
	int i,j,k,x,y,z;
	scanf("%d",&n);
	for(i=1;i<n;i++){
		scanf("%d%d%d",&x,&y,&z);
		G[x].push_back(pii(y,z));
		G[y].push_back(pii(x,z));
	}
	Dfs(1);
	scanf("%d",&m);
	while(m--){
		scanf("%d",&tot);
		for(i=1;i<=tot;i++)scanf("%d",&g[i]);
		VT();
	}
}
