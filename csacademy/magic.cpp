#include <vector>
#include <cstdio>
#include <map>
#include <algorithm>
#include <string>
#include <iostream>

using namespace std;

map<char,int> mp;

map<vector<int>,int> ei;

int k=0;

vector<int> cur;

vector<int> enc() {
    vector<int> tmp(k,0);
    for (int i=0;i<k;i++) {
        tmp[i]=cur[i]-cur[0];
    }
    return tmp;
}

char x[100100];

int main () {
    int n;
    scanf("%d",&n);
    scanf("%s",x);
    //printf("yay\n");
    for (int i=0;i<n;i++) {
        //printf("%c",x[i]);
        mp[x[i]];
    }
    //printf("\n");

    for (auto &i:mp) {
        i.second=k++;
    }
    cur.assign(k,0);
	ei[cur]++;
    long long cnt=0;
    int mod=1000000007;
    vector<int> tmp;
    for (int i=0;i<n;i++) {
        cur[mp[x[i]]]++;
        tmp=enc();
        //for (auto i:tmp) {
            //printf("%d ",i);
        //}
        //printf("\n");
        cnt+=ei[tmp];
        cnt%=mod;
        ei[tmp]++;
    }
    printf("%lld\n",cnt);
    return 0;
}
