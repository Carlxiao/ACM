#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
using namespace std;
const double eps=1e-8;
const double X0=-0.5,X1=0.5,Y0=-0.5,Y1=0.5;
int sgn(double x){
	return x<-eps ? -1 : x>eps;
}

struct point{
	double x,y;
	point() {}
	point(double _x,double _y): x(_x),y(_y) {}
	friend point operator - (point a,point b){
		return point(a.x-b.x,a.y-b.y);
	}
	friend point operator * (double c,point p){
		return point(c*p.x,c*p.y);
	}
	friend point operator / (point p,double c){
		return point(p.x/c,p.y/c);
	}
	friend bool operator < (point a,point b){
		return sgn(a.x-b.x)<0 || (sgn(a.x-b.x)==0 && sgn(a.y-b.y)<0);
	}
	int read(){
		return scanf("%lf%lf",&x,&y);
	}
	void show(){
		printf("%.2lf %.2lf\n",x,y);
	}
}S;
double det(point a,point b){
	return a.x*b.y-a.y*b.x;
}
bool detcmp(point a,point b){
	point p=a-S,q=b-S;
	return sgn(det(p,q))>0;
}
struct line{
	point a,b;
	line() {}
	line(point _a,point _b): a(_a),b(_b) {}
};
bool cross(line a,line b){
	return sgn(det(b.a-a.a , a.b-a.a) * det(b.b-a.a , a.b-a.a))<0;
}
void line_make_point(line a,line b,point &res){
	double s1=det( a.a-b.a , b.b-b.a );
	double s2=det( a.b-b.a , b.b-b.a );
	res=(s1*a.b - s2*a.a)/(s1-s2);
}
double area(point *a,int n){
	int i;
	double ans=0;
	a[n]=a[0];
	for (i=0;i<n;i++)
		ans+=det(a[i],a[i+1]);
	ans/=2.0;
	if (ans<0) return -ans;
		else return ans;
}

point V[10],nod[105];
line E[10];
int cnt;
int main(){
	freopen("test.in","r",stdin);
	int i,j;
	line L;
	point t;
	double ans;
	while (V[0].read()==2){
		ans=0;
		for (i=1;i<4;i++)
			V[i].read();
		V[4]=V[0];
		for (i=0;i<4;i++)
			E[i]=line(V[i],V[i+1]);
		//----4
		L=line(point(X0,Y0),point(X0,Y1));
		cnt=0;
		for (i=0;i<4;i++)
			if (sgn(V[i].x-X0)<=0)
				nod[cnt++]=V[i];
		for (i=0;i<4;i++){
			if (cross(L,E[i])){
				line_make_point(L,E[i],t);
				nod[cnt++]=t;
			}
		}
		for (S=nod[0],i=1,j=0;i<cnt;i++)
			if (nod[i]<S) {S=nod[i];j=i;}
		swap(nod[0],nod[j]);
		sort(nod+1,nod+cnt,detcmp);
		ans+=area(nod,cnt)*4.0*5.0;
		//printf("%.4f\n",area(nod,cnt));
		//----6
		L=line(point(X0,Y1),point(X1,Y1));
		cnt=0;
		for (i=0;i<4;i++)
			if (sgn(V[i].y-Y1)>=0)
				nod[cnt++]=V[i];
		for (i=0;i<4;i++){
			if (cross(L,E[i])){
				line_make_point(L,E[i],t);
				nod[cnt++]=t;
			}
		}
		for (S=nod[0],i=1,j=0;i<cnt;i++)
			if (nod[i]<S) {S=nod[i];j=i;}
		swap(nod[0],nod[j]);
		sort(nod+1,nod+cnt,detcmp);
		ans+=area(nod,cnt)*6.0*5.0;
		//printf("%.4f\n",area(nod,cnt));
		//----3
		L=line(point(X1,Y0),point(X1,Y1));
		cnt=0;
		for (i=0;i<4;i++)
			if (sgn(V[i].x-X1)>=0)
				nod[cnt++]=V[i];
		for (i=0;i<4;i++){
			if (cross(L,E[i])){
				line_make_point(L,E[i],t);
				nod[cnt++]=t;
			}
		}
		for (S=nod[0],i=1,j=0;i<cnt;i++)
			if (nod[i]<S) {S=nod[i];j=i;}
		swap(nod[0],nod[j]);
		sort(nod+1,nod+cnt,detcmp);
		//for (int ii=0;ii<cnt;ii++) nod[ii].show();
		ans+=area(nod,cnt)*3.0*5.0;
		//printf("%.4f\n",area(nod,cnt));
		//----1
		L=line(point(X0,Y0),point(X1,Y0));
		cnt=0;
		for (i=0;i<4;i++)
			if (sgn(V[i].y-Y0)<=0)
				nod[cnt++]=V[i];
		for (i=0;i<4;i++){
			if (cross(L,E[i])){
				line_make_point(L,E[i],t);
				nod[cnt++]=t;
			}
		}
		for (S=nod[0],i=1,j=0;i<cnt;i++)
			if (nod[i]<S) {S=nod[i];j=i;}
		swap(nod[0],nod[j]);
		sort(nod+1,nod+cnt,detcmp);
		ans+=area(nod,cnt)*5.0;
		//printf("%.4f\n",area(nod,cnt));
		//----5
		ans+=5.0*100.0;
		
		printf("%.10f\n",ans/124.0);
	}
	return 0;
}
