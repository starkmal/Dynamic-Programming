#include<stdio.h>
#include<algorithm>
using namespace std;
typedef long long ll;
const int N=20005;

int n,s[N];
ll f[N],g[N],w[N],d[N],ans,sum;
ll slope(int j,int k){
	return (f[j]*g[j]-f[k]*g[k])/(f[j]-f[k]);
}
int main(){
	register int i,j,k,hd=1,tl=0;
	scanf("%d",&n);
	for(i=1;i<=n;i++)
		scanf("%lld%lld",&w[i],&d[i]);
	for(i=1;i<=n;i++)
		f[i]=f[i-1]+w[i];
	for(i=n;i>=1;i--)
		g[i]=g[i+1]+d[i],sum+=w[i]*g[i];
	for(i=1;i<=n;i++){
		while(hd<tl&&g[i]<=slope(s[hd],s[hd+1]))hd++;
		if(hd<=tl)ans=max(ans,f[s[hd]]*g[s[hd]]+(f[i]-f[s[hd]])*g[i]);
		while(hd<tl&&slope(s[tl],s[tl-1])<=slope(s[tl],i))tl--;
		s[++tl]=i;
	}
	printf("%lld",sum-ans);
}
