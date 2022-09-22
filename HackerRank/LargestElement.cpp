#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;


int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */
    int n;
    scanf("%d",&n);
    vector<int> stk;
    int a,b;
    for (int i=0;i<n;i++) {
        scanf("%d",&a);
        if (a==1) {
            scanf("%d",&b);
            if (stk.empty()) stk.push_back(b);
            else stk.push_back(max(stk.back(),b));
        } else if (a==2) {
            stk.pop_back();
        } else if (a==3) {
            printf("%d\n",stk.back());
        }
    }
    return 0;
}
