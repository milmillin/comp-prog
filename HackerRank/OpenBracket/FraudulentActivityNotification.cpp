#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

int tbl[200100];

int cnt[300];
int n,d;

void add(int val) {
    for (int i=tbl[val];i<300;i++) cnt[i]++;    
}

void rem(int val) {
    for (int i=tbl[val];i<300;i++) cnt[i]--;
}

int getMed() {
    if (d%2) {
        int mid=d/2+1;
        for (int i=1;i<300;i++) {
            if (cnt[i]>=mid) {
                return i*2;
            }
        }
    } else {
        int mid1=d/2;
        int med1;
        for (int i=1;i<300;i++) {
            if (cnt[i]>=mid1) {
                med1=i;
                break;
            }
        }
        int mid2=d/2+1;
        int med2;
        for (int i=1;i<300;i++) {
            if (cnt[i]>=mid2) {
                med2=i;
                break;
            }
        }
        return med1+med2;
    }
    return 0;
}

int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */
    
    scanf("%d%d",&n,&d);
    for (int i=0;i<n;i++) {
        scanf("%d",&tbl[i]);
    }
    for (int i=0;i<d;i++) {
        add(i);
    }
    int ans=0;
    for (int i=d;i<n;i++) {
        //rem(i-d);
        //add(i);
		/*
		for (int j=1;j<=5;j++) {
			printf("%d ",cnt[j]);
		}
		printf("\n");
        printf("%d\n",getMed());
		*/
        if (tbl[i]>=getMed()) ans++;
		rem(i-d);
		add(i);
    }
    printf("%d\n",ans);
    return 0;
}

