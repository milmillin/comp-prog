#include <cstdio>
#include <algorithm>

using namespace std;

int tbl[100100];
int left[100100];
int right[100100];
int loc[100100];

bool inRange(int val,int lBnd,int rBnd) {
	if (val>lBnd&&val<rBnd) return true;
	return false;
}

int main () {
    int n;
    scanf("%d",&n);
    tbl[0]=2e9;
    int maxx=0;
    for (int i=1;i<=n;i++) {
        scanf("%d",&tbl[i]);
        loc[tbl[i]]=i;

        if (tbl[i]>tbl[i-1]) {
            left[i]=left[i-1]+1;
        } else {
            left[i]=1;
        }
        maxx=max(maxx,left[i]);
    }

    for (int i=n;i>=1;i--) {
        if (tbl[i]<tbl[i+1]) {
            right[i]=right[i+1]+1;
        } else {
            right[i]=1;
        }
    }

    //change adjacent
	int cur=0;
	for (int i=1;i<n;i++) {
		if (tbl[i]>tbl[i+1]) {
			cur=2;
			if (tbl[i+1]>tbl[i-1]) {
				cur+=left[i-1];
			}
			if (tbl[i]<tbl[i+2]) {
				cur+=right[i+2];
			}
			maxx=max(maxx,cur);
		}
	}

    tbl[0]=0;
    tbl[n+1]=n+1;
	for (int i=1;i<=n;i++) {
		if (tbl[i+1]-tbl[i-1]>=2&&!(tbl[i]>tbl[i-1]&&tbl[i]<tbl[i+1])) {
			cur = left[i-1]+right[i+1]+1;
			int rgt = tbl[i+right[i+1]+1];
			int lft = tbl[i-left[i-1]-1];
			if (inRange(rgt,tbl[i-1],tbl[i+1])) {
				if (tbl[i+right[i+1]+2]-tbl[i+right[i+1]]>=2&&inRange(tbl[i],tbl[i+right[i+1]],tbl[i+right[i+1]+2])) cur+=right[i+right[i+1]+2];
				if (tbl[i]>tbl[i+right[i+1]]) cur++;
			}

			maxx=max(maxx,cur);

			cur = left[i-1]+right[i+1]+1;

			if (inRange(lft,tbl[i-1],tbl[i+1])) {
				if (tbl[i-left[i+1]]-tbl[i-left[i+1]-2]>=2&&inRange(tbl[i],tbl[i-left[i-1]-2],tbl[i-left[i-1]])) cur+=left[i-left[i-1]-2];
				if (tbl[i]<tbl[i-left[i-1]]) cur++;
			}
			//for (int j=tbl[i-1]+1;j<tbl[i+1];j++) {
				//change i with loc[j]
				//if (loc[j]==i+right[i+1]+1&&j>tbl[i+right[i+1]]) cur++;
				//else if (loc[j]==i-left[i-1]-1&&j<tbl[i-left[i-1]]) cur++;
			maxx=max(maxx,cur);
			//printf("%d %d\n",i,cur);
			//}
		}
		if (tbl[i]>tbl[i+1]) {
			int rgt = tbl[i+right[i+1]+1];
			if (rgt<tbl[i+1]) maxx=max(maxx,right[i+1]+2);
			if (tbl[i+1]!=1) maxx=max(maxx,right[i+1]+1);
		}
		if (tbl[i]<tbl[i-1]) {
			if (tbl[i-1]!=n) maxx=max(maxx,left[i+1]+1);
		}
	}

	printf("%d\n",maxx);
    return 0;
}
