#include<stdio.h>
#include<ctype.h>
#include<algorithm>
#include<bitset>
#include<vector>
using namespace std;
typedef long long ll;
const int N=1005;
const ll Mod=100003;
inline ll _R(){
	ll d=0;char t=getchar();
	while(!isdigit(t))t=getchar();
	for(;isdigit(t);t=getchar())d=(d<<3)+(d<<1)+t-'0';
	return d;
}

ll n,k,sum,a[N],f[N],Ans;
ll ksm(ll a,ll b){
	ll ans=1;
	for(;b;b>>=1,a=a*a%Mod)
		if(b&1)ans=ans*a%Mod;
	return ans;
}
int main(){
	freopen("trennen.in","r",stdin);
	freopen("trennen.out","w",stdout);
	ll i,j,x,y;
	n=_R(),k=_R();
	for(i=1;i<=n;i++)a[i]=_R();
	for(i=n;i>=1;i--){
		for(j=i+i;j<=n;j+=i)
			a[i]^=a[j];
		sum+=a[i];
	}
	for(i=1;i<=k;i++)f[k]=_R();
	for(i=n;i>k;i--)f[i]=(n+(n-i)*f[i+1]%Mod)*ksm(i,Mod-2)%Mod;
	for(i=1;i<=sum;i++)Ans=(Ans+f[i])%Mod;
	for(i=1;i<=n;i++)Ans=Ans*i%Mod;
	printf("%lld",Ans);
}
