/*
���⣺��������Σ����ܷ�ƴ��һ������Σ�С����ȫ���ϡ����ص�������ת��

ƴ�ķ���ϸ����ʮ���֡�������dfs���δ�����Ƿ���ת��Ȼ������������ʮ����check�����������Ǵ���ҵ�⡣��������©���

���Ǻϲ�ƴ�����������С������ƴ��һ������Ϳ����˻�Ϊ4�����λ���3������ƴ��һ���������ǣ�2+1+1+1,3+1+1,2+2+1
���ҽ���һ��������⣬5��С����������ƴ��һ���ϴ���Σ��������ĳ�ֹ���ͼ��֤��������ͼ����
������������д�ˣ�����3+1+1��3Ҫdfs��2+1+1+1ת��Ϊ4ƴ1���Ҳ�е�࣬�����ټ��ٷ��ࡣ��

�Ѹ���ƴ�������������ִ󲿷ֶ��ǿ���ͨ�������ķ������죺
	��һ��С���ο�ʼ��ÿ���ڵ�ǰ����һ�߲���һ��С���Σ���ɴ�һ��ľ��Σ�ֱ������С����(dfs1)
ʣ�²����ƴ�������ˡ�����ͼ��(dfs3)����ʣ2+2+1(dfs2)��
����ʵ����ֻ��3�����ࣨ��Ȼ2+2+1תΪ3ƴ1֮��Ҫ�����֣�

WA���������Ӽ��Ŵ��&&||���
*/
#include <cstdio>
#include <cstdlib>
#include <cstring>
using namespace std;
struct rec{
	int x,y;
	rec() {}
	rec(int _x,int _y): x(_x),y(_y) {}
	rec trans(){ return rec(y,x); }
	void show(){printf("%d %d\n",x,y);}
};

rec a[10],b[10],tmp,tmp2;
bool f[10],ff[10],yes=0;
int h[5];
void init(){
	for (int i=0;i<5;i++){
		scanf("%d%d",&a[i].x,&a[i].y);
		a[i+5]=a[i].trans();
	}
}
void dfs1(int cnt){
	if (cnt==5){
		yes=1;
		return;
	}
	for (int i=0; i<5 && !yes; i++){
		if (f[i]) continue;
		f[i]=1;
		if (cnt==0){
			tmp=a[i];
			dfs1(cnt+1);
		}else{
			if (tmp.x==a[i].x){ tmp.y+=a[i].y; dfs1(cnt+1); tmp.y-=a[i].y; }
			if (tmp.y==a[i].y){ tmp.x+=a[i].x; dfs1(cnt+1); tmp.x-=a[i].x; }
			if (tmp.x==a[i+5].x){ tmp.y+=a[i+5].y; dfs1(cnt+1); tmp.y-=a[i+5].y; }
			if (tmp.y==a[i+5].y){ tmp.x+=a[i+5].x; dfs1(cnt+1); tmp.x-=a[i+5].x; }
		}
		f[i]=0;
	}
}
bool check3(){
	//for (int i=0;i<3;i++) b[h[i]].show(); puts("");
	if (b[h[0]].y == b[h[1]].y && b[h[1]].y == b[h[2]].y) return 1;
	if (b[h[0]].y == b[h[1]].y && b[h[0]].x + b[h[1]].x == b[h[2]].x) return 1;
	return 0;
}
void check3_dfs(int cnt){
	if (cnt==3){
		yes = yes || check3();
		return;
	}
	for (int i=0;i<3;i++){
		if (ff[i]) continue;
		ff[i]=1;
		h[cnt]=i;
		check3_dfs(cnt+1);
		h[cnt]=i+3;
		check3_dfs(cnt+1);
		ff[i]=0;
	}
}
void dfs2(int cnt){
	if (cnt==4){
		int i;
		for (i=0;i<5;i++)
			if (!f[i]) break;
		b[0]=tmp; b[1]=tmp2; b[2]=a[i];
		b[3]=tmp.trans(); b[4]=tmp2.trans(); b[5]=a[i].trans();
		memset(ff,0,sizeof(ff));
		//puts("!!");
		check3_dfs(0);
		return;
	}
	for (int i=0;i<5;i++){
		if (f[i]) continue;
		f[i]=1;
		if (cnt==0){
			tmp=a[i]; dfs2(cnt+1);
			tmp=a[i+5]; dfs2(cnt+1);
		}
		if (cnt==1){
			if (tmp.x==a[i].x){ tmp.y+=a[i].y; dfs2(cnt+1); tmp.y-=a[i].y; }
			if (tmp.y==a[i].y){ tmp.x+=a[i].x; dfs2(cnt+1); tmp.x-=a[i].x; }
			if (tmp.x==a[i+5].x){ tmp.y+=a[i+5].y; dfs2(cnt+1); tmp.y-=a[i+5].y; }
			if (tmp.y==a[i+5].y){ tmp.x+=a[i+5].x; dfs2(cnt+1); tmp.x-=a[i+5].x; }
		}
		if (cnt==2){
			tmp2=a[i]; dfs2(cnt+1);
			tmp2=a[i+5]; dfs2(cnt+1);
		}
		if (cnt==3){
			if (tmp2.x==a[i].x){ tmp2.y+=a[i].y; dfs2(cnt+1); tmp2.y-=a[i].y; }
			if (tmp2.y==a[i].y){ tmp2.x+=a[i].x; dfs2(cnt+1); tmp2.x-=a[i].x; }
			if (tmp2.x==a[i+5].x){ tmp2.y+=a[i+5].y; dfs2(cnt+1); tmp2.y-=a[i+5].y; }
			if (tmp2.y==a[i+5].y){ tmp2.x+=a[i+5].x; dfs2(cnt+1); tmp2.x-=a[i+5].x; }
		}
		f[i]=0;
	}
}
bool check5(){
	//for (int i=0;i<5;i++) a[h[i]].show(); puts("");
	if ( a[h[1]].y + a[h[2]].y != a[h[3]].y + a[h[4]].y ) return 0;
	return (a[h[1]].y - a[h[4]].y == a[h[0]].y) && (a[h[3]].y - a[h[2]].y == a[h[0]].y)
			&& (a[h[2]].x - a[h[1]].x == a[h[0]].x) && (a[h[4]].x - a[h[3]].x == a[h[0]].x);
}
void dfs3(int cnt){
	if (cnt==5){
		yes=yes || check5();
		return;
	}
	for (int i=0;i<5;i++)
		if (!f[i]){
			f[i]=1;
			h[cnt]=i;
			dfs3(cnt+1);
			h[cnt]=i+5;
			dfs3(cnt+1);
			f[i]=0;
		}
}
int main(){
	init();
	memset(f,0,sizeof(f));
	dfs1(0);
	if (!yes) dfs2(0);
	if (!yes) dfs3(0);
	if (yes) printf("YES\n");
		else printf("NO\n");
	return 0;
}