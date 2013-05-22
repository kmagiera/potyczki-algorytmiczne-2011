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

typedef long long lld;
typedef unsigned long long ulld;
typedef pair<lld, lld> pt;
const pt zero(0,0), one(1,1);
vector<pt> pts;
vector<pair<pt,pt> > bounds;
vector<ulld> pow2;

pt rotC(const pt& c, const pt& p) {
	return pt(p.Y - c.Y + c.X, -p.X + c.X + c.Y);
}
pt rotCC(const pt& c, const pt& p) {
	return pt(-p.Y + c.Y + c.X, p.X - c.X + c.Y);
}
lld min(lld a, lld b, lld c, lld d) {
	return min(a, min(b, min(c,d)));
}
lld max(lld a, lld b, lld c, lld d) {
	return max(a, max(b, max(c,d)));
}

void init() {
	pts.PB(one);
	bounds.PB(make_pair(zero, one));
	pow2.PB(1);
	FOR(i,1,MAXPT) {
		pts.PB(rotC(pts.back(), zero));
		pow2.PB(pow2.back()*2);
		pt a = rotC(pts[i-1], bounds[i-1].X), b = rotC(pts[i-1], bounds[i-1].Y);
		bounds.PB(make_pair(
			pt(min(a.X, b.X, bounds[i-1].X.X, bounds[i-1].Y.X),
				min(a.Y, b.Y, bounds[i-1].X.Y, bounds[i-1].Y.Y)),
			pt(max(a.X, b.X, bounds[i-1].X.X, bounds[i-1].Y.X),
				max(a.Y, b.Y, bounds[i-1].X.Y, bounds[i-1].Y.Y))));
	}
	//FOR(i,0,bounds.size()) 
	//	printf("%lld %lld %lld %lld\n", bounds[i].X.X, bounds[i].X.Y, bounds[i].Y.X, bounds[i].Y.Y);
}

struct mpt {
	pt p;
	vector<int> hist;
};

main() {
	init();
	int n,m;
	mpt g;
	vector<mpt> res;
	vector<ulld> rws;
	
	scanf("%d%d", &n, &m);
	while (m--) {
		scanf("%lld %lld", &g.p.X, &g.p.Y);
		res.clear();
		rws.clear();
		res.PB(g);
		for (int rot = min(n,MAXPT)-1; !res.empty() && rot >= 0; rot--) {
			//printf("Rot %d (%lld %lld) size %d bnd (%lld,%lld %lld,%lld)\n",
			//	rot, pts[rot].X, pts[rot].Y, res.size(), bounds[rot].X.X, bounds[rot].X.Y,
			//	bounds[rot].Y.X, bounds[rot].Y.Y);
			int s = res.size();
			REP(i,s) {
				if (res[i].p == pts[rot]) continue;
				mpt newp = res[i];
				newp.hist.PB(rot);
				newp.p = rotCC(pts[rot], newp.p);
				res.PB(newp);
			}
			REP(i,res.size()) {
				pt f = res[i].p;
				if (f.X < bounds[rot].X.X || f.X > bounds[rot].Y.X 
						|| f.Y < bounds[rot].X.Y || f.Y > bounds[rot].Y.Y) {
					swap(res.back(), res[i]); res.pop_back(); i--;
				}
			}
		}
		REP(i,res.size()) if (res[i].p.X != res[i].p.Y) {
			swap(res.back(), res[i]); res.pop_back(); i--;
		}
		/*REP(i,res.size()) {
			printf("%lld %lld -> ", res[i].p.X, res[i].p.Y);
			REP(j,res[i].hist.size()) printf("%d ", res[i].hist[j]);
			puts("");
		}*/
		REP(i,res.size()) {
			ulld rw = (res[i].p == zero) ? 0 : 1;
			for (int j=res[i].hist.size()-1; j >= 0; j--) {
				rw = pow2[res[i].hist[j]]*2 - rw;
			}
			rws.PB(rw);
		}
		sort(rws.begin(), rws.end());
		printf("%d", rws.size());
		REP(i, rws.size()) printf(" %llu", rws[i]); puts("");
	}
	
}

