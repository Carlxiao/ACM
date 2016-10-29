//DFS找环
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#include <cmath>
#include <vector>
#define maxn 305
using namespace std;
const double eps=1e-6;
int sgn(double x){
	if (fabs(x)<eps) return 0;
	return x>0 ? 1:-1;
}

struct point{
	double x,y;
	point() {}
	point(double _x,double _y): x(_x),y(_y) {}
	friend point operator - (point a,point b){
		return point (a.x-b.x , a.y-b.y);
	}
	friend bool operator == (point a,point b){
		return sgn(a.x-b.x)==0 && sgn(a.y-b.y)==0;
	}
	double norm(){
		return sqrt(x*x+y*y);
	}
	void show(){
		printf("%.3lf %.3lf\n",x,y);
	}
};
	double det(point a,point b){
		return a.x*b.y-a.y*b.x;
	}
	double dot(point a,point b){
		return a.x*b.x+a.y*b.y;
	}
struct line{
	point a,b;
	line(point _a,point _b): a(_a),b(_b) {}
};
struct circle{
	point o;
	double r;
	void read(){
		scanf("%lf%lf%lf",&o.x,&o.y,&r);
	}
};

bool point_on_seg(point p,line l){
	return ( sgn(det( p-l.a , l.b-l.a ))==0 && sgn(dot( p-l.a , l.b-l.a ))>0 && sgn(dot( p-l.b , l.a-l.b ))>0);
}
bool cir_intersect( circle a , circle b){
	return sgn( ( a.o - b.o ).norm() - ( a.r + b.r ) ) < 0;
}
int point_in_poly( point p , point *a , int m ){
	int num=0,i,d1,d2,k;
	a[m]=a[0];
	//for (i=0;i<m;i++)a[i].show();
	for (i=0;i<m;i++){
		if ( point_on_seg( p , line( a[i] , a[i+1] ) ) ) return 2;
		k=sgn( det( a[i+1]-a[i] , p-a[i] ) );
		d1=sgn( a[i].y - p.y );
		d2=sgn( a[i+1].y - p.y );
		if ( k>0 && d1<=0 && d2>0 ) num++;
		if ( k<0 && d2<=0 && d1>0 ) num--;
	}
	return num!=0;
}

circle cir[maxn],S;
vector < int > to[maxn];
int n,tim[maxn],tot,top;
point sta[maxn];
bool inside,in[maxn];

void init(){
	int i;
	for (i=0;i<n;i++)
		cir[i].read();
	S.read();
	for (i=0;i<n;i++){
		to[i].clear();
		cir[i].r+=S.r;
	}
}
void dfs(int p){
	//printf("%d\n",p);
	//for (int i=0;i<n;i++) printf("%d ",in[i]); printf("\n");
	//for (int i=0;i<n;i++) printf("%d ",tim[i]); printf("\n");
	tim[p]=++tot;
	sta[top++]=cir[p].o;
	in[p]=1;
	int i;
	for (i=0;i<(int)to[p].size();i++){
		int t=to[p][i];
		//printf("  +%d %d %d\n",t,tim[t],in[t]);
		if (tim[t]>0 && tim[t]==tim[p]-1) continue;
		if (tim[t]==0)
			dfs(t);
		else if (in[t]){
			int j;
			for (j=0;j<top;j++)
				if (sta[j]==cir[t].o) break;
			//printf("~~%d\n",point_in_poly( S.o , sta+j , top-j+1 ));
			//printf("%d %d\n",j,top);
			if ( point_in_poly( S.o , sta+j , top-j ) == 1 ){
				inside=1;
				return;
			}
		}
		if (inside) return;
	}
	//puts("");
	//printf("la\n");
	in[p]=0;
	top--;
}
void tr(){
	int i,j;
	for (i=0;i<n;i++)
		for (j=i+1;j<n;j++)
			if ( cir_intersect( cir[i] , cir[j] ) ){
				to[i].push_back(j);
				to[j].push_back(i);
				//printf("%d %d\n",i,j);
			}
	memset(tim,0,sizeof(tim));
	tot=0; top=0;
	inside=0;
	memset(in,0,sizeof(in));
	for (i=0;i<n;i++){
		if (tim[i]==0)
			dfs(i);
		if (inside) break;
	}
	if (inside) printf("NO\n");
		else printf("YES\n");
}
int main(){
	while (scanf("%d",&n)==1){
		init();
		tr();
	}
	return 0;
}
