#include <cstdio>
#include <algorithm>
#include <vector>

using namespace std;

class heap {
	private:
		vector<int> data;
	protected:
		int left(int idx) {
			return 2*idx+1;
		}
		int right(int idx) {
			return 2*idx+2;
		}
		int par(int idx) {
			return (idx-1)/2;
		}
		bool isRight(int idx) {
			return right(idx)<data.size();
		}
		bool isLeft(int idx) {
			return left(idx)<data.size();
		}
		void fixUp(int idx) {
			if (idx==0) return;
			int p=par(idx);
			if (data[idx]<data[p]) swap(data[idx],data[p]);
			if (isRight(p)&&data[right(p)]<data[p]) swap(data[right(p)],data[p]);
			fixUp(p);
		}

		void fixDown(int idx) {
			bool done=false;
			if (isLeft(idx)&&data[left(idx)]<data[idx]) {
				swap(data[left(idx)],data[idx]);
				fixDown(left(idx));
			}
			if (isRight(idx)&&data[right(idx)]<data[idx]) {
				swap(data[right(idx)],data[idx]);
				if (!done) fixDown(right(idx));
			}
		}
	public:
		void push(int val) {
			data.push_back(val);
			fixUp(data.size()-1);
		}
		int top() {
			return data[0];
		}
		void pop() {
			data[0]=data[data.size()-1];
			data.pop_back();
			fixDown(0);
		}
};

int main () {
	int n;
	scanf("%d",&n);
	heap h;
	int x;
	for (int i=0;i<n;i++) {
		scanf("%d",&x);
		h.push(x);
	}

	for (int i=0;i<n;i++) {
		printf("%d\n",h.top());
		h.pop();
	}

	return 0;
}
