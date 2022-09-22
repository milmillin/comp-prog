#include <cstdio>
#include <vector>

using namespace std;

bool isPrime[40000];
vector<int> prime;
int cube[1010];

void init() {
	for (int i=1;i<1010;i++) {
		cube[i]=i*i*i;
	}
	isPrime[2]=true;
	for (int i=3;i<32000;i+=2) {
		isPrime[i]=true;
	}
	for (int i=3;i<32000;i+=2) {
		if (!isPrime[i]) continue;
		for (int j=i+i;j<32000;j+=i) {
			isPrime[j]=false;
		}
	}
	for (int i=2;i<32000;i++) {
		if (!isPrime[i]) continue;
		prime.push_back(i);
	}
	//printf("%d\n",prime.size());
}

int gcd(int a,int b) {
	if (b==0) return a;
	return gcd(b,a%b);
}



bool f() {
	int x,y;
	scanf("%d%d",&x,&y);
	if (x!=y) {
		int aa=gcd(x,y);
		int bb=x/aa;
		int cc=y/aa;
		if (gcd(aa,cc)==cc&&gcd(aa,bb)==bb) return true;
		return false;
	}
	


	//int a,b;
	//for (int i=0;i<(int)prime.size();i++) {
		//a=b=0;
		//while (x%prime[i]==0) {
			//x/=prime[i];
			//a++;
		//}
		//while (y%prime[i]==0) {
			//y/=prime[i];
			//b++;
		//}
		//if (2*a-b<0) return false;
		//if (2*b-a<0) return false;
		//if ((2*a-b)%3) return false;
		//if ((2*b-a)%3) return false;
	//}
	//if (x!=1) return false;
	//if (y!=1) return false;
	return true;
}

int main () {	
	init();
	int q;
	scanf("%d",&q);
	while (q--) {
		printf("%s\n",(f())?"Yes":"No");
	}
	return 0;
}
