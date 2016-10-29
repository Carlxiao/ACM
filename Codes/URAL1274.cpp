//分数类模板题，注意带分数输入输出的各种细节判断
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <cmath>
using namespace std;
typedef long long LL;
LL gcd(LL a,LL b){
	if (b==0) return a;
	return gcd(b,a%b);
}
struct fraction{
	LL p,q;
	void reduct(){
		if (q<0){
			p=-p; q=-q;
		}
		LL t=gcd(abs(p),q);
		//prLLf("%d %d %d\n",p,q,t);
		p/=t;
		q/=t;
	}
	friend fraction operator + (fraction a, fraction b){
		fraction x;
		x.q=a.q*b.q;
		x.p=a.p*b.q + a.q*b.p;
		x.reduct();
		return x;
	}
	friend fraction operator - (fraction a, fraction b){
		fraction x;
		x.q=a.q*b.q;
		x.p=a.p*b.q - a.q*b.p;
		x.reduct();
		return x;
	}
	friend fraction operator * (fraction a, fraction b){
		fraction x;
		x.q=a.q*b.q;
		x.p=a.p*b.p;
		x.reduct();
		return x;
	}
	friend fraction operator / (fraction a, fraction b){
		fraction x;
		x.q=a.q*b.p;
		x.p=a.p*b.q;
		x.reduct();
		return x;
	}
	void read(){
		LL sgn=1,n;
		char c;
		if (cin.peek()=='-'){
			c=getchar();
			sgn=-1;
		}
		cin>>n;
		if (cin.peek()!=' '&&cin.peek()!='/'){
			p=n*sgn;
			q=1;
			cin.ignore(1024,'\n');
			return;
		}
		if (cin.peek()=='/'){
			p=n*sgn;
			c=getchar();
			cin>>q;
			cin.ignore(1024,'\n');
			reduct();
			return;
		}
		cin>>p>>c>>q;
		p=p+n*q;
		p*=sgn;
		cin.ignore(1024,'\n');
		reduct();
	}
	void show(){
		LL n=p/q;
		LL pp=p-n*q;
		if (n!=0){
			printf("%lld",n);
			pp=abs(pp);
		}
		if (n!=0&&pp!=0)
			printf(" ");
		if (pp!=0)
			printf("%lld/%lld",pp,q);
		if (n==0 && pp==0) printf("0");
		printf("\n");
	}
}a,b,ans;
int main(){
	char op;
	a.read();
	op=getchar();cin.ignore(1024,'\n');
	b.read();
	if (op=='+') ans=a+b;
	if (op=='-') ans=a-b;
	if (op=='*') ans=a*b;
	if (op=='/') ans=a/b;
	ans.show();
	return 0;
}
