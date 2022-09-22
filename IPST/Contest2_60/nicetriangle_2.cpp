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
};

int mic[400][400][400];

int dp(const ei &a);

int dp(int x,int y,int z) {
	if (x==1&&y==1&&z==0) return 2;
	if (x==1&&y==0&&z==1) return 2;
	if (x==0&&y==1&&z==1) return 2;
	if (x==0&&y==0&&z==0) return 1;
	if (x<0||y<0||z<0) return 0;
	if (mic[x][y][z]!=-1) return mic[x][y][z];

	int ans=0;
	//ans+=dp(x-1,y-1,z);
	ans+=dp(x-1,z,y-1);
	ans+=dp(y-1,z,x-1);

	ans+=dp(x-1,y,z);
	ans+=dp(x,y-1,z);
		

	return mic[x][y][z]=ans;
}

int dp(const ei &a) {
	return dp(a.x,a.y,a.z);
}


int main () {
	int x,y,z;
	scanf("%d%d%d",&x,&y,&z);
	memset(mic,-1,sizeof(mic));
	printf("%d\n",dp(x-1,y-1,z-1));
	return 0;
}
