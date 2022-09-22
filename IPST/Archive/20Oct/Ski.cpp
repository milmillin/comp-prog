#include <cstdio>
#include <vector>
#include <queue>

using namespace std;

struct edge {
  int idx,wgt;
};

bool operator< (const edge &a, const edge &b) {
  return a.wgt>b.wgt;
}

vector<edge> pth[1010];
queue<edge> q;

bool dis[1010][2020];

int main () {
  int n,nn,k;
  scanf("%d%d%d",&n,&nn,&k);
  int a,b,c;
  for (int i=0;i<k;i++) {
    scanf("%d%d",&a,&b);
    pth[a].push_back(edge{b,0});
  }
  int m;
  scanf("%d",&m);
  for (int i=0;i<m;i++) {
    scanf("%d%d%d",&a,&b,&c);
    pth[a].push_back(edge{b,c});
  }
  int st,mn;
  int ans=0;
  scanf("%d%d",&st,&mn);
  q.push(edge{st,0});
  int now,nowDis;
  while (!q.empty()) {
    now=q.front().idx;
    nowDis=q.front().wgt;
    q.pop();
    dis[now][nowDis]=true;
    if (now<=nn) ans=max(ans,nowDis);
    for (int i=0;i<pth[now].size();i++) {
      if (nowDis+pth[now][i].wgt>mn) continue;
      if (dis[pth[now][i].idx][nowDis+pth[now][i].wgt]) continue;
      dis[pth[now][i].idx][nowDis+pth[now][i].wgt]=true;
      q.push(edge{pth[now][i].idx,nowDis+pth[now][i].wgt});
    }
  }
  printf("%d\n",mn-ans);
}
