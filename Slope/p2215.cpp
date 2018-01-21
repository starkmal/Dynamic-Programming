#include<stdio.h>
#include<algorithm>
using namespace std;
typedef double db;
typedef long long ll;
const int N=1000005;

int n,A,B,C;
ll u[N],f[N],Sum[N];
int hd,tl,s[N];
db Slope(int j,int k){
	return (db)(u[j]-u[k])/(Sum[j]-Sum[k]);
}
int main(){
	int i,j,k;
	scanf("%d%d%d%d",&n,&A,&B,&C);
	hd=tl=1;
	for(i=1;i<=n;i++){
		scanf("%d",&k);
		Sum[i]=Sum[i-1]+k;
		while(hd<tl&&2*A*Sum[i]<=Slope(s[hd],s[hd+1]))hd++;
		j=Sum[i]-Sum[s[hd]];
		f[i]=f[s[hd]]+A*j*j+B*j+C;
		u[i]=f[i]+A*Sum[i]*Sum[i]-B*Sum[i];
		while(hd<tl&&Slope(s[tl-1],s[tl])<Slope(s[tl],i))tl--;
		s[++tl]=i;
	}
	printf("%lld",f[n]);
}
