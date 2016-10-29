/*14北京 加训打的，一开始抄的是红书的n个圆求并(solve)，花了不少时间（毕竟挺长），
然而因为不知道n和m需要每次初始化出不了样例，换了另一份模板的两个圆求交(solve2)。
两点启示：1.有模板也要熟悉、会用 2.要找合适的模板*/
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
#include <cmath>
#include <vector>
#include <complex>
using namespace std;
const double eps=1e-8;
const double PI=acos(-1.0);
int dcmp(double x){
	return x<-eps ? -1 : x>eps;
}

struct point{
	double x,y;
	point () {}
	point (double _x,double _y): x(_x),y(_y) {}
	friend point operator - (point a,point b){
		return point ( a.x-b.x , a.y-b.y );
	}
	friend point operator + (point a,point b){
		return point ( a.x+b.x , a.y+b.y );
	}
	friend point operator / (point a,double c){
		return point ( a.x/c , a.y/c );
	}
	friend point operator * (point a,double c){
		return point ( a.x*c , a.y*c );
	}
	double norm(){
		return sqrt ( x*x + y*y );
	}
};
double cross(point &a,point &b){
	return a.x*b.y-a.y*b.x;
}

struct Circle {
	point p;
	double r;
	bool operator < (const Circle &o) const{
		if (dcmp(r - o.r) != 0) return dcmp(r-o.r) == -1;
		if (dcmp(p.x - o.p.x) !=0){
			return dcmp(p.x - o.p.x) == -1;
		}
		return dcmp(p.y - o.p.y) == -1;
	}
	bool operator ==(const Circle &o) const{
		return dcmp(r - o.r) == 0 && dcmp(p.x - o.p.x == 0) &&
			dcmp(p.y - o.p.y) ==0;
	}
	double area(){
		return PI * r * r;
	}
};

point rotate(const point &p, double cost, double sint){
	double x = p.x, y = p.y;
	return point( x*cost - y*sint , x*sint + y*cost );
}
pair<point, point> crosspoint(point ap,double ar,point bp,double br){
	double d = (ap - bp).norm();
	double cost = (ar*ar + d*d - br*br) / (2*ar*d);
	double sint = sqrt(1. - cost*cost);
	point v = (bp - ap) / (bp - ap).norm() * ar;
	return make_pair(ap+rotate(v,cost,-sint) , ap+rotate(v,cost,sint));
}
inline pair<point,point> crosspoint (const Circle &a,const Circle &b){
	return crosspoint(a.p, a.r, b.p, b.r);
}

Circle c[5],tc[5];
int n,m;

struct Node{
	point p;
	double a;
	int d;
	Node (const point &p,double a,int d) : p(p), a(a) ,d(d) {}
	bool operator < (const Node &o) const {
		return a < o.a;
	}
};

double arg(point p){
	return arg(complex<double>(p.x,p.y));
}

double _solve(){
	n=0;
	sort(tc,tc+m);
	m=unique(tc,tc+m)-tc;
	for (int i=m-1;i>=0;i--){
		bool ok=1;
		for (int j=i+1;j<m;j++){
			double d = (tc[i].p - tc[j].p).norm();
			if (dcmp(d- abs(tc[i].r - tc[j].r)) <=0){
				ok=0;
				break;
			}
		}
		if (ok) c[n++] = tc[i];
	}
	double ans=0;
	for (int i=0;i<n;i++){
		vector<Node> event;
		point boundary = c[i].p + point(-c[i].r , 0);
		event.push_back(Node(boundary, -PI, 0));
		event.push_back(Node(boundary, PI , 0));
		for (int j=0;j<n;j++){
			if (i==j) continue;
			double d = (c[i].p - c[j].p).norm();
			if (dcmp(d - (c[i].r + c[j].r)) <0){
				pair<point, point> ret = crosspoint(c[i], c[j]);
				double x = arg(ret.first - c[i].p);
				double y = arg(ret.second - c[i].p);
				if (dcmp(x - y) > 0){
					event.push_back(Node(ret.first, x, 1));
					event.push_back(Node(boundary, PI, -1));
					event.push_back(Node(boundary, -PI, 1));
					event.push_back(Node(ret.second, y ,-1));
				} else {
					event.push_back(Node(ret.first, x, 1));
					event.push_back(Node(ret.second, y, -1));
				}
			}
		}
		sort(event.begin(),event.end());
		int sum = event[0].d;
		for (int j=1; j<(int)event.size(); j++){
			if (sum==0){
				ans+=cross(event[j-1].p , event[j].p) / 2;
				double x = event[j-1].a;
				double y = event[j].a;
				double area = c[i].r * c[i].r * (y-x) /2;
				point v1 = event[j-1].p - c[i].p;
				point v2 = event[j].p - c[i].p;
				area -= cross(v1,v2) /2;
				ans+=area;
			}
			sum+=event[j].d;
		}
	}
	return ans;
}
double solve(Circle &a, Circle &b){
	m=2;
	tc[0]=a; tc[1]=b;
	return _solve();
}
double solve2(Circle &a, Circle &b){
	double area=0.;
	Circle &M = (a.r>b.r) ? a:b;
	Circle &N = (a.r>b.r) ? b:a;
	double D=(a.p-b.p).norm();
	if ( dcmp(D-(M.r+N.r))<0 && dcmp(D-(M.r-N.r))>0 ){
		double cosM = (M.r*M.r + D*D - N.r*N.r) / (2.0 * M.r * D);
		double cosN = (N.r*N.r + D*D - M.r*M.r) / (2.0 * N.r * D);
		double alpha = 2.0 * acos(cosM);
		double beta = 2.0 * acos(cosN);
		double TM = 0.5 * M.r * M.r * sin(alpha);
		double TN = 0.5 * N.r * N.r * sin(beta);
		double FM = (alpha / (2.*PI)) * M.area();
		double FN = (beta / (2.*PI)) * N.area();
		area = FM + FN - TM - TN;
	}else if (dcmp(D-(M.r-N.r))<=0)
		area=N.area();
	return N.area()+M.area()-area;
}

int main(){
	int cas,ii,xa,ya,xb,yb,r,R;
	double ans;
	Circle o1,o2,o1p,o2p;
	for (scanf("%d",&cas),ii=1;ii<=cas;ii++){
		scanf("%d%d%d%d%d%d",&r,&R,&xa,&ya,&xb,&yb);
		o1.p=o2.p=point(xa,ya);
		o1p.p=o2p.p=point(xb,yb);
		o1.r=o1p.r=R;
		o2.r=o2p.r=r;
		
		ans= solve(o1,o1p);
		ans-= solve(o2,o1p)-o1p.area();
		ans-= solve(o1,o2p)-o1.area();
		ans-= o2.area() + o2p.area() - solve(o2,o2p);
		ans= o1.area() + o1p.area() - o2.area() - o2p.area() - ans;
		
		/*ans= solve2(o1,o1p);
		ans-= solve2(o2,o1p)-o1p.area();
		ans-= solve2(o1,o2p)-o1.area();
		ans-= o2.area() + o2p.area() - solve2(o2,o2p);
		ans= o1.area() + o1p.area() - o2.area() - o2p.area() - ans;*/
		
		printf("Case #%d: %.6f\n",ii,ans);
	}
	return 0;
}
