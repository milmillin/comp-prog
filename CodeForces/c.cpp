#include <cstdio>
#include <cmath>

using namespace std;

int cnt[3000];
int tbl[3000];
int corr[3000];
int print[3000];

int main () {
	int n,m;
	scanf ("%d%d",&n,&m);
	for (int i=0; i<n; i++) {
		scanf ("%d",&tbl[i]);
		if (tbl[i]<=m) cnt[tbl[i]]++;
	}
	int each=n/m;
	int quota=n%m;

	for (int i=1; i<=m; i++) {
		corr[i]=each;
	}
	int chg=0;
	for (int i=0; i<n; i++) {
		//printf ("--%d\n",i);
		if (tbl[i]<=m) {
			if (corr[tbl[i]]>0) {
				corr[tbl[i]]--;
				print[i]=tbl[i];
				//printf ("A\n");
			} else if (quota>0) {
				quota--;
				print[i]=tbl[i];
				//printf ("B\n");
			} else {
			    print[i]=-1;
//			    int tmp;
//			    bool used=false;
//				for (int j=1; j<=m; j++) {
//                    if (corr[j]) tmp=j;
//					if (corr[j]&&cnt[j]==0) {
//						corr[j]--;
//						print[i]=j;
//						used=true;
//						break;
//					}
//				}
//
//				if (!used) {
//                    corr[tmp]--;
//                    print[i]=tmp;
//				}
//
//				chg++;
//				cnt[tbl[i]]--;
				//printf ("C\n");
			}
		} else {
		    print[i]=-1;
//			bool used=false;
//			for (int j=1; j<=m; j++) {
//				if (corr[j]) {
//					corr[j]--;
//					print[i]=j;
//					used=true;
//					break;
//				}
//			}
//			if (!used&&quota) {
//				print[i]=1;
//			}
//			//printf ("D\n");
//			chg++;
		}
	}

	for (int i=0;i<n;i++) {
        if (print[i]!=-1) continue;
        for (int j=1; j<=m; j++) {
            if (corr[j]>0) {
                corr[j]--;
                print[i]=j;
                chg++;
                break;
            } else if (quota>0) {
                print[i]=j;
                quota--;
                chg++;
                break;
            }
        }
        //if (print[i]==-1) print[i]=1;
	}
	printf ("%d %d\n",each,chg);
	for (int i=0; i<n; i++) {
		printf ("%d ",print[i]);
	}
	printf ("\n");
	return 0;
}
