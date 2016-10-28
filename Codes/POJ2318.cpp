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
	point(double a,double b): x(a), y(b) {}
	friend point operator - (point a,point b){
		return point(a.x-b.x,a.y-b.y);
	}
};
	double det(point a,point b){
		return a.x*b.y-a.y*b.x;
	}

struct line{
	point a,b;
	line() {}
};

int n,m,x1,Y1,x2,y2;
line a[5005];
int ans[5005];
void init(){
	int i,j,k;
	for (i=0;i<n;i++){
		scanf("%d%d",&j,&k);
		line t;
		t.a.x=k; t.a.y=y2;
		t.b.x=j; t.b.y=Y1;
		a[i]=t;
	}
}
void tr(){
	point p;
	int i,j;
	memset(ans,0,sizeof(ans));
	for (i=0;i<m;i++){
		scanf("%lf%lf",&p.x,&p.y);
		for (j=0;j<n;j++)
			if (sgr(det( a[j].b-a[j].a , p-a[j].a ))>0)
				break;
		ans[j]++;
	}
	for (i=0;i<=n;i++)
		printf("%d: %d\n",i,ans[i]);
}
int main(){
	while (scanf("%d%d%d%d%d%d",&n,&m,&x1,&Y1,&x2,&y2)==6){
		init();
		tr();
		printf("\n");
	}
	return 0;
}
