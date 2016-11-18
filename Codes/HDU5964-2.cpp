//16合肥-平行四边形
//换基
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cmath>
#include <algorithm>
using namespace std;
const int maxn=1000005;
double a11,a12,a21,a22;
int a1,b1,a2,b2;
double Abs(double x){
	return x>0 ? x : -x;
}
int getint(){
	char c;
	int sgn=1,x=0;
	do {c=getchar();} while ((c<'0'||c>'9')&&c!='-');
	if (c=='-'){
		sgn=-1;
		c=getchar();
	}
	for (;c>='0'&&c<='9';c=getchar())
		x=x*10+c-'0';
	return sgn*x;
}
struct point{
	double x,y;
	void read(){
		//scanf("%lf%lf",&x,&y);
		x=getint();
		y=getint();
		//printf("x,y: %f %f\n",x,y);
	}
	void show(){
		printf("%.2f %.2f\n",x,y);
	}
};

void change(point &p){
	point t;
	t.x = p.x * a22 - p.y * a12;
	t.y = -p.x * a21 + p.y * a11;
	p=t;
}

point nod[maxn],A1,A2;
int n;
void init(){
	int i;
	//scanf("%d%d%d%d",&a1,&b1,&a2,&b2);
	A1.x=b1; A1.y=-a1;
	A2.x=b2; A2.y=-a2;
	scanf("%d",&n);
	//n=getint();
	for (i=0;i<n;i++)
		nod[i].read();
}
void tr(){
	a11 = A1.x;
	a21 = A1.y;
	a12 = A2.x;
	a22 = A2.y;
	double det = a11 * a22 - a21 * a12;
	
	for (int i=0;i<n;i++)
		change(nod[i]);
	
//	for (int i=0;i<n;i++) nod[i].show();	
		
	double maxm=nod[0].x*nod[0].y,minm=nod[0].x*nod[0].y;
	for (int i=1;i<n;i++){
		maxm = max(maxm , nod[i].x*nod[i].y);
		minm = min(minm , nod[i].x*nod[i].y);
	}
	
	printf("%.0f\n",Abs((maxm-minm)/det));
}
int main(){
	freopen("pland10.in","r",stdin);
	while (scanf("%d%d%d%d",&a1,&b1,&a2,&b2)==4){
		init();
		tr();
	}
	return 0;
}
