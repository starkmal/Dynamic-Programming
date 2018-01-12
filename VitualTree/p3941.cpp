#include<stdio.h>
#include<string.h>
#include<algorithm>
#include<queue>
#include<vector>
using namespace std;
const int N=300005,M=N<<1,Inf=1e9;
#define DEBUG 0

typedef vector<int> vt;
typedef vt::iterator vi;
vt G[N];

int n,T;

//Origin Tree
int vtt,Dfn[N],Dep[N],Fa[N][22],Size[N];
void Dfs(int x){
	Dfn[x]=++vtt;
	Dep[x]=Dep[Fa[x][0]]+1;
	Size[x]=1;
	for(int i=1;i<=20;i++)Fa[x][i]=Fa[Fa[x][i-1]][i-1];
	for(vi nxt=G[x].begin();nxt!=G[x].end();nxt++)
		if(!Dfn[*nxt]){
			Fa[*nxt][0]=x;
			Dfs(*nxt);
			Size[x]+=Size[*nxt];
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
int dis(int x,int y){return Dep[x]+Dep[y]-Dep[LCA(x,y)]*2;}

//Virtual Tree
int Tote,Last[N],Next[M],End[M];
void Ins(int x,int y){
	End[++Tote]=y;
	Next[Tote]=Last[x];
	Last[x]=Tote;
}

int tot,c[N],Msp[N],f[N],Val[N];
void DP1(int x){
	int i,j,u,k,t0,t1;
	c[++tot]=x,Val[x]=Size[x];
	for(i=Last[x],u;i;i=Next[i]){
			k=u=End[i];
			DP1(u);
			for(j=20;j>=0;j--)
				if(Dep[Fa[k][j]]>Dep[x])k=Fa[k][j];
			Val[x]-=Size[k];
			if(!Msp[u])continue;
			int t0=dis(Msp[u],x),t1=dis(Msp[x],x);
			if((t0==t1&&Msp[u]<Msp[x])||t0<t1||!Msp[x])Msp[x]=Msp[u];
	}
}

void DP2(int x){
	for(int i=Last[x],u;i;i=Next[i]){
		u=End[i];
		int t0=dis(Msp[x],u),t1=dis(Msp[u],u);
		if((t0==t1&&Msp[x]<Msp[u])||t0<t1||!Msp[u])Msp[u]=Msp[x];
		DP2(u);
	}
}

void GetAns(int x,int y){
	int i,k=y,r=y,t,t0,t1;
	for(i=20;i>=0;i--)
		if(Dep[Fa[r][i]]>Dep[x])r=Fa[r][i];
	if(Msp[x]==Msp[y]){
		f[Msp[x]]+=Size[r]-Size[y];
		return;
	}
	for(i=20;i>=0;i--)
		if(Dep[t=Fa[k][i]]>Dep[x]){
		t0=dis(Msp[x],t),t1=dis(Msp[y],t);
		if((t0==t1&&Msp[y]<Msp[x])||t0>t1)k=t;
	}
	f[Msp[x]]+=Size[r]-Size[k];
	f[Msp[y]]+=Size[k]-Size[y];
}

int m,top,s[N],g[N],A[N];
bool cmp(int x,int y){return Dfn[x]<Dfn[y];}
void VT(){
	int i,j,k,t,x,y;
	sort(g+1,g+1+m,cmp);
	if(g[1]!=1)s[++top]=1;
	for(i=1;i<=m;i++){
		t=0;
		while(top){
			t=LCA(s[top],g[i]);
			if(top>1&&Dep[t]<Dep[s[top-1]])
				Ins(s[top-1],s[top]),top--;
			else if(Dep[t]<Dep[s[top]]){
				Ins(t,s[top]),top--;
				break;
			}
			else break;
		}
		if(s[top]!=t)s[++top]=t;
		s[++top]=g[i];
	}
	for(x=s[top--];top;x=s[top--])
		Ins(s[top],x);
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
		for(i=1;i<=m;i++)scanf("%d",&g[i]),A[i]=g[i];
		for(i=1;i<=m;i++)Msp[g[i]]=g[i];
		Tote=top=tot=0;
		VT();
		DP1(1);
		DP2(1);
#if DEBUG
		for(i=1;i<=tot;i++)printf("%d ",c[i]);
		puts("");
		for(i=1;i<=tot;i++)printf("%d ",Msp[c[i]]);
		puts("");
		for(i=1;i<=tot;i++)printf("%d ",Val[c[i]]);
		puts("");
		printf("%d\n",Tote);
#endif
		for(i=1;i<=tot;i++)f[Msp[c[i]]]+=Val[c[i]];
		for(i=1;i<=tot;i++)
			for(j=Last[c[i]];j;j=Next[j])GetAns(c[i],End[j]);
		for(i=1;i<=m;i++)printf("%d ",f[A[i]]);
		puts("");
		for(i=1;i<=tot;i++)Last[c[i]]=f[c[i]]=Val[c[i]]=Msp[c[i]]=0;
	}
}
