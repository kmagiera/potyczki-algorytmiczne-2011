#include <cstdio>
#include <algorithm>
#include <vector>

#define FOR(i,s,e) for (int i=(s);i<(e);i++)

using namespace std;

bool test() {
	int n,a,k,s,d = 0;
	vector<pair<int,int> > ev;
	scanf("%d%d%d", &s, &k, &n);
	int inw = 0, laste = 0;
	FOR(i,0,n) {
		scanf("%d", &a);
		if (i%2 == 0 && a >= k) {
			ev.push_back(make_pair(0, -1));
			ev.push_back(make_pair(k, 1));
		}
		else if (i%2 == 0) {
			ev.push_back(make_pair(d, -1));
			ev.push_back(make_pair((d + a) % k, 1));
			if (ev[ev.size()-2].first > ev[ev.size()-1].first) inw++;
		}
		d = (d + a) % k;
	}
	ev.push_back(make_pair(k, 0));
	//FOR (i,0,ev.size()) printf("Ev %d %d\n", ev[i].first, ev[i].second);
	sort(ev.begin(), ev.end());
	//printf("laste %d inw %d\n", laste, inw);
	FOR(i,0,ev.size()) {
		//printf("Ev %d %d inw %d\n", ev[i].first, ev[i].second, inw);
		if (inw == 0 && ev[i].first - laste >= s) {
			//printf("At %d laste %d\n", ev[i].first, laste);
			return true;
		}
		inw -= ev[i].second;
		laste = ev[i].first;
	}
	return false;
}

main() {
	int t; scanf("%d", &t);
	while (t--) puts(test() ? "TAK" : "NIE");
}

