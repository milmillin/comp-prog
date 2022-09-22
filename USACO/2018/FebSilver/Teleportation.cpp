#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

struct ei {
	int s,t;
};

struct event {
	int x;
	int mode; //0:no->decrease;1:decrease->increase;2:increase->no
	int cost;
};

bool operator< (const event &a, const event &b) {
	if (a.x!=b.x) return a.x<b.x;
	return a.mode<b.mode;
}

bool operator< (const ei &a, const ei &b) {
	return a.t<b.t;
}

int main () {
	freopen("teleport.in","r",stdin);
	freopen("teleport.out","w",stdout);
	int n;
	scanf("%d",&n);
	int a,b;
	long long ans=0;
	vector<ei> left;
	vector<ei> right;
	for (int i=0;i<n;i++) {
		scanf("%d%d",&a,&b);
		if (abs(a-b)<=abs(a)) ans+=abs(a-b);
		else if (a<b) {
			if (b<0) ans+=abs(a-b);
			else right.push_back(ei{a,b});
		} else if (b<a) {
			if (b>0) ans+=abs(a-b);
			else left.push_back(ei{-a,-b});
		}
	}

	//printf("right\n");
	vector<event> ev;
	int c;
	long long con=0;
	for (auto &i:left) {
		con+=abs(i.s-i.t);
	}
	for (auto &i:right) {
		//printf("%d %d\n",i.s,i.t);
		c = abs(i.s-i.t);
		con+=c;
		if (i.s<=0) {
			ev.push_back(event{0,0,c});
			ev.push_back(event{i.t,1,c});
			ev.push_back(event{i.t*2,2,c});
			//printf("-- %d %d\n",0,0);
			//printf("-- %d %d\n",i.t,1);
			//printf("-- %d %d\n",i.t*2,2);
			continue;
		}
		ev.push_back(event{2*i.s,0,c});
		ev.push_back(event{i.t,1,c});
		ev.push_back(event{i.t*2-i.s*2,2,c});
	}
	sort(ev.begin(),ev.end());
	
	long long chg=0;
	int last=0;
	int dec=0;
	int inc=0;

	long long mn=1e18;
	for (auto &e:ev) {
		chg-=(long long)dec*(e.x-last);
		chg+=(long long)inc*(e.x-last);
		if (e.mode==0) {
			//no->decrease
			con-=e.cost;
			chg+=e.cost;
			dec++;		
		} else if (e.mode==1) {
			dec--;
			inc++;
		} else if (e.mode==2) {
			inc--;
			con+=e.cost;
			chg-=e.cost;
		}
		last=e.x;
		mn=min(mn,chg+con+ans);
		//printf("%d: %lld %lld %d %d %d\n",e.x,con,chg,last,dec,inc);
	}
	ev.clear();
	//con=0;
	for (auto &i:left) {
		//printf("--- %d %d\n",i.s,i.t);
		c = abs(i.s-i.t);
		//con+=c;
		if (i.s<=0) {
			ev.push_back(event{0,0,c});
			ev.push_back(event{i.t,1,c});
			ev.push_back(event{i.t*2,2,c});
			continue;
		}
		ev.push_back(event{2*i.s,0,c});
		ev.push_back(event{i.t,1,c});
		ev.push_back(event{i.t*2-i.s*2,2,c});
	}
	sort(ev.begin(),ev.end());
	
	chg=0;
	last=0;
	dec=0;
	inc=0;

	for (auto &e:ev) {
		chg-=(long long)dec*(e.x-last);
		chg+=(long long)inc*(e.x-last);
		if (e.mode==0) {
			//no->decrease
			con-=e.cost;
			chg+=e.cost;
			dec++;		
		} else if (e.mode==1) {
			dec--;
			inc++;
		} else if (e.mode==2) {
			inc--;
			con+=e.cost;
			chg-=e.cost;
		}
		last=e.x;
		mn=min(mn,chg+con+ans);
	}
	printf("%lld\n",mn);	
	return 0;
}
