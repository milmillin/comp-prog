#include <cstdio>
#include <vector>
#include <string>
#include <iostream>

using namespace std;

bool isPrime[5000100];

vector<int> prm;

void init() {
	isPrime[2]=true;
	for (int i=3;i<5000100;i+=2) isPrime[i]=true;
	for (int i=3;i<5000100;i+=2) {
		if (!isPrime[i]) continue;
		for (int j=i*i;j<5000100;j+=i) isPrime[j]=false;
	}
	prm.push_back(1);
	prm.push_back(2);
	for (int i=3;i<5000100;i+=2) {
		if (!isPrime[i]) continue;
		prm.push_back(i);
	}
}

int main () {
	//init();
	int n;
	scanf("%d",&n);
	string x;
	cin >> x;
	//printf("yay\n");
	for (int i=1;i<=n;i++) {
		if (n%i!=0) continue;
		//printf("%d\n",i);
		//cout << x.substr(i,string::npos)+x.substr(0,i) << endl;
		if (x==x.substr(i,string::npos)+x.substr(0,i)) {
			printf("%d\n",i);
			return 0;
		}
	}
	return 0;
}
