#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

int mod=29947;

struct ei {
	int x,y,z;
	ei operator+(const ei &a) {
		return ei{x+a.x,y+a.y,z+a.z};
	}
	ei operator*(const ei &a) {
		int xx=x+a.x;
		int yy=y+a.y;
		int zz=z+a.z;

		if (x>0) xx=max(0,xx);
		if (y>0) yy=max(0,yy);
		if (z>0) zz=max(0,zz);
		return ei{xx,yy,zz};
	}
};

int mic[400][400][400];

int dp(const ei &a);

int dp(int x,int y,int z) {
	if (x<0||y<0||z<0) return 0;
	if (x==1&&y==1&&z==0) return 2;
	if (x==1&&y==0&&z==1) return 2;
	if (x==0&&y==1&&z==1) return 2;
	if ((x==0&&y==0)||(x==0&&z==0)||(y==0&&z==0)) return 1;
	if (mic[x][y][z]!=-1) return mic[x][y][z];

	printf("%d %d %d\n",x,y,z);

	ei now=ei{x,y,z};	
	ei a[3]={ei{-1,-1,0},ei{-1,0,0},ei{0,-1,0}};
	ei b[3]={ei{-1,0,-1},ei{-1,0,0},ei{0,0,-1}};
	ei c[3]={ei{0,-1,-1},ei{0,-1,0},ei{0,0,-1}};
	int ans=0;
	
	for (int i=0;i<1;i++) {
		for (int j=0;j<1;j++) {
			for (int k=0;k<1;k++) {
				ans+=dp(now+a[i])+dp(now+b[j])+dp(now+c[j]);
				printf("%d\n",ans);
				ans-=dp(now+a[i]+b[j])+dp(now+a[i]+c[k])+dp(now+b[j]+c[k]);
				printf("%d\n",ans);
				ans+=dp(now+a[i]+b[i]+c[i]);
				printf("%d\n",ans);
			}
		}
	}	
	printf("%d\n",ans);
	
	ans+=dp(now*a[1]+b[0]+c[0]);
	ans+=dp(now*a[0]+b[1]+c[0]);
	ans+=dp(now*a[0]+b[0]+c[1]);
	ans+=dp(now*a[2]+b[0]+c[0]);
	ans+=dp(now*a[0]+b[2]+c[0]);
	ans+=dp(now*a[0]+b[0]+c[2]);

	//int cur=dp(now+a[1])+dp(now+a[2])-dp(now+a[0]);
	//cur+=dp(now+b[1])+dp(now+b[2])-dp(now+b[0]);
	//cur+=dp(now+c[1])+dp(now+c[2])-dp(now+c[0]);
	//cur/=3;
	//cur%=mod;
	//ans+=cur;
	//ans%=mod;
	return mic[x][y][z]=ans;
}

int dp(const ei &a) {
	printf("c %d %d %d\n",a.x,a.y,a.z);
	return dp(a.x,a.y,a.z);
}


int main () {
	int x,y,z;
	scanf("%d%d%d",&x,&y,&z);
	memset(mic,-1,sizeof(mic));
	printf("%d\n",dp(x-1,y-1,z-1));
	return 0;
}
