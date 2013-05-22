#include <cstdio>
#include <vector>
#include <algorithm>
#include <set>
#include <ext/hash_set>

#define X first
#define Y second

#define GENPT 20
#define GENMINX (-1365)
#define GENMINY (-1365)
#define GENWIDTH (341+1365)
#define GENHEIGHT (682+1365)

#define MAXPT 65
#define FOR(i,s,e) for (int i=(s);i<(e);i++)
#define REP(i,n) FOR(i,0,n)
#define FOREACH(i,c) for(typeof((c).begin()) i = (c).begin(); i != (c).end(); i++)
#define PB push_back

using namespace std;
using namespace __gnu_cxx;

typedef long long lld;
typedef unsigned long long ulld;
typedef pair<lld, lld> pt;
const pt zero(0,0), one(1,1);
vector<pt> pts;
vector<pair<pt,pt> > bounds;

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
	FOR(i,1,MAXPT) {
		pts.PB(rotC(pts.back(), zero));
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
struct pasek {
	pt a,b;
};

void gen();
void paseczekHardcore(pasek p);

hash_set<int> result(1000000);
void resultAdd(int p) {
	//printf(" Result add %d\n", p);
	hash_set<int>::iterator i = result.find(p);
	if (i == result.end()) result.insert(p);
	else result.erase(i);
}

int resultGet() {
	return result.size()/2;
}

void resultClear() {
	result.clear();
}

pasek pasekRot(const pasek& p, int lvl) {
	//printf("Rot %lld,%lld %lld,%lld w %d(%lld,%lld) => ", p.a.X, p.a.Y, p.b.X, p.b.Y,lvl,pts[lvl].X,pts[lvl].Y);
	pasek r = p;
	r.a = rotCC(pts[lvl], r.a);
	r.b = rotCC(pts[lvl], r.b);
	//printf("%lld,%lld %lld,%lld\n", p.a.X, p.a.Y, p.b.X, p.b.Y);
	return r;
}

void paseczek(const pasek& p, int lvl) {
	//printf("Paseczek (%lld,%lld) (%lld,%lld) lvl %d\n", p.a.X, p.a.Y, p.b.X, p.b.Y, lvl);
	//printf("  Bnd %lld %lld; %lld %lld\n", bounds[lvl].X.X, bounds[lvl].X.Y, bounds[lvl].Y.X, bounds[lvl].Y.Y);
	
	//printf("%lld,%lld %lld,%lld\n", ld.X, ld.Y, pg.X, pg.Y);
	if (abs(p.a.Y-p.b.Y)==1) { // pasek poziomy
		pt ld(min(p.a.X,p.b.X), min(p.a.Y,p.b.Y));
		pt pg(max(p.a.X,p.b.X), max(p.a.Y,p.b.Y));
		if (pg.Y > bounds[lvl].X.Y && pg.Y <= bounds[lvl].Y.Y
				&& ld.X < bounds[lvl].Y.X && pg.X > bounds[lvl].X.X) {
			//do nth
		}
		else return;
		if (lvl == 0) {
			resultAdd(abs(1-p.a.X));
			resultAdd(abs(0-p.a.X));
			return;
		}
		if (lvl == GENPT) {
			paseczekHardcore(p);
			return;
		}
	}
	else { // pasek pionowy
		//printf("Pion\n");
		pt ld(min(p.a.X,p.b.X), min(p.a.Y,p.b.Y));
		pt pg(max(p.a.X,p.b.X), max(p.a.Y,p.b.Y));
		if (ld.X >= bounds[lvl].X.X && ld.X < bounds[lvl].Y.X
				&& ld.Y < bounds[lvl].Y.Y && pg.Y > bounds[lvl].X.Y) {
			//do nth
		}
		else return;
		if (lvl == 0) {
			resultAdd(abs(1-p.a.Y));
			resultAdd(abs(0-p.a.Y));
			return;
		}
		if (lvl == GENPT) {
			paseczekHardcore(p);
			return;
		}
	}
	//printf("  IN! (%lld,%lld) (%lld,%lld)\n",p.a.X, p.a.Y, p.b.X, p.b.Y);
	paseczek(p, lvl-1);
	paseczek(pasekRot(p, lvl-1), lvl-1);
}

int main() {
	init();
	int n,m;
	pasek pp;
	scanf("%d%d", &n, &m);
	if (n >= GENMINX) gen();
	while (m--) {
		scanf("%lld %lld %lld", &pp.a.X, &pp.b.X, &pp.a.Y);
		pp.b.Y = pp.a.Y + 1;
		resultClear();
		paseczek(pp, min(n, MAXPT-1));
		//FOREACH(it,rr) printf("%d ", *it); puts("");
		printf("%d\n", resultGet());
	}
}

vector<int> cols[GENWIDTH], rows[GENHEIGHT];

void gen() {
	int minx = GENMINX, miny = GENMINY;
	int LIMIT = (1<<GENPT);
	bool map[GENWIDTH][GENHEIGHT];
	
	pt a = pt(1,1), v = pt(1,1), b;
	//printf("0 0\n1 1\n");
	REP(x,GENWIDTH) REP(y,GENHEIGHT) map[x][y] = 0;
	map[-GENMINX][-GENMINY] = 1;
	for (int i=1;i<LIMIT;i++) {
		if ((((i&-i)<<1)&i) == 0) {
			if (v.first == v.second) v.first *= -1;
			else v.second *= -1;
		}
		else {
			if (v.first == v.second) v.second *= -1;
			else v.first *= -1;
		}
		b = pt(a.first + v.first, a.second + v.second);
		if (v.first == 1 && v.second == 1) map[a.first-GENMINX][a.second-GENMINY] = 1;
		else if (v.first == -1 && v.second == 1) map[b.first-GENMINX][a.second-GENMINY] = 1;
		else if (v.first == 1 && v.second == -1) map[a.first-GENMINX][b.second-GENMINY] = 1;
		else if (v.first == -1 && v.second == -1) map[b.first-GENMINX][b.second-GENMINY] = 1;
		a = b;
		//printf("%d %d\n", a.first, a.second);
	}
	REP(x,GENWIDTH) REP(y,GENHEIGHT) {
		if (map[x][y]) {
			if (x==0 || !map[x-1][y]) rows[y].PB(x+GENMINX);
			if (x==GENWIDTH-1 || !map[x+1][y]) rows[y].PB(x+1+GENMINX);
			if (y==0 || !map[x][y-1]) cols[x].PB(y+GENMINY);
			if (y==GENHEIGHT-1 || !map[x][y+1]) cols[x].PB(y+1+GENMINY);
		}
	}
	//printf("%lld %lld pt %lld %lld\n", bounds[20].X.X, bounds[20].X.Y, pts[20].X, pts[20].X);
}

void paseczekHardcore(pasek p) {
//	printf("Hard %lld %lld; %lld %lld\n", p.a.X, p.a.Y, p.b.X, p.b.Y);
	vector<int>::iterator s,e,beg,end;
	if (abs(p.a.Y-p.b.Y) == 1) { // poziom
		int yy = min(p.a.Y,p.b.Y), minx = min(p.a.X,p.b.X), maxx = max(p.a.X, p.b.X);
		beg = rows[yy-GENMINY].begin();
		end = rows[yy-GENMINY].end();
		s = lower_bound(beg, end, minx);
		e = upper_bound(beg, end, maxx);
		int ladd = 0;
		if (s != end && (s-beg)%2==1) {
			resultAdd(p.a.X<p.b.X ? 0 : maxx-minx); ladd++;
		}
		for (; s!=e; s++) {
			resultAdd(abs(p.a.X-*s)); ladd++;
		}
		if (ladd%2==1) resultAdd(p.a.X<p.b.X ? maxx-minx : 0);
	}
	else { // pion
		int xx = min(p.a.X,p.b.X), miny = min(p.a.Y,p.b.Y), maxy = max(p.a.Y, p.b.Y);
		beg = cols[xx-GENMINX].begin();
		end = cols[xx-GENMINX].end();
		s = lower_bound(beg, end, miny);
		e = upper_bound(beg, end, maxy);
		int ladd = 0;
		if (s != end && (s-beg)%2==1) {
			resultAdd(p.a.Y<p.b.Y ? 0 : maxy-miny); ladd++;
		}
		for (; s!=e; s++) {
			resultAdd(abs(p.a.Y-*s)); ladd++;
		}
		if (ladd%2==1) resultAdd(p.a.Y<p.b.Y ? maxy-miny : 0);
	}
}

