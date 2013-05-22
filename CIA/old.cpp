#include <cstdio>
#include <algorithm>

#define FOR(i,s,e) for (int i=(s);i<(e);i++)
#define REP(i,n) FOR(i,0,n)
#define FOREACH(i,c) for(typeof((c).begin()) i = (c).begin(); i != (c).end(); i++)
#define PB push_back

#define TMAX (1<<17)
#define MAXV 1000000000000000000LL
#define NO 2000000000
using namespace std;

typedef long long lld;

int n,p,q,a,id,qcp;
int T[100000];
pair<int,int> data[100000];
pair<int,pair<lld,int> > que[100000];
int res[100000][10];
lld tre[2*TMAX][10];

void insert(int x, lld val, int pos) {
	int v = TMAX+x;
	tre[v][pos] = min(MAXV+1, tre[v][pos] + val);
	while (v!=1) {
		v /= 2;
		tre[v][pos] = min(MAXV+1, tre[v][pos] + val);
	}
}

lld query(int a, int b,int pos) {
	int va = TMAX+a, vb = TMAX+b;
	lld res = min(MAXV+1, va!=vb ? tre[va][pos] + tre[vb][pos] : tre[va][pos]);
	while (va/2 != vb/2) {
		if (va%2==0) res = min(MAXV+1, res + tre[va+1][pos]);
		if (vb%2==1) res = min(MAXV+1, res + tre[vb-1][pos]);
		va/=2;
		vb/=2;
	}
	return res;
}

int findPos(int start, lld sum, int pos) {
	//printf("FindPos(%d,%lld,%d)\n", start, sum, pos);
	int l = start, r = n;
	while (l != r) {
		int mid = (l + r)/2;
		lld qr = query(start, mid, pos);
		if (qr < sum) l = mid + 1;
		else r = mid;
	}
	//printf("Query(%d,%d) = %lld > %lld\n", start, l, query(start, l, pos), sum);
	return l;
}

main() {
	scanf("%d%d%d", &n, &p, &q);
	qcp = q;
	REP(i,n) scanf("%d", &T[i]);
	REP(i,n) data[i] = make_pair(T[i], i);
	sort(data,data+n);
	REP(i,q) {
		scanf("%lld", &que[i].second.first);
		que[i].first = NO-1;
		que[i].second.second = i;
		res[i][0] = -1;
	}
	REP(pos, p) {
		sort(que, que+q);
		while (q && que[q-1].first == NO) q--;
		REP(j,2*TMAX) REP(i,p) tre[j][i]=0;
		int qp = 0;
		REP(i,n) {
			insert(data[i].second,1,0);
			FOR(hp,1,p-pos) {
				lld qr = query(data[i].second+1,n+1,hp-1);
				insert(data[i].second,qr,hp);
				//printf("Insert(%d,%d) = %lld\n", data[i].second, hp, qr);
			}
			int next = (i == n-1) ? NO : data[i+1].first;
			for (; qp < q && que[qp].first <= next; qp++) {
				int beg = (pos == 0) ? 0 : res[que[qp].second.second][pos-1]+1;
				//printf("Q %d (%lld,%d)\n", que[qp].second.second, que[qp].second.first,que[qp].first);
				int px = findPos(beg, que[qp].second.first, p-pos-1);
				//printf("Px = %d ", px);
				if (px == n)
					que[qp].first = NO;
				else {
					res[que[qp].second.second][pos] = px;
					que[qp].first = T[px];
					//printf("Add %d ", T[px]);
					if (px > beg) {
						//printf("Sub %lld ", query(beg, px-1, p-pos-1));
						que[qp].second.first -= query(beg, px-1, p-pos-1);
					}
				}
				//printf("\n");
			}
		}
		//printf("-------\n");
	}
	REP(i,qcp) {
		printf("%d", res[i][0] >= 0 ? res[i][0]+1 : -1);
		if (res[i][0] >= 0) FOR(j,1,p) printf(" %d", res[i][j]+1);
		puts("");
	}
}

