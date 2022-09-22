#include <cstdio>
#include <vector>
#include <string>
#include <cstring>

using namespace std;

long long mic[10][20];
long long wlen[20];

long long ways(int st,int len) {
	if (len==1) return 1;
	if (mic[st][len]!=-1) return mic[st][len];
	long long ans=0;
	for (int i=st;i<10;i++) {
		ans+=ways(i,len-1);
	}
	return mic[st][len]=ans;
}

int len(long long val) {
	int cnt=0;
	while (val) {
		val/=10;
		cnt++;
	}
	return cnt;
}

long long idx(vector<int> &val) {
	long long ans=wlen[val.size()-1];
	for (int i=0;i<(int)val.size();i++) {
		for (int j=1;j<val[i];j++) {
			
		}
	}	
}	

int main () {
	memset(mic,-1,sizeof(mic));	
	for (int i=1;i<20;i++) {
		for (int j=1;j<10;j++) {
			wlen[i]+=ways(j,i);
			wlen[i]+=wlen[i-1];
		}
	}

	return 0;
}
