//16合肥-平行四边形
//两条直线通过坐标系旋转和仿射变换变为x、y轴，此时平行四边形面积为|xi*yi-xj*yj|/2，于是转化为求新坐标系下max{xi*yi}，min{xi*yi}
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cmath>
#include <algorithm>
using namespace std;
const int maxn=1000005;
double r11,r12,r21,r22;
double s11,s12,s21,s22;
int a1,b1,a2,b2;
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
	}
	void show(){
		printf("%.2f %.2f\n",x,y);
	}
};

void rotate(point &p){
	double x=p.x , y=p.y;
	p.x = r11 * x + r12 * y;
	p.y = r21 * x + r22 * y;
}
void shear(point &p){
	double x=p.x , y=p.y;
	p.x = s11 * x + s12 * y;
	p.y = s21 * x + s22 * y;
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
	double theta=-atan2(A1.y,A1.x);
	r11=cos(theta); r12=-sin(theta);
	r21=sin(theta); r22=cos(theta);
	
	rotate(A2);
	for (int i=0;i<n;i++)
		rotate(nod[i]);
	
	s11=1; s12=-A2.x/A2.y;
	s21=0; s22=1;
	
	for (int i=0;i<n;i++)
		shear(nod[i]);
	
//	for (int i=0;i<n;i++) nod[i].show();	
		
	double maxm=nod[0].x*nod[0].y,minm=nod[0].x*nod[0].y;
	for (int i=1;i<n;i++){
		maxm = max(maxm , nod[i].x*nod[i].y);
		minm = min(minm , nod[i].x*nod[i].y);
	}
	
	printf("%.0f\n",(maxm-minm));
}
int main(){
	freopen("pland10.in","r",stdin);
	while (scanf("%d%d%d%d",&a1,&b1,&a2,&b2)==4){
		init();
		tr();
	}
	return 0;
}
