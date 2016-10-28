#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
#include <cmath>
using namespace std;
const double eps=1e-6;
int n;

int sgr(double x){
	if (fabs(x)<eps) return 0;
	if (x>0) return 1;
	return -1;
}
void adj(double &x,int w){
	double d=1.0;
	for (int i=0;i<w;i++) d/=10.0;
	if (x<0&&x>(-d))
		x=eps/2.0;
}

struct point{
	double x,y;
	point() {}
	point(double a,double b): x(a),y(b) {}
	friend point operator - (point a,point b){
		return point(a.x-b.x,a.y-b.y);
	}
	friend point operator * (double c,point p){
		return point(c*p.x,c*p.y);
	}
	friend point operator / (point p,double c){
		return point (p.x/c,p.y/c);
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
}l1,l2;
	bool point_on_line(point p,line l){
		return !sgr(det(l.a-p,l.b-p));
	}
	bool parallel(line a,line b){
		return !sgr(det(a.a-a.b,b.a-b.b));
	}
	int line_make_point(line a,line b,point &res){
		if (parallel(a,b)){
			if (point_on_line(a.a , b)) return -1;
			return 0;
		}
		double s1=det(a.a-b.a,b.b-b.a);
		double s2=det(a.b-b.a,b.b-b.a);
		res=(s1*a.b-s2*a.a)/(s1-s2);
		return 1;
	}
	
int main(){
	scanf("%d",&n);
	int i,c;
	point x;
	printf("INTERSECTING LINES OUTPUT\n");
	for (i=0;i<n;i++){
		l1.read();
		l2.read();
		c=line_make_point(l1,l2,x);
		if (c==-1) printf("LINE\n");
		if (c==0) printf("NONE\n");
		//adj(x.x,2); adj(x.y,2);
		if (c==1) printf("POINT %.2f %.2f\n",x.x,x.y);
	}
	printf("END OF OUTPUT\n");
	return 0;
}
