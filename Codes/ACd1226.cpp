/*红书推荐经典题，求n平面条直线围成所有最小封闭多边形面积。
  初始化将直线交点离散化，同一直线上相邻两点互相连单向边。
  每次从一条未访问边开始找环，为保证环内没有边，dfs选取下一条边时需极角排序。找到一个环就计算面积退出。
  （实际上不是dfs，因为每次只会遍历到一个最小多边形的所有边）
  这种做法最后会多算一个凸包面积，因为它必然是最大的，把最大的ans去掉即可。
  细节：1.小于eps的面积忽略  2.没有封闭多边形要特判，因为不需要去掉凸包面积（否则会输出-1）*/
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#include <cmath>
#include <map>
#include <vector>
using namespace std;
const double eps=1e-8;
const int maxn=85;
int dcmp(double x){
	return x<-eps ? -1 : x>eps;
}
double Abs(double x){
	return x>=0 ? x : -x;
}
struct point{
	double x,y;
	point () {}
	point(double _x,double _y): x(_x),y(_y) {}
	friend bool operator == (point a,point b){
		return dcmp(a.x-b.x)==0 && dcmp(a.y-b.y)==0;
	}
	friend bool operator < (point a,point b){
		return dcmp(a.x-b.x)<0 || (dcmp(a.x-b.x)==0 && dcmp(a.y-b.y)<0);
	}
	friend point operator - (point a,point b){
		return point( a.x-b.x , a.y-b.y );
	}
	friend point operator * (double x,point a){
		return point( x*a.x , x*a.y );
	}
	friend point operator / (point a,double x){
		return point( a.x/x , a.y/x );
	}
	void show(){
		printf("%.2f %.2f\n",x,y);
	}
};
double det(point a,point b){
	return a.x*b.y - a.y*b.x;
}
struct line{
	point a,b;
	line () {}
	line (point _a,point _b): a(_a),b(_b) {}
	void read(){
		scanf("%lf%lf%lf%lf",&a.x,&a.y,&b.x,&b.y);
	}
};
bool parallel(line a,line b){
	return !dcmp(det( a.a-a.b , b.a-b.b ));
}
int line_make_point(line a, line b, point &res){
	if (parallel(a,b)) return 0;
	double s1=det( a.a-b.a , b.b-b.a );
	double s2=det( a.b-b.a , b.b-b.a );
	res=( s1*a.b - s2*a.a )/( s1-s2 );
	return 1;
}

point P[maxn*maxn],S,T;
line L[maxn];
int ln,N=0;
int sta[maxn*maxn],Top,ansn=0;
double ans[maxn*maxn];
vector<int> to[maxn*maxn];
bool f[maxn*maxn][maxn*maxn],found;
map<point,int> M;

bool cmp(int ha,int hb){
	int xa=dcmp(det(T-S,P[ha]-S));
	int xb=dcmp(det(T-S,P[hb]-S));
	if (xa>=0 && xb<=0) return 1;
	if (xa<=0 && xb>=0) return 0;
	return dcmp(det(P[ha]-S,P[hb]-S))>0;
}
double area(){
	double x=0;
	sta[Top]=sta[0];
	for (int i=0;i<Top;i++)
		x+=det(P[sta[i]] , P[sta[i+1]]);
	return Abs(x/2.0);
}
void add(point a,point b){
	map<point,int> :: iterator it;
	int ha,hb;
	if ((it=M.find(a))==M.end()){
		ha=N;
		P[N]=a;
		to[N].clear();
		M[a]=N++;
	}else
		ha=it->second;
	if ((it=M.find(b))==M.end()){
		hb=N;
		P[N]=b;
		to[N].clear();
		M[b]=N++;
	}else
		hb=it->second;
	if (ha==hb) return;
	to[ha].push_back(hb);
	to[hb].push_back(ha);
}
void init(){
	int i,j,k,cnt;
	point tmp[maxn];
	M.clear();
	scanf("%d",&ln);
	for (i=0;i<ln;i++)
		L[i].read();
	for (i=0;i<ln;i++){
		cnt=0;
		for (j=0;j<ln;j++){
			if (i==j) continue;
			if (line_make_point(L[i],L[j],tmp[cnt])==1){
				//printf("line %d line %d\n",i,j);
				cnt++;
			}
		}
		sort(tmp,tmp+cnt);
		for (j=1;j<cnt;j++){
			add(tmp[j-1],tmp[j]);
			//add(tmp[j],tmp[j-1]);
		}
	}
	memset(f,0,sizeof(f));
}
void dfs(int p,int q){
	if (f[p][q]){
		double x=area();
		if (dcmp(x)>0)
			ans[ansn++]=x;
		found=1;
		return;
	}
	f[p][q]=1;
	sta[Top++]=p;
	S=P[q]; T=P[p];
	for (int i=0;i<to[q].size();i++)
		if (to[q][i]==p){
			swap(to[q][0],to[q][i]);
			break;
		}
	sort(to[q].begin()+1,to[q].end(),cmp);
	for (int i=1;i<to[q].size();i++){
		dfs(q,to[q][i]);
		if (found) break;
	}
	Top--;
}
void tr(){
	int i,j;
	for (i=0;i<N;i++){
		bool ok=1;
		while (ok){
			ok=0;
			for (j=0;j<to[i].size();j++)
				if (!f[i][to[i][j]]){
					Top=0;
					found=0;
					dfs(i,to[i][j]);
					ok=1;
					break;
				}
		}
	}
	sort(ans,ans+ansn);
	if (ansn) ansn--;
	printf("%d\n",ansn);
	for (i=0;i<ansn;i++)
		printf("%.4f\n",ans[i]);
}
int main(){
	init();
	tr();
	return 0;
}
