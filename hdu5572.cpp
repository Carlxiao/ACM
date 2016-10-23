#include <cstdio>
#include <iostream>
#include <cstring>
#include <cstdlib>
#include <cmath>
#include <algorithm>
using namespace std;
const double eps=1e-8;
inline int sgn(double x){
    if (fabs(x)<eps) return 0;
    return x>0 ? 1:-1;
}
int dcmp(double k){
	return k < -eps ? -1 : k > eps ? 1 : 0;
}
inline double sqr(double n){
	return n*n;
}
double mysqrt(double n){
    return sqrt(max(0.0,n));
}
struct point{
    double x,y;
    point() {}
    point(double a,double b): x(a),y(b) {}
    void read(){scanf("%lf%lf",&x,&y);}
	friend point operator + (point a,point b){
		return point( a.x+b.x , a.y+b.y );
	}
	friend point operator - (point a, point b){
		return point( a.x-b.x , a.y-b.y );
	}
	friend point operator * (point a,double x){
		return point( a.x*x , a.y*x );
	}
	friend point operator / (point a,double x){
		return point( a.x/x, a.y/x );
	}
	double norm(){
		return sqrt(x*x+y*y);
	}
	void show(){
		printf("%.2lf %.2lf\n",x,y);
	}
};
	double dot(point a,point b){
		return a.x*b.x+a.y*b.y;
	}
	double det(point a,point b){
		return a.x*b.y-a.y*b.x;
	}
struct circle{
    point o;
    double r;
    void read(){scanf("%lf%lf%lf",&o.x,&o.y,&r);}
};
struct line{
    point a,b;
	line () {}
	line (point _a,point _b): a(_a),b(_b) {}
};


bool point_on_ray(point p,line l){
	return ( sgn(det( p-l.a , l.b-l.a ))==0 && sgn(dot( p-l.a , l.b-l.a ))>0 );
}
bool point_on_seg(point p,line l){
	return ( sgn(det( p-l.a , l.b-l.a ))==0 && sgn(dot( p-l.a , l.b-l.a))>0 && sgn(dot( p-l.b , l.a-l.b ))>0);
}
void circle_cross_line(point a,point b,point o,double r,point ret[],int &num){
    double x0=o.x, y0=o.y;
    double x1=a.x, y1=a.y;
    double x2=b.x, y2=b.y;
    double dx=x2-x1, dy=y2-y1;
    double A=dx*dx+dy*dy;
    double B=2*dx*(x1-x0) + 2*dy*(y1-y0);
    double C=sqr(x1-x0) + sqr(y1-y0) - sqr(r);
    double delta=B*B-4*A*C;
    num=0;
    if (sgn(delta)>=0){
        double t1=(-B-mysqrt(delta)) / (2*A);
        double t2=(-B+mysqrt(delta)) / (2*A);
        ret[num++]=point(x1+t1*dx , y1+t1*dy);
		ret[num++]=point(x1+t2*dx , y1+t2*dy);
    }
}

circle cir;
point A,B,V;
void init(){
    cir.read();
    A.read(); V.read();
    B.read();
}
bool tr(){
	point C,ret[2];
	int m;
	circle_cross_line(A,A+V,cir.o,cir.r,ret,m);
	if (m<=1){
		if (point_on_ray(B,line(A,A+V)))
			return 1;
		else return 0;
	}else{
		if ( (ret[0]-A).norm() < (ret[1]-A).norm() )
			C=ret[0];
		else C=ret[1];
		if ( point_on_ray(B,line(A,A+V)) && !point_on_seg(C,line(A,B)) )
			return 1;
		point B1,BC=B-C;
		B1=C+BC/BC.norm()*(C-A).norm();
		if (sgn(dot(B1-A,C-cir.o))==0)
			return 1;
		return 0;
	}
}
int main(){
    int cas,ii;
	freopen("test.in","r",stdin);
    for (ii=0,scanf("%d",&cas);ii<cas;ii++){
        init();
		printf("Case #%d: ",ii+1);
        if (tr()) printf("Yes\n");
			else printf("No\n");
    }
    return 0;
}
