/*
��������޻�ͼ���·��һ��ʼ����SPFA��ʱ����Ϊ��Ҫ�Ż������ǳ����Լ�SPFA(SLF+LLL)�İ壬����T����ʱ���뵽Ҫ�����Ż���
���˶����Ż�����ȥ��T��ʮ�����ƣ�������ѭ���ˣ��Ļ���SPFA����ȻA�ˡ�
������鷢��ȷʵ���Լ��İ�LLL��һ��ά��д��
��Ȥ��������ʱ�䣺SLF+��ȷLLL > ��SPFA > SLF+������Ĵ���LLL
*/
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
#include <queue>
using namespace std;
struct pat{int to,lh,len;} a[300005];
int an=0, ah[100005];
int n,m,S,T;
int d[1005];
int getint(){
	char c;
	int x=0;
	do {c=getchar();} while (c<'0'||c>'9');
	for (;c>='0'&&c<='9';c=getchar())
		x=x*10+(c-'0');
	return x;
}
void newa(int x,int y,int l){
	an++;
	a[an].to=y; a[an].len=l;
	a[an].lh=ah[x]; ah[x]=an;
}
void init(){
	int i,j,k,l;
	scanf("%d%d",&n,&m);
	memset(ah,0,sizeof(ah));
	for (i=0;i<m;i++){
		//scanf("%d%d%d",&j,&k,&l);
		j=getint();
		k=getint();
		l=getint();
		newa(j,k,l);
	}
	scanf("%d%d",&S,&T);
}
void tr(){  //��
	int i,k,p=0,q=1,P;
	bool f[1005];
	int Q[1005];
	memset(f,0,sizeof(f));
	Q[0]=S; f[S]=1;
	for (i=1;i<=n;i++) d[i]=-1;
	d[S]=0;
	while (p!=q){
		P=Q[p];
		p=(p+1)%n;
		f[P]=0;
		for (i=ah[P];i;i=a[i].lh){
			k=a[i].to;
			if (/*d[k]<0 || */d[P] + a[i].len > d[k]){
				d[k]=d[P] + a[i].len;
				if (!f[k]){
					Q[q]=k;
					q=(q+1)%n;
					f[k]=1;
				}
			}
		}
		//printf("%d\n",P);
		//for (int ii=1;ii<=n;ii++) printf("%d ",d[ii]); puts("");
	}
	//for (int ii=1;ii<=n;ii++) printf("%d ",d[ii]);
}
void spfa(){ //SLF+LLL����ȷ��
	static deque<int> Q;
	static bool f[1005];
	int i,k,P;
	long long ds=0,Qs=1;
	Q.clear();
	memset(f,0,sizeof(f));
	for (i=0;i<=n;i++) d[i]=-1;
	f[S]=1; d[S]=0; Q.push_back(S);
	while (!Q.empty()){
		while(1){
			P=Q.front();
			if ((long long)d[P]*Qs >= ds) break;
			Q.push_back(P);
			Q.pop_front();
		}
		Qs--; ds-=d[P];
		Q.pop_front();
		f[P]=0;
		for (i=ah[P];i;i=a[i].lh){
			k=a[i].to;
			if (d[P]+a[i].len>d[k]){
				if (f[k]) ds-=d[k];
				d[k]=d[P]+a[i].len;
				if (!f[k]){
					f[k]=1;
					ds+=d[k];
					if (!Q.empty() && d[k]>d[Q.front()]) Q.push_front(k);
						else Q.push_back(k);
					Qs++;
				}
			}
		}
	}
}
void spfa2(){  //SLF+LLL������
	static deque<int> Q;
	static bool f[1005];
	int i,k,P;
	long long ds=0,Qs=1;
	Q.clear();
	memset(f,0,sizeof(f));
	for (i=0;i<=n;i++) d[i]=-1;
	f[S]=1; d[S]=0; Q.push_back(S);
	while (!Q.empty()){
		while(1){
			P=Q.front();
			if (d[P]*Qs <= ds) break;//��������·ʱӦΪ<=���·ӦΪ>=�����ĳ�>=����ѭ������dsƫ�󣩣���<=�����..
			Q.push_back(P);
			Q.pop_front();
		}
		Qs--; ds-=d[P];
		Q.pop_front();
		f[P]=0;
		for (i=ah[P];i;i=a[i].lh){
			k=a[i].to;
			if (d[P]+a[i].len>d[k]){
				if (f[k]) ds-=d[k];
				d[k]=d[P]+a[i].len;
				ds+=d[k];  //���Ӧ�÷���if(!f[k])����
				if (!f[k]){
					f[k]=1;
					if (!Q.empty() && d[k]>d[Q.front()]) Q.push_front(k);
						else Q.push_back(k);
					Qs++;
				}
			}
		}
	}
}
int main(){
	init();
	//spfa();
	tr();
	if (d[T]<0) printf("No solution\n");
		else printf("%d\n",d[T]);
	return 0;
}