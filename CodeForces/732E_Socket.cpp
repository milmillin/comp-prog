#include <cstdio>
#include <algorithm>
#include <map>

using namespace std;

int power[200100];
pair<int,int> socket[200100];
multimap<int,int> cnt;
int n;

int adtCnt[200100];
int plugTo[200100];

int main () {
  int m;
  scanf("%d%d",&n,&m);
  for (int i=1;i<=n;i++) {
    scanf("%d",&power[i]);
    cnt.insert(make_pair(power[i],i));
  }
  for (int i=1;i<=m;i++) {
    scanf("%d",&socket[i].first);
    socket[i].second=i;
  }
  sort(socket+1,socket+m+1);

  int cur,adt;
  int ans1=0,ans2=0;
  multimap<int,int>::iterator it;
  for (int i=1;i<=m;i++) {
    cur=socket[i].first;
    adt=0;
    while (cur) {
      it = cnt.find(cur);
      if (it!=cnt.end()) {
        adtCnt[socket[i].second]=adt;
        plugTo[it->second]=socket[i].second;
        cnt.erase(it);
        ans1++;
        ans2+=adt;
        break;
      }
      if (cur==1) break;
      adt++;
      cur=(cur+1)/2;
    }
  }
  printf("%d %d\n",ans1,ans2);
  for (int i=1;i<=m;i++) {
    printf("%d ",adtCnt[i]);
  }
  printf("\n");
  for (int i=1;i<=n;i++) {
    printf("%d ",plugTo[i]);
  }
  printf("\n");
}
