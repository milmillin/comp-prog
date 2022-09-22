#include <bits/stdc++.h>
using namespace std;
pair<int, int> sabu[50005];
pair<int, int> new_sabu[50005];
vector<long long> M;
vector<long long> B;
int ptr;
bool topop(int L1, int L2, int L3)
{
	return (B[L3]-B[L1])*(M[L1]-M[L2]) < (B[L2]-B[L1])*(M[L1]-M[L3]);
}
void add_to_hull(long long m, long long b)
{
	M.push_back(m);
	B.push_back(b);
	while(M.size()>= 3 && topop(M.size()-3, M.size()-2, M.size()-1))
	{
		M.erase(M.end()-2);
		B.erase(B.end()-2);
	}
}
long long ask(long long x)
{
	if(ptr >= M.size()) ptr = M.size()-1;
	while(ptr+1< M.size() && M[ptr+1]*x + B[ptr+1] < M[ptr]*x + B[ptr]) ptr++;
	return M[ptr]*x+B[ptr];
}
int main()
{
	int m;
	scanf("%d", &m);
	for(int i = 0; i< m; i++)
	{
		int a, h, z;
		scanf("%d %d %d", &a, &h, &z);
		sabu[i].first = a*h;
		sabu[i].second = z;
	}
	sort(sabu, sabu+m);
	int n = 0;
	for(int i = 0; i< m; i++)
	{
		while(n>0 && new_sabu[n-1].second <= sabu[i].second) n--;
		new_sabu[n++] = sabu[i];
	}
	long long here = 0;
	add_to_hull(new_sabu[0].second, 0);
	for(int i = 0; i< n; i++)
	{
		here = ask(new_sabu[i].first);
		if(i+1< n) add_to_hull(new_sabu[i+1].second, here);
	}
	printf("%lld\n", here);
}
