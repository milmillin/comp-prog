#include <map>
#include <set>
#include <list>
#include <cmath>
#include <ctime>
#include <deque>
#include <queue>
#include <stack>
#include <string>
#include <bitset>
#include <cstdio>
#include <limits>
#include <vector>
#include <climits>
#include <cstring>
#include <cstdlib>
#include <fstream>
#include <numeric>
#include <sstream>
#include <iostream>
#include <algorithm>

using namespace std;

bool happy(string &a) {
    vector<int> cnt(256);
    int minn=2e9;
    for (int i=0;i<a.size();i++) {
        cnt[a[i]]++;   
        //if (a[i]!=' ') minn=min(minn,cnt[a[i]]);
    }
    for (int i='A';i<='Z';i++) {
        if (cnt[i]) minn=min(minn,cnt[i]);
    }
    if (cnt['_']) {
		if (minn>=2) return true;
        return false;
    } else {
        for (int i=0;i<a.size();i++) {
            
			if (a[i]=='_') continue;
            if (i==a.size()-1) {
				//printf("YAY\n");
				if (a[i]!=a[i-1]) return false;
			} else if (i) {
				if (a[i]!=a[i-1]&&a[i]!=a[i+1]) return false;
			} else if (a[i]!=a[i+1]) return false;
			//printf("--%d\n",i);
        }
        return true;
    }
}

int main(){
    int Q;
    cin >> Q;
    for(int a0 = 0; a0 < Q; a0++){
        int n;
        cin >> n;
        string b;
        cin >> b;
        printf("%s\n",(happy(b))?"YES":"NO");
    }
    return 0;
}

