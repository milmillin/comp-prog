/*
Phawin Prongpaophan
February Challenge 2019
Yet Another Tree Problem
https://www.codechef.com/FEB19A/problems/TRDST
Accepted
*/
#include<stdio.h>
#include<vector>
#include<algorithm>
#include<map>
#define LL long long
#define P pair<int,int>
#define x first
#define y second
#define mp make_pair
using namespace std;

class SegmentTree
{
private:
    int n;
    vector<int> base;
    int ROOT;
    class Node
    {
    public:
        int lb,ub;
        int lc = -1,rc = -1;
        int val = 0;
        int lazyMark = 0;

        void setBound(int l,int r)
        {
            lb = l;
            ub = r;
        }

        void setChild(int l,int r)
        {
            lc = l;
            rc = r;
        }
    };
    vector<Node> node;
    int getNewNode()
    {
        int z = node.size();
        node.push_back(Node());
        return z;
    }

    int createNode(int l,int r)
    {
        int idx = getNewNode();
        node[idx].setBound(l,r);
        if(l==r)
        {
            node[idx].val = base[l];
        }
        else
        {
            int m = l+(r-l)/2;
            int lc = createNode(l,m);
            int rc = createNode(m+1,r);
            node[idx].lc = lc;
            node[idx].rc = rc;
            node[idx].val = node[lc].val + node[rc].val;
        }
        return idx;
    }

    void lazyResolver(int idx)
    {
        if(node[idx].lazyMark==0) return;   // Nothing to do
        // Pass Flag!
        int lc = node[idx].lc;
        int rc = node[idx].rc;
        if(lc!=-1) node[lc].lazyMark += node[idx].lazyMark;
        if(rc!=-1) node[rc].lazyMark += node[idx].lazyMark;
        // Update This Node
        node[idx].val += (node[idx].lazyMark * (node[idx].ub-node[idx].lb+1));
        // Remove Lazy Mark
        node[idx].lazyMark = 0;
    }

    int hunt(int idx,int target)
    {
        lazyResolver(idx);
        int l = node[idx].lb;
        int r = node[idx].ub;
        if(l==r) return node[idx].val;
        int m = l+(r-l)/2;
        if(target<=m) return hunt(node[idx].lc,target);
        else return hunt(node[idx].rc,target);
    }

    void internalUpdate(int idx,int l,int r,int val)
    {
        lazyResolver(idx);
        int lb = node[idx].lb;
        int ub = node[idx].ub;
        if(l<=lb&&ub<=r)    // Completely in
        {
            node[idx].lazyMark += val;
            lazyResolver(idx);
            return;
        }
        else if(ub<l||r<lb) return;
        // General Case
        internalUpdate(node[idx].lc,l,r,val);
        internalUpdate(node[idx].rc,l,r,val);
        node[idx].val = node[node[idx].lc].val + node[node[idx].rc].val;
        return;
    }
public:
    SegmentTree(int n,vector<int> &initialValue)
    {
        this->n = n;
        base = initialValue;
        ROOT = createNode(1,n);
    }

    SegmentTree() {}

    void rangeUpdate(int l,int r,int val)
    {
        if(l>r) return;
        internalUpdate(ROOT,l,r,val);
    }

    int pointQuery(int idx)
    {
        return hunt(ROOT,idx);
    }

    void showMeAll()
    {
        fprintf(stderr,"Current Tree Status: ");
        for(int i=1;i<=n;i++) fprintf(stderr,"%d ",pointQuery(i));
        fprintf(stderr,"\n");
    }

};

class Bucket
{
public:
    int BUCKET_START;
    int BUCKET_END;
private:
    int lazyAdd = 0;
    vector<int> element;
    bool ready = false;

    void recreation(vector<int> &cnt,int l,int r,int val)
    {
        // fprintf(stderr,"Re-Counting Bucket [%d,%d]\n",BUCKET_START,BUCKET_END);
        element.clear();
        for(int i=BUCKET_START;i<=BUCKET_END;i++)
        {
            if(l<=i&&i<=r) cnt[i] += val; else cnt[i]-=val;

            int cur = 1;
            cur = cnt[i];

            element.push_back(cur);
        }
        // lazyAdd = 0;
        ready = false;
        // fprintf(stderr,"Bucket Status: "); for(int v:element) fprintf(stderr,"%d ",v); fprintf(stderr,"(+ %d)\n",lazyAdd);
    }

public:
    Bucket() {}

    Bucket(int firstNode,int lastNode,vector<int> &cnt)
    {
        BUCKET_START = firstNode;
        BUCKET_END = lastNode;
        recreation(cnt,BUCKET_START,BUCKET_END,0);
    }

    // Return the number of node in this bucket that has distance STRICTLY more than arg.
    int getHigher(int arg)
    {
        int n = element.size();
        if(n<=0) return 0;
        // fprintf(stderr,"Request for more than %d\n",arg);
        if(!ready)
        {
            sort(element.begin(),element.end());
            ready = true;
        }

        if(element[n-1]+lazyAdd <= arg) return 0;

        // Binary Search
        int l = 0;
        int r = n-1;
        while(l<r)
        {
            if(l+1==r)
            {
                if(element[l] + lazyAdd > arg) return n-l;
                else return n-r;
            }
            int m = l + (r-l)/2;
            // fprintf(stderr,"Ask? Position %d = %d\n",m,element[m]+lazyAdd);
            if(element[m] + lazyAdd > arg) r = m;
            else l = m+1;
        }
        return n-l;
    }

    // Try to update the bucket, given that the segment tree cnt has been correctly updated.
    void updateCommand(int l,int r,int val,vector<int> &cnt)
    {
        // fprintf(stderr,"UpdateCommand[%d,%d] for[%d,%d]->(%d) points\n",BUCKET_START,BUCKET_END,l,r,val);
        if(l>r) return;
        if(r<BUCKET_START||BUCKET_END<l)
        {
            // fprintf(stderr,"Completely OUT\n");
            lazyAdd -= val;
            return;
        }
        if(l<=BUCKET_START&&BUCKET_END<=r)
        {
            // fprintf(stderr,"Completely IN\n");
            lazyAdd += val;
            return;
        }
        // Partial Update
        recreation(cnt,l,r,val);
    }

    void showStatus()
    {
        fprintf(stderr,"Bucket Status: ");
        for(int v:element) fprintf(stderr,"%d ",v+lazyAdd);
        fprintf(stderr,"\n");
    }
};


class Tree
{
private:
    int n;
public:
    vector<vector<int>> edge;
private:
    vector<P> edgeList;

    void addEdge(int u,int v)
    {
        edge[u].push_back(v);
        edge[v].push_back(u);
    }

    void dfs(int node,int prv,vector<int> &lvl,int curlvl)
    {
        lvl[curlvl]++;
        for(int v:edge[node])
        {
            if(v==prv) continue;
            dfs(v,node,lvl,curlvl+1);
        }
    }

    void travel(int node,int prv,vector<int> &tod,int &visitedCount)
    {
        visitedCount++;
        tod[node] = visitedCount;
        for(int v:edge[node])
        {
            if(v==prv) continue;
            travel(v,node,tod,visitedCount);
        }
    }

    void travel2(int node,int prv,vector<int> &tod,int &visitedCount)
    {
        visitedCount++;
        int curNode = visitedCount;
        for(int v:edge[node])
        {
            if(v==prv) continue;
            travel2(v,node,tod,visitedCount);
        }
        tod[curNode] = visitedCount;
    }

    void distanceHunt(int node,int prv,vector<int> &dst)
    {
        for(int v:edge[node])
        {
            if(v==prv) continue;
            dst[v] = dst[node]+1;
            distanceHunt(v,node,dst);
        }
    }

public:
    Tree(int n,vector<P> &edgeList)
    {
        this->n = n;
        this->edgeList = edgeList;
        edge = vector<vector<int>>(n+7);
        for(P p:edgeList) addEdge(p.x,p.y);
    }

    Tree() {}

    int getNodeCount()
    {
        return n;
    }

    vector<int> getDistanceDistribution(int root)
    {
        vector<int> lvl(n,0);
        dfs(root,-1,lvl,0);
        return lvl;
    }

    vector<int> getDistanceFromRoot(int root)
    {
        vector<int> dst(n+7,0);
        dst[root] = 0;
        distanceHunt(root,-1,dst);
        return dst;
    }

    vector<int> getTransversalOrder(int root)
    {
        vector<int> tod(n+7,0);
        int visitedCount = 0;
        travel(root,-1,tod,visitedCount);
        return tod;
    }

    vector<int> getLastNodeInSubtree(int root)
    {
        vector<int> tod(n+7,0);
        int visitedCount = 0;
        travel2(root,-1,tod,visitedCount);
        return tod;
    }

    Tree reconstruct(int root,vector<int> &tf)
    {
        tf = getTransversalOrder(root);
        vector<P> newEdgeList;
        for(P e:edgeList) newEdgeList.push_back(mp(tf[e.x],tf[e.y]));
        return Tree(n,newEdgeList);
    }



};

class BruteForceSolver  // A straightforward O(N^2) Solution
{
private:
    int n;
    Tree tree;
    vector<int> k;

    int simpleCase(int root,int arg)
    {
        vector<int> dst = tree.getDistanceDistribution(root);
        int curSum = 0;
        for(int i=n-1;i>=0;i--)
        {
            if(curSum>=arg) return i;
            curSum += dst[i];
        }
        return -1;
    }
public:
    BruteForceSolver(Tree tree,vector<int> k)
    {
        n = tree.getNodeCount();
        this->tree = tree;
        this->k = k;
    }

    vector<int> getAnswer()
    {
        vector<int> ans(n+7);
        for(int i=1;i<=n;i++) ans[i] = simpleCase(i,k[i]);
        return ans;
    }
};



class RootLogSolver // Hope for O(N*log(sqrt(N))*sqrt(N)) Solution
{
private:
    const int BUCKET_SIZE = 1000;
    int n;
    int BUCKET_COUNT;
    Tree tree;
    vector<int> k;
    vector<int> ans;
    vector<Bucket> bucket;
    vector<int> tf;
    vector<int> endpoints;
    SegmentTree counter;

    vector<int> dst;

    vector<int> modifyDistance(vector<int> &oldDistance)
    {
        vector<int> newDistance(n+1,0);
        for(int i=1;i<=n;i++)   newDistance[tf[i]] = oldDistance[i];
        return newDistance;
    }

public:
    RootLogSolver(Tree tree,vector<int> k)
    {
        n = tree.getNodeCount();
        this->tree = tree;
        this->k = k;
        BUCKET_COUNT = (n-1)/BUCKET_SIZE +1;
        bucket = vector<Bucket>(BUCKET_COUNT);
    }
private:
    void generalUpdate(int l,int r,int val)
    {
        if(l>r) return;
        for(int i=0;i<BUCKET_COUNT;i++)
        {
            bucket[i].updateCommand(l,r,val,dst);
        }
    }

    // Get aggregate supply (modified)
    bool getAggregateSupply(int targetDistance,int passingScore)
    {
        int ret = 0;
        int remaining = n;
        for(int i=0;i<BUCKET_COUNT;i++)
        {
            int thisOne = bucket[i].getHigher(targetDistance);
            ret += thisOne;
            if(ret>=passingScore) return true;
            remaining -= BUCKET_SIZE;
            if(ret+remaining < passingScore) return false;
        }
        // fprintf(stderr,"Supply(more than %d) = %d\n",targetDistance,ret);
        return ret>=passingScore;
    }

    int queryCommand(int arg)
    {
        // Binary Search for the answer!
        int l = 0;
        int r = n-1;
        while(l<r)
        {
            if(l+1==r)
            {
                if(getAggregateSupply(r,arg)) return r;
                else return l;
            }
            // General Case
            int m = l + (r-l)/2;
            if(getAggregateSupply(m,arg)) l = m;
            else r = m-1;
        }
        return l;
    }


    void checkout(int node,int prv)
    {
        // Answer Query for themselves first
        //fprintf(stderr,"Solve for node %d\n",node);
        ans[node] = queryCommand(k[node]);
        // Go to Children
        for(int v:tree.edge[node])
        {
            if(v==prv) continue;
            int startTree = tf[v];
            int endTree = endpoints[startTree];
            // Update before moving on
            generalUpdate(startTree,endTree,-1);
            // Calculations
            checkout(v,node);
            // Revert Updates
            generalUpdate(startTree,endTree,1);
        }
    }

public:

    void compositionTest()
    {
        fprintf(stderr,"Tree Status\n");
        for(int i=1;i<=n;i++)
        {
            fprintf(stderr,"Node %d: In: %d, Out: %d\n",i,tf[i],endpoints[tf[i]]);
        }
    }

    void distanceTest(vector<int> &dst)
    {
        fprintf(stderr,"Modified Distance: ");
        for(int i=1;i<=n;i++) fprintf(stderr,"%d ",dst[i]);
        fprintf(stderr,"\n");
    }

    vector<int> getAnswer()
    {
        // Prepare Space for storing answer
        ans = vector<int>(n+7);
        // Calculate Distance & Transform the Tree
        tf = tree.getTransversalOrder(1);   // Get a Transformation Function
        endpoints = tree.getLastNodeInSubtree(1);   // Get Last Node in Subtree
        dst = tree.getDistanceFromRoot(1);  // We select an arbitrary root
        dst = modifyDistance(dst);
        // Initialize Segment Tree
        counter = SegmentTree(n,dst);
        // Initialize Buckets
        for(int i=0;i<BUCKET_COUNT;i++)
        {
            bucket[i] = Bucket(1 + BUCKET_SIZE*i,min(n,BUCKET_SIZE*(i+1)),dst);
        }
        // Do Something for the answer
        checkout(1,-1);
        // Return Answer
        return ans;
    }
};

int main()
{
    int n; scanf("%d",&n);
    vector<int> k(n+7);
    for(int i=1;i<=n;i++) scanf("%d",&k[i]);
    vector<P> edgeList(n-1);
    for(int i=0;i<n-1;i++) scanf("%d%d",&edgeList[i].x,&edgeList[i].y);

    Tree tree(n,edgeList);

    vector<int> ans;

    // Get Answer!
    if(false)
    {
        BruteForceSolver shao(tree,k);
        ans = shao.getAnswer();
    }
    else
    {
        RootLogSolver shao(tree,k);
        ans = shao.getAnswer();
    }

    for(int i=1;i<=n;i++) printf("%d ",ans[i]);

    return 0;
}
