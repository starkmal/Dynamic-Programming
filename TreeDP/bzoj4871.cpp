#include<stdio.h>
#include<ctype.h>
#include<algorithm>
#include<vector>
using namespace std;
const int N=100005;
inline int _R(){
	int d=0;char t=getchar();
	while(!isdigit(t))t=getchar();
	for(;isdigit(t);t=getchar())d=(d<<3)+(d<<1)+t-'0';
	return d;
}

int Tote,Last[N],Next[N<<1],End[N<<1];
void Ins(int x,int y){
	End[++Tote]=y;
	Next[Tote]=Last[x];
	Last[x]=Tote;
}

int f[N][2][3];
void DP(int x,int fa){
	int i,u,t=0,tot=0;
	int A0,A1,A2,B0,B1,B2;
	int a0,a1,a2,b0,b1,b2;
	for(i=Last[x];i;i=Next[i]){
		u=End[i];
		if(u==fa)continue;
		DP(u,x);
		
		A0=A1=A2=B0=B1=B2=0;
		a0=f[u][0][0],a1=f[u][0][1],a2=f[u][0][2];
		b0=f[u][1][0],b1=f[u][1][1],b2=f[u][1][2];

		A0=max(a0,max(a1,a2)+1);
		A1=a1+tot;
		A2=f[x][0][1]+a1;

		B0=max(b0,max(b1,b2)+1);
		B0=max(B0,f[x][0][0]+a0-1);
		B0=max(B0,max(f[x][0][0]+a1,f[x][0][0]+a2));
		B1=max(B1,max(f[x][0][2]+a1,f[x][0][1]+a2));
		B1=max(B1,max(f[x][0][1]+a0,tot+b1));
		B1=max(B1,a1+t);
		B2=max(max(f[x][0][2]+a2,f[x][0][2]+a0),max(f[x][0][1]+b1,f[x][1][1]+a1));

		t=max(t+1,tot+max(a0,max(a1,a2)));
		tot++;
		f[x][0][0]=max(f[x][0][0],A0);
		f[x][0][1]=max(f[x][0][1]+1,max(tot,A1));
		f[x][0][2]=max(f[x][0][2]+1,A2);
		f[x][1][0]=max(f[x][1][0],B0);
		f[x][1][1]=max(f[x][1][1]+1,B1);
		f[x][1][2]=max(f[x][1][2]+1,B2);
	}
}
int T,P,n;
int main(){
	freopen("treediagram.in","r",stdin);
	freopen("treediagram.out","w",stdout);
	int i,j,k,x,y;
	T=_R(),P=_R();
	while(T--){
		n=_R();
		for(i=1;i<=P;i++)_R(),_R();
		for(i=1;i<n;i++){
			x=_R(),y=_R();
			Ins(x,y),Ins(y,x);
		}
		DP(1,0);
		printf("%d\n",max(f[1][1][0],max(f[1][1][1],f[1][1][2])));
		//Init
		Tote=0;
		for(i=1;i<=n;i++){
			Last[i]=0;
			for(j=0;j<2;j++)
				for(k=0;k<3;k++)
					f[i][j][k]=0;
		}
	}
}
