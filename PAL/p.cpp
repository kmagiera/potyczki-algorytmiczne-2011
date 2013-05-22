#include <cstdio>
#include <vector>
#include <queue>

#define FOR(i,s,e) for (int i=(s);i<(e);i++)
#define REP(i,n) FOR(i,0,n)
#define FOREACH(i,c) for(typeof((c).begin()) i = (c).begin(); i != (c).end(); i++)
#define PB push_back

using namespace std;

typedef pair<int,int> para;

vector<int> G[500500];
int vis[500500];

para dfs(int v, int color) {
	para p;
	queue<para> q;
	vis[v] = color;
	q.push(para(v,0));
	while (!q.empty()) {
		p = q.front(); q.pop();
		FOREACH(it,G[p.first]) {
			if (vis[*it] != color) {
				vis[*it] = color;
				q.push(para(*it,p.second+1));
			}
		}
	}
	return p;
}

main() {
	int n,m,a,b;
	scanf("%d%d", &n, &m);
	REP(i,n-1) {
		scanf("%d%d", &a, &b);
		G[a-1].PB(b-1);
		G[b-1].PB(a-1);
	}
	para pv = dfs(0, 1);
	pv = dfs(pv.first, 2);
	printf("%d\n", pv.second > m ? m+1 : min(n, 1 + pv.second + (m-pv.second)/2));
}

