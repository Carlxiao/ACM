//有向角度为长建边，SPFA找负环
//cmath的fabs精度丢失严重，必须手写
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#include <cmath>
#include <queue>
#define maxn 309
using namespace std;
const double eps=1e-8;
/*int dcmp(double x){
	if (fabs(x)<eps) return 0;
	return x>0 ? 1:-1;
}*/
int dcmp(double x)
{
if (x>eps) return 1;
if (x<-eps) return -1;
return 0;
}
struct path{
	int to,lh;
	double x;
};
struct point{
	double x,y;
	point() {}
	point(double _x,double _y): x(_x),y(_y) {}
	friend point operator - (point a,point b){
		return point (a.x-b.x , a.y-b.y);
	}
};
double det(point a,point b){return a.x*b.y-a.y*b.x;}
double dot(point a,point b){return a.x*b.x+a.y*b.y;}
double dis(point a,point b){return sqrt(dot(a-b,a-b));}
struct circle{
	point o;
	double r;
	void read(){
		scanf("%lf%lf%lf",&o.x,&o.y,&r);
	}
};
bool cir_intersect( circle a , circle b){
	return dcmp( dis( a.o , b.o ) -  a.r - b.r  ) < 0;
}

circle cir[maxn],S;
int n;
double d[maxn];
path a[maxn*maxn];
int ah[maxn],an;

void init(){
	int i;
	for (i=0;i<n;i++)
		cir[i].read();
	S.read();
	for (i=0;i<n;i++)
		cir[i].r+=S.r;
}
bool spfa(){
	queue<int> Q;
	int i;
	int cnt[maxn];
	bool ff[maxn];
	memset(d,0,sizeof(d));
	memset(ff,1,sizeof(ff));
	memset(cnt,0,sizeof(cnt));
	for (i=0;i<n;i++) Q.push(i);
	while (!Q.empty()){
		int P=Q.front(); Q.pop();
		ff[P]=0;
		for (i=ah[P];i;i=a[i].lh){
			int k=a[i].to;
			double l=a[i].x;
			if (dcmp(d[k]-d[P]-l)>0){
			//if (dcmp(d[P]+l-d[k])<0){
				d[k]=d[P]+l;
				if (!ff[k]){
					ff[k]=1;
					cnt[k]++;
					if (cnt[k]>n)
						return 0;
					Q.push(k);
				}
			}
		}
	}
	return 1;
}
double calc(point a,point b,point c){
	double l1=dis(a,c),l2=dis(b,c),l3=dis(a,b);
	return acos((l1*l1+l2*l2-l3*l3)/2/l1/l2);
}
void add(int x,int y,double l){
	an++;
	a[an].to=y; a[an].x=l; a[an].lh=ah[x];
	ah[x]=an;
}
void tr(){
	int i,j;
	memset(ah,0,sizeof(ah));
	an=0;
	for (i=0;i<n;i++)
		for (j=0;j<n;j++)
			if ( i!=j && cir_intersect( cir[i] , cir[j] ) ){
				int f=det( cir[i].o-S.o , cir[j].o-S.o )>0 ? 1:-1;
				add(i,j,f*calc(cir[i].o,cir[j].o,S.o));
			}
	if (spfa()) puts("YES");
		else puts("NO");
}

int main(){
	//freopen("test.in","r",stdin);
	while (scanf("%d",&n)==1){
		init();
		tr();
	}
	return 0;
}
