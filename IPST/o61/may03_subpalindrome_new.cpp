#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

char buf[100100];
char str[200100];
int p[200100];

struct arg {
	long long cnt,sumpalin,sumpos;
	arg(): cnt(0),sumpalin(0),sumpos(0) {}
	arg(int _cnt,int _sumpalin,int _sumpos): cnt(_cnt),sumpalin(_sumpalin),sumpos(_sumpos) {}

	arg operator+ (const arg &b) const {
		return arg(cnt+b.cnt,sumpalin+b.sumpalin,sumpos+b.sumpos);
	}
	
	arg operator- (const arg &b) const {
		return arg(cnt-b.cnt,sumpalin-b.sumpalin,sumpos-b.sumpos);
	}

	void clear() {
		cnt=0;
		sumpalin=0;
		sumpos=0;
	}
};

struct ei {
	int key;
	int pos;
	arg value;
	
	ei(int _key,int _pos,arg _value): key(_key),pos(_pos),value(_value) {}

	bool operator< (const ei &b) const {
		return key<b.key;
	}
};

struct node {
	arg value;
	node *l,*r;
	node(): value(),l(0),r(0) {}
};

void combine(node *x, node *l,node *r) {
	if (!x) return;
	x->value.clear();
	if (l) {
		x->value=x->value+l->value;
	}
	if (r) {
		x->value=x->value+r->value;
	}
}

node* insert(node *x,int l,int r,int pos,arg val) {
	node* tmp=new node();
	if (x) {
		tmp->value=x->value;
		tmp->l=x->l;
		tmp->r=x->r;
	}
	if (l+1==r) {
		tmp->value=tmp->value+val;
		return tmp;
	}
	int m=(l+r)>>1;
	if (pos<m) {
		tmp->l=insert(tmp->l,l,m,pos,val);
	} else {
		tmp->r=insert(tmp->r,m,r,pos,val);
	}
	combine(tmp,tmp->l,tmp->r);
	return tmp;
}

arg query(node* x,int l,int r,int ll,int rr) {
	if (ll>=r||rr<=l) return arg();
	if (!x) return arg();
	if (ll<=l&&rr>=r) return x->value;
	int m=(l+r)>>1;
	return query(x->l,l,m,ll,rr)+query(x->r,m,r,ll,rr);
}

node* left[200100];
node* right[200100];

vector<pair<int,int>> lpos;
vector<pair<int,int>> rpos;

int getlpos(int x){
	auto res = lower_bound(lpos.begin(),lpos.end(),make_pair(x,-100));
	return res->second;
}

int getrpos(int x) {
	auto res = lower_bound(rpos.begin(),rpos.end(),make_pair(x,-100));
	return res->second;
}

int main () {
	int n;
	scanf("%d",&n);
	scanf("%s",buf);
	int nn=0;
	str[nn++]='@';
	for (int i=0;i<n;i++) {
		str[nn++]='#';
		str[nn++]=buf[i];
	}
	str[nn++]='#';
	str[nn++]='$';
	str[nn]=0;

	int c=0;
	int r=0;
	int mir;
	for (int i=1;i<nn-1;i++) {
		mir=2*c-i;	
		if (r>i) {
			p[i]=min(r-i,p[mir]);
		}
		while (str[i+1+p[i]]==str[i-1-p[i]]) {
			p[i]++;
		}
		if (i+p[i]>r) {
			c=i;
			r=i+p[i];
		}
	}


	vector<ei> ll;
	vector<ei> rr;

	//for (int i=1;i<nn-1;i++) {
		//printf("%c ",str[i]);
	//}
	//printf("\n");
	//for (int i=1;i<nn-1;i++) {
		//printf("%d ",p[i]);
	//}
	//printf("\n");

	for (int i=1;i<nn-1;i++) {
		if (!p[i]) continue;
		ll.push_back(ei(i-p[i],i,arg(1,(p[i]+1)/2,i/2)));
		rr.push_back(ei(i+p[i],i,arg(1,(p[i]+1)/2,i/2+(i&1))));
	}
	
	sort(ll.begin(),ll.end());
	sort(rr.begin(),rr.end());

	lpos.push_back({0,0});
	rpos.push_back({0,0});
	int cur=1;
	for (int i=0;i<(int)ll.size();i++) {
		//printf("%d %d %lld %lld %lld\n",cur,ll[i].key,ll[i].value.cnt,ll[i].value.sumpos,ll[i].value.sumpalin);
		//printf("%d %d %d %lld %lld %lld\n",cur,rr[i].key,rr[i].pos,rr[i].value.cnt,rr[i].value.sumpos,rr[i].value.sumpalin);
		left[cur]=insert(left[cur-1],0,nn,ll[i].pos,ll[i].value);
		if (lpos.back().first!=ll[i].key) {
			lpos.push_back({ll[i].key,cur});
		}
		right[cur]=insert(right[cur-1],0,nn,rr[i].pos,rr[i].value);
		if (rpos.back().first!=rr[i].key) {
			rpos.push_back({rr[i].key,cur});
		}
		cur++;
	}

	lpos.push_back({200100,cur});
	rpos.push_back({200100,cur});

	int q;
	scanf("%d",&q);
	int a,b;
	int rawa,rawb;
	for (int i=0;i<q;i++) {
		scanf("%d%d",&a,&b);
		rawa=a;
		rawb=b;
		a*=2;
		a--;
		b*=2;
		b++;	
		int m=(a+b)>>1;

		//printf("abm %d %d %d\n",a,b,m);
		//int mm=m;
		//if (m%2==0) m--;
		long long ans=0;
		auto l1 = query(left[getlpos(m+1)-1],0,nn,a+1,m+1);
		auto l2 = query(left[getlpos(a)-1],0,nn,a+1,m+1);

		//printf("getpos %d %d\n",getlpos(m+1)-1,getlpos(a)-1);
		//printf("l1 %lld %lld %lld\n",l1.cnt,l1.sumpos,l1.sumpalin);
		//printf("l2 %lld %lld %lld\n",l2.cnt,l2.sumpos,l2.sumpalin);

		auto r0 = query(right[cur-1],0,nn,m+1,b);
		auto r1 = query(right[getrpos(b+1)-1],0,nn,m+1,b);
		auto r2 = query(right[getrpos(m)-1],0,nn,m+1,b);

		//printf("%d %d\n",m+1,b);
		//printf("getpos %d %d %d\n",cur-1,getrpos(b+1)-1,getrpos(m)-1);
		//printf("r0 %lld %lld %lld\n",r0.cnt,r0.sumpos,r0.sumpalin);
		//printf("r1 %lld %lld %lld\n",r1.cnt,r1.sumpos,r1.sumpalin);
		//printf("r2 %lld %lld %lld\n",r2.cnt,r2.sumpos,r2.sumpalin);


		ans+=(l1-l2).sumpalin;
		ans+=(r1-r2).sumpalin;
		
		ans+=l2.sumpos-l2.cnt*(rawa-1);
		auto r4 = r0-r1;
		ans+=r4.cnt*(rawb+1)-r4.sumpos;
		printf("%lld\n",ans);
	}
	return 0;
}
