//需要一点水的勇气和方法
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cmath>
#include <algorithm>
using namespace std;
const double eps=1e-6;
int sgr(double x){
	if (fabs(x)<eps) return 0;
	if (x>0) return 1;
	return -1;
}

struct point{
	double x,y;
	point() {}
	point(double a,double b): x(a),y(b) {}
	friend point operator - (point a,point b){
		return point(a.x-b.x,a.y-b.y);
	}
	friend point operator / (point a,double c){
		return point(a.x/c,a.y/c);
	}
	friend point operator * (double c,point a){
		return point (c*a.x,c*a.y);
	}
};
	double det(point a,point b){
		return a.x*b.y-a.y*b.x;
	}
	
struct line{
	point a,b;
	line() {}
	void read(){
		scanf("%lf%lf%lf%lf",&a.x,&a.y,&b.x,&b.y);
	}
};
	bool cover(line a,line b){
		return (min(a.a.x,a.b.x)<=max(b.a.x,b.b.x) && min(b.a.x,b.b.x)<=max(a.a.x,a.b.x)
				&&min(a.a.y,a.b.y)<=max(b.a.y,b.b.y) && min(b.a.y,b.b.y)<=max(a.a.y,a.b.y)
				&&sgr(det(a.b-a.a,b.a-a.a)*det(a.b-a.a,b.b-a.a))<=0
				&&sgr(det(b.b-b.a,a.a-b.a)*det(b.b-b.a,a.b-b.a))<=0);
	}
	
int n,ansn,ans[1005],nxt[100005];
line l[100005];
bool f[100005];
void init(){
	int i;
	for (i=0;i<n;i++)
		l[i].read();
	memset(f,1,sizeof(f));
	ansn=0;
}
void tr(){
	int i,j,beg=n,last;
	for (i=0;i<n;i++) nxt[i]=i+1;
	nxt[n]=0;
	for (i=n-1;i>=0;i--){
		if (f[i])
			ans[ansn++]=i;
		if (ansn==1000) break;
		for (j=nxt[beg],last=beg;j<i;j=nxt[j]){
			if (cover(l[i],l[j])){
				f[j]=0;
				nxt[last]=nxt[j];
			}else last=j;
		}
	}
	printf("Top sticks:");
	for (i=ansn-1;i>=0;i--){
		printf(" %d",ans[i]+1);
		if (i) printf(",");
			else printf(".\n");
	}
}
int main(){
	while (scanf("%d",&n)==1){
		if (n==0) break;
		init();
		tr();
	}
	return 0;
}
