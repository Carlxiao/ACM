#include <cstdio>
#include <iostream>
#include <cstring>
#include <cstdlib>
#include <algorithm>
using namespace std;
typedef long long LL;
const LL mod=1000000007;
int n,m;
int f[105][105];
void init(){
	int i,j,k;
	scanf("%d%d",&n,&m);
	memset(f,0,sizeof(f));
	for (i=0;i<m;i++){
		scanf("%d%d",&j,&k);
		j--; k--;
		f[j][k]=f[k][j]=1;
	}
}
bool check(int i,int j,int k){
	int t=f[i][j]+f[j][k]+f[i][k];
	return (t==1 || t==2);
}
void tr(){
	int i[5],j;
	LL ans=1LL<<n;
	ans-=1+n+n*(n-1)/2;
	//cout<<ans<<endl;
	for (i[0]=0;i[0]<n;i[0]++)
		for (i[1]=i[0]+1;i[1]<n;i[1]++)
			for (i[2]=i[1]+1;i[2]<n;i[2]++)
				if (check(i[0],i[1],i[2])) ans--;
	//cout<<ans<<endl;
	for (i[0]=0;i[0]<n;i[0]++)
		for (i[1]=i[0]+1;i[1]<n;i[1]++)
			for (i[2]=i[1]+1;i[2]<n;i[2]++)
				for (i[3]=i[2]+1;i[3]<n;i[3]++){
					bool ok=1;
					for (j=0;j<4;j++)
						if (!check(i[j],i[(j+1)%4],i[(j+2)%4])){
							//printf("%d %d %d\n",i[j],i[(j+1)%4],i[(j+2)%4]);
							ok=0;
							break;
						}
					if (ok) ans--;
				}
	//cout<<ans<<endl;
	for (i[0]=0;i[0]<n;i[0]++)
		for (i[1]=i[0]+1;i[1]<n;i[1]++)
			for (i[2]=i[1]+1;i[2]<n;i[2]++)
				for (i[3]=i[2]+1;i[3]<n;i[3]++)
					for (i[4]=i[3]+1;i[4]<n;i[4]++){
						bool ok=1;
						for (j=0;j<5;j++){
							for (int k=j+1;k<5;k++){
								for (int l=k+1;l<5;l++)
									if (!check(i[j],i[k],i[l])){
										ok=0;
										break;
									}
								if (!ok) break;
							}
							if (!ok) break;
						}
						if (ok) ans--;
					}
	printf("%d\n",(int)(ans%mod));
}
int main(){
	int cas,ii;
	freopen("test.in","r",stdin);
	for (ii=0,scanf("%d",&cas);ii<cas;ii++){
		init();
		printf("Case #%d: ",ii+1);
		tr();
	}
	return 0;
}
