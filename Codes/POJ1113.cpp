#include <cstdio>
#include <cmath>
#include <cstring>
#include <cstdlib>
#include <algorithm>
using namespace std;
const double eps=1e-6 , pi=acos(-1.0);
int sgn(double x){
	if (fabs(x)<eps) return 0;
	return (x>0 ? 1:-1);
}
struct point{
	double x,y;
	point () {}
	point (double a,double b): x(a),y(b) {}
	friend bool operator < (point a,point b){
		return sgn(a.x-b.x)<0 || (sgn(a.x-b.x)==0 && sgn(a.y-b.y)<0);
	}
	friend point operator - (point a,point b){
		return point(a.x-b.x,a.y-b.y);
	}
	void read(){
		scanf("%lf%lf",&x,&y);
	}
	double norm(){
		return sqrt(x*x+y*y);
	}
}S;
	double det(point a,point b){
		return a.x*b.y-a.y*b.x;
	}
	bool detcmp(point a,point b){
		point p=a-S,q=b-S;
		return sgn(det(p,q))>0 || ( sgn(det(p,q))==0 && sgn(p.norm()-q.norm())>0 );
	}
void convex_hull(point *a,point *b,int n,int &bn){
	int i,j,k,p=0;
	for (i=1;i<n;i++)
		if (a[i]<a[p])
			p=i;
	swap(a[p],a[0]);
	S=a[0];
	sort(a+1,a+n,detcmp);
	for (i=1;i<n;i++)
		if (sgn(det(a[i-1]-S,a[i]-S))!=0) break;
	for (j=1,k=i-1;j<k;j++,k--)
		swap(a[j],a[k]);
	
	b[0]=a[0]; b[1]=a[1];
	p=1;
	for (i=2;i<n;i++){
		while (sgn(det(b[p]-b[p-1],a[i]-b[p-1])<0)) p--;
		b[++p]=a[i];
		//for (int ii=0;ii<=p;ii++) printf("%.0lf,%.0lf ",b[ii].x,b[ii].y); printf("\n");
	}
	bn=p+1;
}

int n,R;
point a[1005],b[1005];
void init(){
	int i;
	scanf("%d%d",&n,&R);
	for (i=0;i<n;i++)
		a[i].read();
}
void tr(){
	int bn,i;
	convex_hull(a,b,n,bn);
	double ans=2.*R*pi;
	b[bn]=b[0];
	for (i=0;i<bn;i++){
		//printf(" %.0lf %.0lf\n",b[i].x,b[i].y);
		point t=b[i+1]-b[i];
		ans+=t.norm();
	}
	printf("%.0f\n",ans);
}
int main(){
	init();
	tr();
	return 0;
}
