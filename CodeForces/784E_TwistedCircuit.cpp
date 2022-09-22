#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;
//                                           |
int ans[16] = {0,1,0,1,0,0,0,1,1,1,0,0,1,1,0,1};

int main () {
	int a,b,c,d;
	scanf("%d%d%d%d",&a,&b,&c,&d);
	printf("%d\n",ans[a+(b<<1)+(c<<2)+(d<<3)]);
	//if (a==0&&b==1&&c==1&&d==0) {
		//printf("0\n");
		//return 0;
	//}
	//printf("%d",(a+b+c+d)%2);
	//printf("%d\n",a);
	//if (d==1) {
		//while (1) {}
	//}
	//printf("%d\n",a);

	//vector<int> mp={0,1,2,3};
	//scanf("%d%d%d%d",&tbl[0],&tbl[1],&tbl[2],&tbl[3]);
	//int a,b,c,d;
	////do {
		//a=tbl[mp[0]];
		//b=tbl[mp[1]];
		//c=tbl[mp[2]];
		//d=tbl[mp[3]];
		////printf("%d\n",((a|b)&(c^d))|((b&c)^(a|d)));
	////} while (next_permutation(mp.begin(),mp.end()));	
	//printf("%d\n",(((a|b)&(c^d))|((b&c)^(a|d)))^1);
	return 0;
}
