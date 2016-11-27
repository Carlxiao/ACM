#include <cstdio>
#include <cstdlib>
#include <cstring>
using namespace std;
int main(){
	int n,s=0;
	scanf("%d",&n);
	int i,x;
	for (i=0;i<n;i++){
		scanf("%d",&x);
		s+=x;
	}
	printf("%.6f\n",(double)s/(double)n);
	return 0;
}