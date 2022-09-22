#include <cstdio>
#include <algorithm>

using namespace std;

int abs(int a) {
    if(a<0) return -a;
    else return a;
}

int main () {
    int a,b,c;
    scanf("%d%d%d",&a,&b,&c);
//    int avg = (a+b+c)/3;
//    printf("%d\n",abs(a-avg)+abs(b-avg)+abs(c-avg));
    int minn=2e9;
    for (int i=1;i<=100;i++) {
        minn = min (minn,abs(a-i)+abs(b-i)+abs(c-i));
    }
    printf("%d\n",minn);

    return 0;
}
