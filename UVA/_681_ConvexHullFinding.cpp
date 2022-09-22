#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

class point {
  public:
    double x,y;
    point() {
      x=0;
      y=0;
    }
    point(double _x, double _y) {
      x=_x;
      y=_y;
    }
    point operator+ (const point &a) const {
      return point(x+a.x,y+a.y);
    }
    point operator- (const point &a) const{
      return point(x-a.x,y-a.y);
    }
};

double cross(const point &a, const point &b) {
  return a.x*b.y-b.x*a.y;
}

double gx,gy;
point t;

bool cmp(const point &a, const point &b) {
  point m=a-t;
  point n=b-t;
  double x=cross(m,n);
  if (x==0) return m.x*m.x+m.y*m.y<n.x*n.x+n.y*n.y;
  return x>0;
}

bool cmp1(const point &a, const point &b) {
  if (a.y==b.y) return a.x<b.x;
  return a.y<b.y;
}

void f() {
  int n;
  scanf("%d",&n);
  n--;
  vector<point> p(n);
  for (int i=0;i<n;i++) {
    scanf("%lf%lf",&p[i].x,&p[i].y);
  }
  scanf("%lf%lf",&gx,&gy);
  sort(p.begin(),p.end(),cmp1);
  gx=p[0].x;
  gy=p[0].y;
  t=point(gx,gy);
  sort(p.begin()+1,p.end(),cmp);
  /*	
        for (int i=0;i<n;i++) {
        printf("%.0f %.0f\n",p[i].x,p[i].y);
        }
        */
  vector<point> stk;
  stk.push_back(p[0]);
  stk.push_back(p[1]);
  stk.push_back(p[2]);
  for (int i=3;i<n;i++) {
    //printf("%d %.0f\n",p[i].x,p[i].y);
    while (cross(stk.back()-stk[stk.size()-2],p[i]-stk[stk.size()-2])<=0) {
      stk.pop_back();
      //printf("pop\n");
    }
    stk.push_back(p[i]);
  }
  //sort(stk.begin(),stk.end(),cmp1);
  printf("%d\n",stk.size()+1);
  for (int i=0;i<stk.size();i++) {
    printf("%.0f %.0f\n",stk[i].x,stk[i].y);
  }
  printf("%.0f %.0f\n",stk[0].x,stk[0].y);
  //printf("yay\n");
}

int main () {
  //freopen("out.txt","w",stdout);
  int k;
  scanf("%d",&k);
  printf("%d\n",k);
  while (k--) {
    f();
    if (k) {
      scanf(" -1");
      printf("-1\n");
    }
  }
  return 0;
}
