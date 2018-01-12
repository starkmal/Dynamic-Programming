#include<stdio.h>
#include<algorithm>
#include<queue>
#include<set>
#include<vector>
using namespace std;
typedef long long ll;
const int N=100005;

int n,T;
typedef pair<int,int> pii;
typedef vector<pii> vt;
typedef vt::iterator vi;
#define nd now->first
vt G[N];

int vtt,Dfn[N],Dep[N],Fa[N][22];
ll Dis[N];
void Dfs(int x){
	Dfn[x]=++vtt;
	Dep[x]=Dep[Fa[x][0]]+1;
	for(int i=1;i<=20;i++)Fa[x][i]=Fa[Fa[x][i-1]][i-1];
	for(vi now=G[x].begin();now!=G[x].end();now++)
		if(!Dfn[nd]){
			Fa[nd][0]=x;
			Dis[nd]=Dis[x]+now->second;
			Dfs(nd);
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
ll dis(int x,int y){return Dis[x]+Dis[y]-Dis[LCA(x,y)]*2;}

int Tote,Last[N],Next[N],End[N];
ll Len[N];
void Ins(int x,int y,ll z){
	End[++Tote]=y;
	Len[Tote]=z;
	Next[Tote]=Last[x];
	Last[x]=Tote;
}

int m,top,s[N];
struct cmp{
	bool operator() (const int& a,const int& b) const{return Dfn[a]<Dfn[b];}
};
typedef set<int,cmp> sit;
typedef sit::iterator sii;
sit g;

int main(){
	int i,j,k,x,y,z;
	ll ans=0,ty;
	scanf("%d%d",&n,&T);
	for(i=1;i<n;i++){
		scanf("%d%d%d",&x,&y,&z);
		G[x].push_back(pii(y,z));
		G[y].push_back(pii(x,z));
	}
	Dfs(1);
	while(T--){
		scanf("%d",&x);
		if(!g.count(x))g.insert(x),ty=1;
		else ty=-1;
		sii it=g.find(x),lhs,rhs,bg=g.begin(),ed=g.end();
		ed--;
		lhs=it,lhs--;
		rhs=it,rhs++;
		if(it==bg&&rhs==g.end())ans=0;
		else if(it==bg){
			if(rhs!=ed)ans+=(0-ty)*dis(*rhs,*ed);
			ans+=ty*dis(*rhs,x)+ty*dis(x,*ed);
		}
		else if(it==ed){
			if(lhs!=bg)ans+=(0-ty)*dis(*lhs,*bg);
			ans+=ty*dis(*lhs,x)+ty*dis(x,*bg);
		}
		else ans+=(0-ty)*dis(*lhs,*rhs)+ty*(dis(*lhs,x)+dis(*rhs,x));
		if(ty<0)g.erase(x);
		printf("%lld\n",ans);
	}
}