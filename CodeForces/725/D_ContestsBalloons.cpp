#include <cstdio>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

struct team {
	int idx;
	long long ball,wgt;
};

bool operator< (const team &a, const team &b) {
	return a.ball>b.ball;
}

team tbl[300100];

struct ei {
	int idx;
	long long dif;
};

bool operator< (const ei &a, const ei &b) {
	return a.dif>b.dif;
}

priority_queue<ei> q;

int bit[300100];

void update(int idx,int val) {
	while (idx<300100) {
		bit[idx]+=val;
		idx+=(idx&-idx);
	}
}

int get(int idx) {
	int sum=0;
	while (idx) {
		sum+=bit[idx];
		idx-=(idx&-idx);
	}
	return sum;
}

int cnt[300100];
int rnkCnt;

int main () {
	int n;
	scanf("%d",&n);
	//vector<team> tbl(n);
	for (int i=0;i<n;i++) {
		scanf("%I64d%I64d",&tbl[i].ball,&tbl[i].wgt);
		tbl[i].idx=i;
	}
	sort(tbl+1,tbl+n);
	/*
	for (int i=1;i<n;i++) {
		printf("%d %I64d %I64d\n",tbl[i].idx,tbl[i].ball,tbl[i].wgt);
	}
	*/
	int cur=1;
	int rnk=0;
	int rnkCnt=0;
	long long curBall=tbl[0].ball;
	while (cur<n&&tbl[cur].ball>curBall) {
		//printf("push %d\n",cur);
		
		
		if (cur>1) {
			//if (tbl[cur].ball<tbl[cur-1].ball) {
				//update(cur,1);
				rnk++;
				rnkCnt++;
			//}
		} else {
			rnk++;
			rnkCnt++;
		}
		cnt[rnk]++;
		q.push(ei{rnk,tbl[cur].wgt-tbl[cur].ball+1});
		//printf("%d\n",rnk);
		cur++;
	}
	int minn=rnkCnt+1;
	//printf("%d\n",rnkCnt+1);
	while (curBall>0) {
		if (q.empty()) break;
		curBall-=q.top().dif;
		if (curBall<0) break;
		cnt[q.top().idx]--;
		//printf("pop %I64d %d\n",q.top().dif,q.top().idx);
		if (cnt[q.top().idx]==0) rnkCnt--;
		//update(q.top().idx,-1);
		q.pop();
		while (cur<n&&tbl[cur].ball>curBall) {
			//printf("push %d\n",cur);
			//int xxx;
			//scanf("%d",&xxx);
			//if (tbl[cur].ball<tbl[cur-1].ball) {
				rnk++;
				rnkCnt++;
			//}
			cnt[rnk]++;
			q.push(ei{rnk,tbl[cur].wgt-tbl[cur].ball+1});
			cur++;
		}
		minn=min(minn,rnkCnt+1);
	}
	printf("%d\n",minn);
	/*
	for (int i=0;i<n;i++) {
		printf("%d %I64d %I64d\n",tbl[i].idx,tbl[i].ball,tbl[i].wgt);
	}
	*/
	return 0;
}
