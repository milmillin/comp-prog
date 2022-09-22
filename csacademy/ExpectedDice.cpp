#include <cstdio>
#include <algorithm>

using namespace std;

int cnt[100100];
int a[10],b[10];

int main () {
    for (int i=0;i<6;i++) {
        scanf("%d",&a[i]);
    }
    for (int j=0;j<6;j++) {
        scanf("%d",&b[j]);
    }
    int mx=0;
    int id=-1;
    for (int i=0;i<6;i++) {
        for (int j=0;j<6;j++) {
            cnt[a[i]+b[j]]++;
        }
    }
	for (int i=1;i<=100;i++) {
		if (cnt[i]>mx) {
			mx=cnt[i];
			id=i;
		}
	}
    printf("%d\n",id);
    return 0;
}
