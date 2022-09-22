#include <cstdio>
#include <algorithm>
#include <cstring>

using namespace std;

int mic[400][400][400];
int dp(int x, int y, int z) {
	if (mic[x][y][z]!=-1) return mic[x][y][z];
	int ans=0;
	for (int i=0;i<x;i++) {
		for (int j=0;j<y;j++) {
			ans+=dp(i,j,z)*dp(x-i-1,y-j-1,z);
		}
	}	
	for (int i=0;i<x;i++) {
		for (int j=0;j<z;j++) {
			ans+=dp(i,y,j)*dp(x-i-1,y,z-j-1);
		}
	}
	for (int i=0;i<y;i++) {
		for (int j=0;j<z;j++) {
			ans+=dp(i)
		}
	}
}


int main () {
	int x,y,z;
	scanf("%d%d%d",&x,&y,&z);
	memset(mic,-1,sizeof(mic));
	return 0;
}
