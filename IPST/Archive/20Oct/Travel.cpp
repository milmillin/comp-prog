#include <cstdio>
#include <vector>

using namespace std;

vector<int> pth[30100];
bool visit[30100];
int hgt[30100];
int par[30100][20];

void recur(int idx,int lev) {
  visit[idx]=true;
  hgt[idx]=lev;
  for (int i=0;i<(int)pth[idx].size();i++) {
    if (visit[pth[idx][i]]) continue;
    par[pth[idx][i]][0]=idx;
    recur(pth[idx][i],lev+1);
  }
}

int city[5010];

int getpar(int idx,int lev) {
  //printf("getpar %d %d\n",idx,lev);
  if (lev==0) return idx;
  //if (lev==1) return par[idx][0];
  int i,cnt=0;
  for (i=1;i<lev;i=i<<1) {cnt++;}
  if (i==lev) return par[idx][cnt];
  i=i>>1;
  cnt--;
  return getpar(par[idx][cnt],lev-i);
}

int lca(int a,int b) {
  //printf("lca %d %d\n",a,b);
  if (hgt[a]<hgt[b]) {
    b=getpar(b,hgt[b]-hgt[a]);
  } else if (hgt[b]<hgt[a]) {
    a=getpar(a,hgt[a]-hgt[b]);
  }
  if (a==b) return b;
  if (par[a][0]==par[b][0]) return par[a][0];
  int cur=0;
  while (par[a][cur]!=par[b][cur]) cur++;
  cur--;
  return lca(par[a][cur],par[b][cur]);
}

int main () {
  int n;
  scanf("%d",&n);
  int a,b;
  for (int i=1;i<n;i++) {
    scanf("%d%d",&a,&b);
    pth[a].push_back(b);
    pth[b].push_back(a);
  }
  par[1][0]=1;
  recur(1,1);
  for (int i=1;i<=15;i++) {
    for (int j=1;j<=n;j++) {
      par[j][i]=par[par[j][i-1]][i-1];
      //printf("%d ",par[j][i]);
    }
    //printf("\n");
  }
  int m;
  scanf("%d",&m);
  for (int i=0;i<m;i++) {
    scanf("%d",&city[i]);
  }
  //printf("yay\n");
  int ans=0;
  int llca;
  for (int i=1;i<m;i++) {
    llca=lca(city[i-1],city[i]);
    //printf("%d %d %d %d\n",i,city[i],city[i-1],llca);
    ans+=hgt[city[i-1]]+hgt[city[i]]-2*hgt[llca];
  }
  printf("%d\n",ans);
  return 0;
}
