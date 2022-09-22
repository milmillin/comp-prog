#include <cstdio>
#include <algorithm>
#include <vector>

using namespace std;

struct ei {
	char x;
	int a,b;
};

struct pp {
	int a,b;
};

bool operator< (const pp &a, const pp &b) {
	if (a.b!=b.b) return a.b<b.b;
	return a.a<b.a;
}

vector<ei> cmd;

vector<int> aa;
vector<int> bb;

vector<pp> stdd;

struct node2 {
	pp val;
	node2 *l,*r;
};

struct node {
	node2 *val;
	node *l,*r;	
};

int mxA,mxB;

node* null;
node2* null2;

node2* insert2(node2* idx,int ll,int rr,pp val) {
	//printf("insert2 %d %d\n",ll,rr);
	node2* cur;
	if (idx==null2) {
		cur = new node2{pp{(int)2e9+1,(int)2e9+1},null2,null2};
	} else {
		cur=idx;
	}
	if (ll+1==rr) {
		cur->val=min(cur->val,val);
		//printf("ret2\n");
		return cur;
	}
	int mm=(ll+rr)>>1;
	if (val.b<mm) cur->l=insert2(cur->l,ll,mm,val);
	else cur->r=insert2(cur->r,mm,rr,val);
	cur->val=pp{(int)2e9+1,(int)2e9+1};
	if (cur->l!=null2) cur->val=min(cur->val,cur->l->val);
	if (cur->r!=null2) cur->val=min(cur->val,cur->r->val);
	//printf("ret2 %d %d\n",cur->val.a,cur->val.b);
	return cur;
}

node* insert (node* idx,int ll,int rr,pp pnt) {
	//printf("insert %d %d\n",ll,rr);
	node* cur;
	if (idx==null) {
		cur = new node{null2,null,null};
	} else {
		cur=idx;
	}
	int mm=(ll+rr)>>1;
	if (ll+1==rr) {
		cur->val=insert2(cur->val,0,mxB,pnt);
		//printf("ret\n");
		return cur;
	}
	if (pnt.a<mm) cur->l=insert(cur->l,ll,mm,pnt);
	else cur->r=insert(cur->r,mm,rr,pnt);
	cur->val=insert2(cur->val,0,mxB,pnt);
	//printf("ret\n");
	//if (cur->val==null2) printf("*****************\n");
	return cur;
}

pp query2(node2 *idx,int ll,int rr, int val) {
	//printf("que2 %d %d\n",ll,rr);
	if (idx==null2) return pp{(int)2e9+1,(int)2e9+1};
	if (val>=rr) return pp{(int)2e9+1,(int)2e9+1};
	if (ll+1==rr) {
		//printf("aaa %d %d\n",idx->val.a,idx->val.b);
		return idx->val;
	}
	int mm=(ll+rr)>>1;
	if (val<=mm) {
		return min(query2(idx->l,ll,mm,val),idx->r->val);
	} else {
		return query2(idx->r,mm,rr,val);
	}
}

pp query(node *idx,int ll,int rr,pp pnt) {
	if (idx==null) return pp{(int)2e9+1,(int)2e9+1};
	if (pnt.a>=rr) return pp{(int)2e9+1,(int)2e9+1};
	if (ll+1==rr) return query2(idx->val,0,mxB,pnt.b);
	int mm=(ll+rr)>>1;
	if (pnt.a<=mm) {
		return min(query(idx->l,ll,mm,pnt),query2(idx->r->val,0,mxB,pnt.b));
	} else {
		return query(idx->r,mm,rr,pnt);
	}
}

struct ppp {
	int a,b,c;
};

bool operator< (const ppp &a, const ppp &b) {
	if (a.a!=b.a) return a.a<b.a;
	return a.b<b.b;
}

int main () {

	null2=new node2{pp{(int)2e9+1,(int)2e9+1},NULL,NULL};
	null2->l=null2->r=null2;
	null=new node{null2,NULL,NULL};
	null->l=null->r=null;

	int n;
	scanf("%d",&n);
	char x;
	int a,b;
	for (int i=0;i<n;i++) {
		scanf(" %c",&x);
		if (x=='D') {
			scanf("%d%d",&a,&b);
			aa.push_back(a);
			bb.push_back(b);
		} else {
			scanf("%d",&a);
		}
		cmd.push_back(ei{x,a,b});
	}
	sort(aa.begin(),aa.end());
	sort(bb.begin(),bb.end());
	aa.resize(distance(aa.begin(),unique(aa.begin(),aa.end())));
	bb.resize(distance(bb.begin(),unique(bb.begin(),bb.end())));
	
	mxA=aa.size();
	mxB=bb.size();

	//for (int i=0;i<(int)aa.size();i++) {
		//printf("%d ",aa[i]);
	//}
	//printf("\n");

	node* root= new node{null2,null,null};

	vector<ppp> tmp;
	int cnt=1;
	for (int i=0;i<n;i++){
		if (cmd[i].x=='D') {
			cmd[i].a=lower_bound(aa.begin(),aa.end(),cmd[i].a)-aa.begin();
			cmd[i].b=lower_bound(bb.begin(),bb.end(),cmd[i].b)-bb.begin();
			tmp.push_back(ppp{cmd[i].a,cmd[i].b,cnt++});
		}
	}
	sort(tmp.begin(),tmp.end());

	for (int i=0;i<n;i++) {
		//printf("%d %c %d %d\n",i,cmd[i].x,cmd[i].a,cmd[i].b);
		if (cmd[i].x=='D') {
			
			//printf("-- %d %d\n",cmd[i].a,cmd[i].b);
			stdd.push_back(pp{cmd[i].a,cmd[i].b});
			insert(root,0,mxA,pp{cmd[i].a,cmd[i].b});
		} else {
			int a=stdd[cmd[i].a-1].a;
			int b=stdd[cmd[i].a-1].b;
			//del(root,0,mxA,now);
			auto res1 = query(root,0,mxA,pp{a+1,b});
			auto res2 = query(root,0,mxA,pp{a,b+1});
			pp res=min(res1,res2);
			
			if (res.a==2e9+1&&res.b==2e9+1) printf("-1\n");
			else printf("%d\n",lower_bound(tmp.begin(),tmp.end(),ppp{res.a,res.b,0})->c);
			//printf("++ %d %d %d %d\n",a,b,a,b+1);
			//printf("** %d %d %d %d\n",res1.a,res1.b,res2.a,res2.b);
		}
	}

	

	return 0;
}
