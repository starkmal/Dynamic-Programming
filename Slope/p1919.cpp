#include<stdio.h>
#include<algorithm>
using namespace std;
typedef long long ll;
const int N=50005;

int n,s[N];
ll f[N],g[N],h[N],L,x;
ll slope(int j,int k){
	return (h[j]-h[k])/(g[j]-g[k]);
}
int main(){
	register int i,j,k,hd=1,tl=0;
	scanf("%d%lld",&n,&L);
	L++;
	for(i=1;i<=n;i++){
		scanf("%lld",&x);
		g[i]=g[i-1]+x+1;
		while(hd<tl&&2*g[i]>=slope(s[hd],s[hd+1]))hd++;
		f[i]=(g[i]-L)*(g[i]-L);
		if(hd<=tl)f[i]=min(f[i],f[s[hd]]+(g[i]-g[s[hd]]-L)*(g[i]-g[s[hd]]-L));
		h[i]=f[i]+g[i]*g[i]+2*g[i]*L;
		while(hd<tl&&slope(s[tl],s[tl-1])>=slope(s[tl],i))tl--;
		s[++tl]=i;
	}
	printf("%lld",f[n]);
}
