#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cmath>
#include <algorithm>
using namespace std;
const double eps=1e-8;
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
	double dist(point a,point b){
		double dx=a.x-b.x;
		double dy=a.y-b.y;
		return sqrt(dx*dx+dy*dy);
	}
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
	bool intersect(line a,line b){
		return (sgr(det(a.b-a.a,b.a-a.a)*det(a.b-a.a,b.b-a.a))<=0);
	}
	
int n;
point d[205];
line l[105];
void init(){
	scanf("%d",&n);
	for (int i=0;i<n;i++){
		l[i].read();
		d[i*2]=l[i].a;
		d[i*2+1]=l[i].b;
	}
}
void tr(){
	int i,j,k;
	line t;
	for (i=0;i<2*n;i++)
		for (j=i+1;j<2*n;j++){
			if (sgr(dist(d[i],d[j]))==0) continue;
			t.a=d[i];
			t.b=d[j];
			bool ok=1;
			for (k=0;k<n;k++)
				if (!intersect(t,l[k])){
					ok=0;
					break;
				}
			if (ok){
				printf("Yes!\n");
				return;
			}
		}
	printf("No!\n");
}
int main(){
	int cas;
	for (scanf("%d",&cas);cas;cas--){
		init();
		tr();
	}
	return 0;
}
