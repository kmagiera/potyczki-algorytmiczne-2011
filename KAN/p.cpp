#include <cstdio>
#include <vector>
#include <algorithm>

#define X first
#define Y second
#define MAXPT 100
#define FOR(i,s,e) for (int i=(s);i<(e);i++)
#define REP(i,n) FOR(i,0,n)
#define FOREACH(i,c) for(typeof((c).begin()) i = (c).begin(); i != (c).end(); i++)
#define PB push_back

using namespace std;

typedef pair<int,int> kang;
kang kangs[50000];

main() {
	int n,m,a,b;
	scanf("%d%d", &n, &m);
	kang* kend = kangs+n;
	for(kang* k=kangs; k != kend; k++)
		scanf("%d%d", &k->first, &k->second);
	while (m--) {
		scanf("%d%d", &a,&b);
		int cnt = 0;
		int mcnt = 0;
		for(kang* k=kangs; k != kend; k++) {
			if (b < k->first || a > k->second) {
				if (mcnt < cnt) mcnt = cnt;
				cnt = 0;
			}
			else cnt++;
		}
		if (mcnt < cnt) mcnt = cnt;
		printf("%d\n", mcnt);
	}
}

