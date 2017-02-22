/*
���⣺
����3���㼯A��B��C������ͬһ�㼯�ĵ���ͬһֱ���ϣ����ص㡣
���ж�����Ԫ��(i,j,k)����C_kΪA_i��B_j�е㡣

˼·��
��0��A��Bû���γ�ֱ�ߣ������ص�ֻ��һ���㣩��������⴦��
��1����A��B��ƽ�У�ö��C��ÿ����C[i]����A����C[i]�ĶԳ�ֱ��A'��B�Ľ���b�Լ�B����C[i]�ĶԳ�ֱ��B'��A�Ľ���a��
�Դ𰸹���ΪA��a������*B��b��������
��2����A��Bƽ�У���AB�еĵ��x����y�������������ö��C��ÿ����C[i]����C[i]��AB������ȣ�����C[i]����*2��Ӧ�ľ��ֵ���㹱�ס�

��ѵ��
1. �����ⲻҪWA�˾ͻ���ը���ȣ��ܿ����и������������
2. c��ab�е㣬���ȼ���a.x + b.x == c.x * 2������a.x != b.x��
3. FFT�����Ľ�����������֮����/len���������롣
4. �ý��Ʊ��루eg. (x,y)->x * base + y����baseһ��Ҫ��������ע��ԭ�����Ƿ���и�����
5. ����cmath��abs��floor�Ȳ���Ҫ������
*/
#include <cstdio>
#include <iostream>
#include <cstring>
#include <cstdlib>
#include <algorithm>
#include <cmath>
#include <map>
#include <complex>
#include <vector>
using namespace std;
typedef long long LL;
typedef long double LD;
typedef complex<LD> comp_d;
const int maxn = 800005, len = 524288, inf = 1e9;
const LD eps = 1e-6, eps1 = 0.5, PI = acos(-1.0);
int dcmp(LD x){ return x<-eps ? -1 : x>eps; }
LD Abs(LD x){ return x<0 ? -x : x; }
struct point{
	LD x, y;
	point(LD a=0, LD b=0): x(a), y(b) {}
	friend point operator + (point a, point b){
		return point (a.x + b.x, a.y + b.y);
	}
	friend point operator - (point a, point b){
		return point (a.x - b.x, a.y - b.y);
	}
	friend point operator * (point a, LD x){
		return point (a.x * x, a.y * x);
	}
	friend point operator * (LD x, point a){
		return point (a.x * x, a.y * x);
	}
	friend point operator / (point a, LD x){
		return point (a.x / x, a.y / x);
	}
	friend bool operator == (point a, point b){
		return dcmp(a.x - b.x)==0 && dcmp(a.y - b.y)==0;
	}
	friend bool operator < (point a, point b){
		int dx = dcmp(a.x - b.x), dy = dcmp(a.y - b.y);
		return dx < 0 || (dx == 0 && dy < 0);
	}
};
LD det(point a, point b){
	return a.x * b.y - a.y * b.x;
}
struct line{
	point a, b;
	line (point _a=point(), point _b=point()) : a(_a),b(_b) {}
	line tran(point p){
		return line(p * 2 - a, p * 2 - b);
	}
};
bool parallel(line a, line b){
	return !dcmp( det(a.a - a.b, b.a - b.b) );
}
bool point_on_line(point p, line l){
	return dcmp( det( l.a - p, l.b - p ) ) == 0;
}
int line_make_point(line a, line b, point &res){
	if (parallel(a, b)){
		if (point_on_line(a.a, b)) return -1;
		return 0;
	}
	LD s1 = det(a.a - b.a, b.b - b.a);
	LD s2 = det(a.b - b.a, b.b - b.a);
	res = ( s1 * a.b - s2 * a.a ) / (s1 - s2);
	return 1;
}

map<LL, int> MA, MB;
int na, nb, nc;
point A[maxn], B[maxn], C[maxn];
line LA, LB;
bool Aonly = 0, Bonly = 0;

LL toLL(LL x, LL y){
	return 1LL * maxn * x + y;
}
int toInt(LD x){
	if (Abs(floor(x) - x) < eps)
		return (int)x;
	else if (Abs(floor(x) + 1 - x) < eps)
		return (int)x + 1;
	else return inf;
}
void build(vector<comp_d> &_P, vector<comp_d> &P, int n, int m, int curr, int &cnt){
	//printf("%d %d %d %d\n",n,m,curr,cnt);
	if (m == n){
		_P[curr] = P[cnt++];
		//if (dcmp(_P[curr].real())>0){puts("_P");for (int i = 0; i < len; i++) printf("%.1f, %.1f  ",_P[i].real(),_P[i].imag()); puts("");}
	}else{
		build(_P, P, n, m * 2, curr, cnt);
		build(_P, P, n, m * 2, curr + m, cnt);
	}
//puts("_P");for (int i = 0; i < len; i++) printf("%.1f, %.1f  ",_P[i].real(),_P[i].imag()); puts("");
}
void FFT(vector<comp_d> &P, int n, int oper){
	static vector<comp_d> _P(len, comp_d(0,0));
	int cnt = 0;
	build(_P, P, n, 1, 0, cnt);
	P = _P;
	for (int d = 0; (1 << d) < n; d++){
		int m = 1 << d;
		int m2 = m * 2;
		LD p0 = PI / m * oper;
		comp_d unit_p0 = comp_d(cos(p0), sin(p0));
		for (int i = 0; i < n; i += m2){
			comp_d unit = 1;
			for (int j = 0; j < m; j++){
				comp_d &P1 = P[i + j + m], &P2 = P[i + j];
				comp_d t = unit * P1;
				P1 = P2 - t;
				P2 = P2 + t;
				unit = unit * unit_p0;
			}
		}
	}
	if (oper == -1)
		for (int i = 0; i < n; i++)
			P[i] /= len;
}

void init(){
	scanf("%d%d%d",&na,&nb,&nc);
	MA.clear();
	for (int i = 0; i < na; i++){
		int x,y;
		scanf("%d%d",&x,&y);
		x += 100000;
		y += 100000;
		LL tmp = toLL(x, y);
		if (MA.find(tmp) == MA.end())
			MA[tmp] = 1;
		else MA[tmp]++;
		A[i] = point(x,y);
	}
	MB.clear();
	for (int i = 0; i < nb; i++){
		int x,y;
		scanf("%d%d",&x,&y);
		x += 100000;
		y += 100000;
		LL tmp = toLL(x, y);
		if (MB.find(tmp) == MB.end())
			MB[tmp] = 1;
		else MB[tmp]++;
		B[i] = point(x,y);
	}
	for (int i = 0; i < nc; i++){
		int x,y;
		scanf("%d%d",&x,&y);
		x += 100000;
		y += 100000;
		C[i] = point(x,y);
	}

	int i;
	for (i = 1; i < na; i++)
		if (!(A[i] == A[0]))
			break;
	if (i < na)
		LA = line(A[0], A[i]);
	else
		Aonly = 1;

	for (i = 1; i < nb; i++)
		if (!(B[i] == B[0]))
			break;
	if (i < nb)
		LB = line(B[0], B[i]);
	else
		Bonly = 1;
}

void tr(){
	LL ans = 0;
	for (int i = 0; i < nc; i++){
		line l = LB.tran(C[i]);
		point cro;
		if (line_make_point(LA, l, cro) < 1) continue;
		int x = toInt(cro.x);
		int y = toInt(cro.y);
		if (x == inf || y == inf)
			continue;
		LL tmp = toLL(x, y);
		LL Acnt = 0;
		if (MA.find(tmp) != MA.end())
			Acnt = MA[tmp];
		else continue;

		line l2 = LA.tran(C[i]);
		point cro2;
		if (line_make_point(LB, l2, cro2) < 1) continue;
		int x2 = toInt(cro2.x);
		int y2 = toInt(cro2.y);
		if (x2 == inf || y2 == inf)
			continue;
		LL tmp2 = toLL(x2, y2);
		if (MB.find(tmp2) != MB.end())
			ans += Acnt * MB[tmp2];
	}
	cout<<ans<<endl;
}

void tr1(){
	LL ans = 0;
	if (Aonly && Bonly){
		for (int i = 0; i < nc; i++)
			if ( C[i] * 2 == A[0] + B[0] )
				ans += 1LL * na * nb;
	}else if (Aonly){
		for (int i = 0; i < nc; i++){
			point p = C[i] * 2 - A[0];
			int x = toInt(p.x);
			int y = toInt(p.y);
			if (x == inf || y == inf)
				continue;
			LL tmp = toLL(x,y);
			if (MB.find(tmp) != MB.end())
				ans += MB[tmp] * na;
		}
	}else{
		for (int i = 0; i < nc; i++){
			point p = C[i] * 2 - B[0];
			int x = toInt(p.x);
			int y = toInt(p.y);
			if (x == inf || y == inf)
				continue;
			LL tmp = toLL(x,y);
			if (MA.find(tmp) != MA.end())
				ans += MA[tmp] * nb;
		}
	}
	cout<<ans<<endl;
}

void tr2(){
	static vector<comp_d> a, b;
	a.resize(len + 5, comp_d(0,0));
	b.resize(len + 5, comp_d(0,0));
	if (dcmp(LA.a.x - LA.b.x) != 0){
		for (int i = 0; i < na; i++)
			a[(int)(A[i].x + eps1)] += 1;
		for (int i = 0; i < nb; i++)
			b[(int)(B[i].x + eps1)] += 1;
	} else {
		for (int i = 0; i < na; i++)
			a[(int)(A[i].y + eps1)] += 1;
		for (int i = 0; i < nb; i++)
			b[(int)(B[i].y + eps1)] += 1;
	}
    FFT(a, len, 1);
    FFT(b, len, 1);
    for (int i = 0; i < len; i++)
		a[i] *= b[i];
	FFT(a, len, -1);

	LL ans = 0;
	point tmp;
	if (dcmp(LA.a.x - LA.b.x) != 0){
		for (int i = 0; i < nc; i++)
			if (line_make_point(LA.tran(C[i]), LB, tmp) == -1){
				int cx = (int)(C[i].x * 2 + eps1);
				ans += (LL)(a[cx].real() + eps1);
			}
	} else {
		for (int i = 0; i < nc; i++)
			if (line_make_point(LA.tran(C[i]), LB, tmp) == -1){
				int cy = (int)(C[i].y * 2 + eps1);
				ans += (LL)(a[cy].real() + eps1);
			}
	}
	cout << ans << endl;
}

int main(){
	init();
	if (Aonly || Bonly)
		tr1();
	else if (parallel(LA, LB))
		tr2();
	else tr();
	return 0;
}

