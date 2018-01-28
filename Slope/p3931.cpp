#include<stdio.h>
#include<math.h>
#include<algorithm>
using namespace std;
typedef double db;
const int N=100005;
const db eps=1e-9,Inf=1e9;

int n;
db Ans[N];
struct Data{
	int id;
	db A,B,R;
	db k,x,y;
	bool operator < (const Data& a)const{
		return k>a.k;
	}
}Q[N],T[N],S[N];
int fcmp(db a,db b){
	if(fabs(a-b)<=eps)return 0;
	if(a-b<-eps)return 1;
	else return -1;
}
db Slope(const Data& a,const Data& b){
	if(fcmp(a.x,b.x)==0)return Inf;
	return (a.y-b.y)/(a.x-b.x);
}
void CDQ(int l,int r){
	if(l==r){
		Ans[l]=max(Ans[l],Ans[l-1]);
		Q[l].y=Ans[l]/(Q[l].A*Q[l].R+Q[l].B);
		Q[l].x=Q[l].y*Q[l].R;
		return;
	}
	int mid=l+r>>1,i=l,j=mid+1,k=l,hd=1,tl=0;
	//按照时间排序，仍然按k有序
	while(k<=r){
		if(Q[k].id<=mid)T[i++]=Q[k++];
		else T[j++]=Q[k++];
	}
	for(i=l;i<=r;i++)Q[i]=T[i];
	CDQ(l,mid);
	//用按x有序的左侧建凸包
	for(i=l;i<=mid;i++){
		while(hd<tl&&fcmp(Slope(S[tl-1],S[tl]),Slope(S[tl],Q[i]))!=-1)tl--;
		S[++tl]=Q[i];
	}
	//右侧按k有序
	for(i=mid+1;i<=r;i++){
		while(hd<tl&&fcmp(Q[i].k,Slope(S[hd],S[hd+1]))!=-1)hd++;
		Ans[Q[i].id]=max(Ans[Q[i].id],Q[i].A*S[hd].x+Q[i].B*S[hd].y);
	}
	CDQ(mid+1,r);
	//按x值排序，为上一层处理凸包做准备
	i=l,j=mid+1,k=l;
	while(i<=mid&&j<=r){
		if(fcmp(Q[i].x,Q[j].x)==1||
		   (fcmp(Q[i].x,Q[j].x)==0&&fcmp(Q[i].y,Q[j].y)==1))T[k++]=Q[i++];
		else T[k++]=Q[j++];
	}
	while(i<=mid)T[k++]=Q[i++];
	while(j<=r)T[k++]=Q[j++];
	for(i=l;i<=r;i++)Q[i]=T[i];
}
int main(){
	register int i,j,k;
	scanf("%d%lf",&n,&Ans[0]);
	for(i=1;i<=n;i++){
		scanf("%lf%lf%lf",&Q[i].A,&Q[i].B,&Q[i].R);
		Q[i].id=i;
		Q[i].k=-Q[i].A/Q[i].B;
	}
	sort(Q+1,Q+1+n);
	CDQ(1,n);
	printf("%.3lf",Ans[n]);
}
