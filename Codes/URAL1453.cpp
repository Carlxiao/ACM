/*
题目本身不难，不过要高精度。。
我预处理2的0到10000次幂，用红书的高精度板，MLE一发，发现必须要改
于是把BigNum里固定长度maxl的数组换成vector，然而这个过程比较艰辛，因为vector不能访问超出长度的下标。。
然后想到了resize，搞了一通，保持vector的长度恰好为数字长度

赛后看看FJH的代码，发现根本不用vector写BigNum。。
其实不需要预处理的2的幂，因为过程中需要用到的2的幂的指数是不上升的，动态维护就好
*/
#include <cstdio>
#include <iostream>
#include <cstring>
#include <cstdlib>
#include <algorithm>
#include <vector>
using namespace std;
const int maxl=3000;
const int ten[4]={1,10,100,1000};
typedef long long LL;
struct BigNum{
	//int d[maxl];
	vector<int> d;
	BigNum() {}
	BigNum(LL _x){
		//d[0]=0;
 		d.clear();
		d.push_back(0);
		for (LL x=_x;x;x/=10000)
			//d[ ++d[0] ] = x%10000;
			++d[0] , d.push_back(x%10000);
	}
	string tostring(){
		string s("");
		int i,j,tmp;
		for (i=3;i>=1;i--) if (d[d[0]]>=ten[i]) break;
		tmp=d[d[0]];
		for (j=i;j>=0;j--){
			s = s+(char)(tmp/ten[j] + '0');
			tmp %= ten[j];
		}
		for (i=d[0]-1;i>0;i--){
			tmp=d[i];
			for (j=3;j>=0;j--){
				s=s+(char)(tmp/ten[j]+'0');
				tmp%=ten[j];
			}
		}
		return s;
	}
};
BigNum operator +(const BigNum &a,const BigNum &b){
	BigNum c;
	c.d.resize(max(a.d[0],b.d[0])+1);
	c.d[0]=max(a.d[0],b.d[0]);
	int i,x=0;
	for (i=1;i<=c.d[0];i++){
		int aa = i>a.d[0] ? 0 : a.d[i];
		int bb = i>b.d[0] ? 0 : b.d[i];
		//x = a.d[i] + b.d[i] + x;
		x=aa+bb+x;
		c.d[i]=x%10000;
		x/=10000;
	}
	while (x!=0){
		//c.d[ ++c.d[0] ] = x%10000;
		++c.d[0] , c.d.push_back(x%10000);
		x/=10000;
	}
	//cout<<"    "<<c.tostring()<<endl;
	return c;
}
BigNum operator *(const BigNum &a,const int &k){
	BigNum c;
	c.d.resize(a.d[0]+1);
	c.d[0] = a.d[0];
	int i,x=0;
	for (i=1;i<=a.d[0];i++){
		x=a.d[i]*k+x;
		c.d[i]=x%10000;
		x/=10000;
	}
	while (x>0){
		//c.d[ ++c.d[0] ] = x%10000;
		++c.d[0] , c.d.push_back(x%10000);
		x/=10000;
	}
	while ( (c.d[0]>1) && (c.d[c.d[0]] == 0) ) --c.d[0];
	c.d.resize(c.d[0]+1);
	//cout<<c.tostring()<<endl;
	return c;
}

BigNum po2[10005];
int n,S;
int co[10005],cnt[10005];
vector<int> out[100005];
void init(){
	int i;
 	scanf("%d%d",&n,&S);
	//n=10000; S=100000;
	for (i=0;i<S;i++)
		out[i].clear();
	for (i=0;i<n;i++){
		scanf("%d",co+i);
		//co[i]=S/2;
		int x=co[i];
		out[x].push_back(i);
		out[S-x+1].push_back(i);
	}
	po2[0]=BigNum(1);
	//puts("@@");
	for (i=1;i<=n;i++){
		po2[i]=po2[i-1]*2;
		//printf("%d\n",i);
	}
}
void tr(){
	BigNum ans = BigNum(1LL * (S-1) * n);
	//cout<<ans.tostring()<<endl;
	//for (int i=0;i<=n;i++) cout<<po2[i].tostring()<<endl;
	if (n==1){
		cout<<ans.tostring()<<endl;
		return;
	}
	LL s2 = n;
	memset(cnt,0,sizeof(cnt));
	for (int i=1;i<S;i++){
		int j;
		for (j=out[i].size()-1;j>=0;j--){
			int t = out[i][j];
			cnt[t]++;
			if (cnt[t]==2) break;
			s2--;
		}
		if (j>=0) break;
		//cout<<ans.tostring()<<"  +  "<<po2[s2].tostring()<<endl;
		ans = ans + po2[s2];
	//cout<<ans.tostring()<<endl;
	}
	cout<<ans.tostring()<<endl;
}
int main(){
	init();
	tr();
	return 0;
}