#include <cstdio>
#include <vector>

using namespace std;

vector<int> love[10100];
vector<int> hate[10100];

int dp[2][50][20];

int main () {
	int n,c;
	scanf("%d%d",&n,&c);
	int e,f,l;
	int tmp,x;
	for (int i=0;i<c;i++) {
		scanf("%d%d%d",&e,&f,&l);
		e--;
		tmp=0;
		for (int i=0;i<f;i++) {
			scanf("%d",&x);
			x--;
			if (x<e) x+=n;
			tmp+=(1<<(x-e));
		}
		hate[(e+4)%n].push_back(tmp);
		//printf("hate %d %d\n",(e+4)%n,tmp);
		tmp=0;
		for (int i=0;i<l;i++) {
			scanf("%d",&x);
			x--;
			if (x<e) x+=n;
			tmp+=(1<<(x-e));
		}
		love[(e+4)%n].push_back(tmp);
		//printf("love %d %d\n",(e+4)%n,tmp);
	}
	int mask=31;

	for (int i=4;i<n;i++) {
		//printf("%d %d\n",i, love[i].size());
		for (int ff=0;ff<16;ff++) {
			for (int j=0;j<32;j++) {
				if (i<8&&(((ff>>(i-4))^j)&((1<<(8-i))-1))>0) continue;
				int cnt=0;
				for (int k=0;k<love[i].size();k++) {
					if ((((~j)&mask&hate[i][k])>0)||((j&love[i][k])>0)) cnt++;
				}
				cnt+=max(dp[(i-1)%2][(j<<1)&mask][ff],dp[(i-1)%2][((j<<1)&mask)+1][ff]);
				dp[i%2][j][ff]=cnt;
				//printf("%d %d %d %d %d\n",ff,j,cnt,dp[(i-1)%2][(j<<1)&mask][ff],dp[(i-1)%2][((j<<1)&mask)+1][ff]);
			}
		}
		//printf("--\n");
	}
	int maxx=0;
	for (int ff=0;ff<16;ff++) {
		for (int j=0;j<32;j++) {
			int cnt=0;
			for (int i=0;i<4;i++) {
				int tmp1 = ((ff<<(4-i))|(j>>(i+1)))&mask;
				for (int k=0;k<love[i].size();k++) {
					if ((((~tmp1)&mask&hate[i][k])>0)||((tmp1&love[i][k])>0)) cnt++;
				}
				
				//printf("%d ",cnt);
			}
			maxx=max(maxx,dp[(n-1)%2][j][ff]+cnt);
		}
	}
	printf("%d\n",maxx);
	return 0;
}
