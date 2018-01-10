#include<stdio.h>
#include<algorithm>
#include<string.h>
#include<queue>
#include<stack>
#include<vector>
typedef long long ll;
using namespace std;
const int N=1000005,M=N<<1,Inf=1e9;

typedef vector<int> vt;
typedef vt::iterator vi;
vt G[N];

int n,m,T;
int vtt,g[N],Dfn[N],Dep[N],Fa[N][22];
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
	int i,t=Dep[y]-Dep[x];
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

ll Ans1,Ans2,Ans3,Size[N],Sum[N],Min[N],Max[N];
bool Mark[N];
void DP(int x,int fa){
	if(Mark[x])Size[x]=1;
	if(!Mark[x])Min[x]=Inf,Max[x]=-Inf;
	else Min[x]=Max[x]=0;
	for(int i=Last[x],u;i;i=Next[i])
		if((u=End[i])!=fa){
			DP(u,x);
			Ans1+=Size[u]*Sum[x]+Size[x]*(Sum[u]+Len[i]*Size[u]);
			Ans2=min(Ans2,Min[x]+Min[u]+Len[i]);
			Ans3=max(Ans3,Max[x]+Max[u]+Len[i]);
			Min[x]=min(Min[x],Min[u]+Len[i]);
			Max[x]=max(Max[x],Max[u]+Len[i]);
			Sum[x]+=Sum[u]+Size[u]*Len[i];
			Size[x]+=Size[u];
		}
}
void Clear(int x,int fa){
	Sum[x]=Size[x]=0;
	Mark[x]=0;
	for(int i=Last[x],u;i;i=Next[i])
		if((u=End[i])!=fa)Clear(u,x);
	Last[x]=0;
}
	
bool cmp(int x,int y){return Dfn[x]<Dfn[y];}
void VT(){
	int i,j,k,t,x,y;
	for(i=1;i<=m;i++)Mark[g[i]]=1;
	sort(g+1,g+1+m,cmp);
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
		if(t!=s.top())s.push(t);
		s.push(g[i]);
	}
	for(x=s.top(),s.pop();!s.empty();x=s.top(),s.pop())
		Ins(x,s.top(),Dep[x]-Dep[s.top()]);
}
int main(){
	int i,j,k,x,y;
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
		Ans1=0,Ans2=Inf,Ans3=0;
		DP(0,0);
		printf("%lld %lld %lld\n",Ans1,Ans2,Ans3);
		Clear(0,0);
	}
}
