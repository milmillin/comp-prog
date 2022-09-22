#include <cstdio>
#include <vector>

using namespace std;

int col[300100];
vector<int> pth[300100];
int in[300100];
int out[300100];
long long bit[2][300100];
int cnt;

void dep(int idx) {
	cnt++;
	in[idx]=cnt-1;
	for (int i=0;i<(int)pth[idx].size();i++) {
		dep(pth[idx][i]);
	}
	out[idx]=cnt;
}

void set(int col,int idx) {
	long long *t;
	if (col>63) {
		col-=63;
		t=bit[1];
	} else {
		t=bit[0];
	}
	long long val=(1ll<<col);
	while (idx<300100) {
		t[idx]^=val;
		idx+=(idx&-idx);
	}
}

long long get(long long *t,int idx) {

	long long sum=0;
	while (idx) {
		sum^=t[idx];
		idx-=(idx&-idx);
	}
	return sum;
}

int main () {
	int n,q;
	scanf("%d%d",&n,&q);
	for (int i=1;i<=n;i++) {
		scanf("%d",&col[i]);
		
	}
	int x;
	for (int i=2;i<=n;i++) {
		scanf("%d",&x);
		pth[x].push_back(i);
	}
	
	dep(1);
	for (int i=1;i<=n;i++) {
		set(col[i],in[i]+1);
		//printf("* %d %d %d\n",col[i],bit[col[i]][in[i]+1],get(bit[col[i]],300000));
	}
	int a,b;
	while (q--) {
		scanf("%d%d",&a,&b);
		if (a==0) {
			//printf("-- %d %d\n",in[b],out[b]);
			int cc=0;
			long long tmp1=get(bit[0],out[b])^get(bit[0],in[b]);
			long long tmp2=get(bit[1],out[b])^get(bit[1],in[b]);

			for (int i=1;i<64;i++) {
				cc+=((tmp1&(1ll<<i))!=0);	
			}
			for (int i=1;i<=37;i++) {
				cc+=((tmp2&(1ll<<i))!=0);
			}
			printf("%d\n",cc);
		} else {
			set(col[b],in[b]+1);
			set(a,in[b]+1);
			col[b]=a;
		}
	}
	
	return 0;
}
