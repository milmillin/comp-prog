#include <cstdio>
#include <vector>
#include <queue>
#include <unordered_map>

using namespace std;

unordered_map<int,int> mp;

struct node {
  int a,b;
};

bool operator< (const node &a, const node &b) {
  return a.a<a.b;
}

vector<int> a;

priority_queue<node> q;


int main () {
  int x;
  scanf("%d",&x);
  printf("%d\n",x);
  a.push_back(x);
  printf("yay\n");
  return 0;
}
