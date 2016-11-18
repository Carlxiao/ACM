//圆
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#include <cmath>
using namespace std;
const double R=100.0;
const double eps=1e-8;
int dcmp(double x){
	return x<-eps ? -1 : x>eps;
}

struct point{
	double x,y;
	point() {}
	point (double _x,double _y): x(_x),y(_y) {}
	friend point operator + (point a,point b){
		return point( a.x + b.x , a.y + b.y );
	}
	friend point operator - (point a,point b){
		return point( a.x - b.x , a.y - b.y );
	}
	friend point operator * (point a, double x){
		return point( a.x * x , a.y * x);
	}
	friend point operator * (double x , point a){
		return point( a.x * x , a.y * x);
	}
	friend point operator / (point a, double x){
		return point( a.x / x , a.y / x );
	}
	double norm(){
		return sqrt( x*x + y*y );
	}
	point trans(){
		return point( y , -x );
	}
	friend double det(point a,point b){
		return a.x * b.y - a.y * b.x;
	}
	friend double dist(point a,point b){
		return (a-b).norm();
	}
	void read(){
		scanf("%lf%lf",&x,&y);
	}
};
struct line{
	point a,b;
	line (point _a,point _b): a(_a),b(_b) {}
};
struct Circle{
	point o;
	double r;
	Circle () {}
	void read(){
		o.read();
		scanf("%lf",&r);
	}
	void show(){
		printf("%.8f %.8f %.8f\n",o.x,o.y,r);
	}
	point getpoint(double alpha){
		return point( o.x + r*cos(alpha) , o.y + r*sin(alpha) );
	}
};

int cnt;
Circle C1,C2,ans[5];
point P;

void line_make_point(line a, line b, point &res){
	double s1 = det( a.a - b.a , b.b - b.a );
	double s2 = det( a.b - b.a , b.b - b.a );
	res=( s1 * a.b - s2 * a.a ) / ( s1 - s2 );
}
Circle inverse(Circle c1, point P,double R){
	Circle c2;
	double do1 = dist(P,c1.o);
	double da = R / (do1 - c1.r);
	double db = R / (do1 + c1.r);
	double do2 = (da + db) / 2.0;
	c2.r = (da - db) / 2.0;
	c2.o = P + (c1.o - P) / do1 * do2;
	return c2;
}
void add(point a, point b){
	if (dcmp(det( P-a , b-a )) == 0)
		return;
	point v = (b-a).trans();
	point res;
	line_make_point( line(a,b) , line(P,P+v) , res );
	v = res - P;
	Circle c;
	c.r = R / dist( res , P ) / 2.0;
	c.o = P + v / v.norm() * c.r ;
	ans[cnt++]=c;
}
void tr(){
	cnt=0;
	C1=inverse(C1,P,R);
	C2=inverse(C2,P,R);
	//C1.show(); C2.show();
	if (C1.r > C2.r)
		swap(C1,C2);
	point oo = C1.o - C2.o;
	double alpha = atan2( oo.y , oo.x );
	double beta = acos( (C2.r - C1.r) / dist( C2.o , C1.o ) );
	point a = C1.getpoint( alpha - beta );
	point b = C2.getpoint( alpha - beta );
	if ( dcmp( det( b-a , C1.o-a ) ) == dcmp( det( b-a , P-a ) ) 
		&& dcmp( det( b-a , C2.o-a ) ) == dcmp( det( b-a , P-a ) ) )
			add(a,b);
	a = C1.getpoint( alpha + beta );
	b = C2.getpoint( alpha + beta );
	if ( dcmp( det( b-a , C1.o-a ) ) == dcmp( det( b-a , P-a ) ) 
		&& dcmp( det( b-a , C2.o-a ) ) == dcmp( det( b-a , P-a ) ) )
			add(a,b);
}
int main(){
	int cas;
	freopen("test.in","r",stdin);
	for (scanf("%d",&cas);cas;cas--){
		C1.read(); C2.read();
		P.read();
		tr();
		printf("%d\n",cnt);
		for (int i=0;i<cnt;i++)
			ans[i].show();
	}
	return 0;
}
