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

typedef unsigned int uint;
int n,m;
int xsiz, ysiz, xs, ys;

uint x[200000], yb[200000], y[10000];
uint sum[200000];
char t[200000];
int bitlen[1<<16+1];
uint bm1 = 0, bm2 = 0;

int __builtin_popcount (unsigned int x);
uint test(int xp, int yp, int t);

inline uint oper(uint a, uint b) {
	return bitlen[(a|b)&bm1] + bitlen[((a|b)&bm2)>>16];
	//return __builtin_popcount(a|b);
}

inline uint getmask(int len) {
	uint m = 0;
	REP(i,len) m = 2*m+1;
	return m<<(32-len);
}

void debug() {
	REP(i,xsiz) printf("%d ", sum[i]); puts("");
}
char bbuf[33];
inline char* bits(uint v) {
	int z = 32;
	bbuf[z] = 0;
	while (z--) {
		bbuf[z] = v%2 ? '1' : '0';
		v /= 2;
	}
	return bbuf;
}

void prepare32() {
	REP(i,xs) {
		uint col = 0;
		REP(j,ys) {
			if (x[(i+j)%xs] | yb[j]) col++;
		}
		sum[i] = col;
	}
}

void prepare23() {
	if (xsiz<32) {
		prepare32();
		return;
	}
	uint s = 0;
	REP(i,31) s = 2*s + x[i];
	REP(i,xs) {
		s = 2*s + x[(i+31)%xs];
		REP(j,ysiz-1) {
			//printf("dodaje do %d\n", (i+32*xs-32*j)%xs);
			sum[(i+32*xs-32*j)%xs] += oper(s,y[j]);
		}
		//printf("dodaje do %d\n", (i+32*xs-32*ysiz+32)%xs);
		sum[(i+32*xs-32*ysiz+32)%xs] += oper((ys%32)?getmask(ys%32)&s:s,y[ysiz-1]);
	}
}

void prepare() {
	if (xsiz<32) {
		prepare32();
		return;
	}
	uint s = 0;
	REP(i,31) s = 2*s + x[i];
	uint *xr = x + 31, *xend = x+xs;
	uint *yr, *yend = y + ysiz - 1;
	uint *sumr, mask = (ys%32) ? getmask(ys%32) : getmask(32);
	REP(i,xs) {
		sumr = sum+i;
		s = 2*s + *xr++;
		if (xr == xend) xr = x;
		
		for (yr = y; yr != yend; yr++) {
			*sumr += oper(s,*yr);
			sumr -= 32;
			if (sumr < sum) sumr+=xs;
		}
		*sumr += oper(mask & s,*yr);
	}
}

int readB(char* b, uint* a, int len);
int readA(char* b, uint* a, int len);

void init() {
	bm2 = getmask(16);
	bm1 = bm2>>16;
	REP(i,(1<<16)+1) bitlen[i] = __builtin_popcount(i);
}

main() {
	init();
	scanf("%d%d", &n, &m);
	xs = m; ys = n;
	scanf("%s", t);
	if (ys<xs) ysiz = readB(t,y,n);
	else xsiz = readA(t,x,n);
	scanf("%s", t);
	if (ys<xs) xsiz = readA(t,x,m);
	else ysiz = readB(t,y,m);
	if (ys>xs) swap(xs,ys);
	xs = 2*xs - 2; ys = 2*ys -2;
	prepare();
//	prepare23();
//	debug();
	int d; scanf("%d", &d);
	int xp,yp,xv,yv,t;
	while (d--) {
		scanf("%d%d%d%d%d", &xp, &yp, &xv, &yv, &t);
		if (n>m) { // byla rotacja stolu
			swap(xp,yp);
			if (xv != yv) swap(xv,yv);
		}
		if (xv == -1) xp = 2*max(n,m)-xp;
		if (yv == -1) yp = 2*min(n,m)-yp;
		printf("%u\n", test(xp-1,yp-1,t));
	}
}

uint test(int xp, int yp, int t) {
	//printf("Test %d %d %d\n", xp, yp, t);
	// lecimy do sufitu
	int sufitT = min(ys-yp-1, t);
	uint res = 0, sufit = 0;
	t -= sufitT;
	for (int i=0;i<=sufitT;i++) sufit += (x[(xp+i)%xs] | yb[yp+i]);
	//printf("Sufit %u sufitt %d\n", sufit, sufitT);
	int dolstart = (xp+sufitT+1)%xs;
	int dol = dolstart, doltim=0;
	uint dolres = 0;
	// skoki
	while (t >= ys) {
		//printf("Duzy skok z %d za %d do %d\n", dol,sum[dol],(dol+ys)%xs);
		t -= ys;
		doltim += ys;
		dolres += sum[dol];
		dol = (dol+ys)%xs;
		if (dol == dolstart) break;
	}
	//printf("Dolres %u %d %d\n", dolres, doltim, t);
	// duze skoki
	if (doltim > 0 && t >= doltim) {
		int k = t / doltim;
		t -= k*doltim;
		res += k*dolres;
		//printf("B duze skoki x %d za %d\n",k,k*dolres);
	}
	// koncowe skoki
	int kon=0;	
	while (t >= ys) {
		kon++;
		//printf("Duzy skok z %d za %d do %d zostalo %d\n", dol,sum[dol],(dol+ys)%xs,t);
		t -= ys;
		res += sum[dol];
		dol = (dol+ys)%xs;
	}
	//printf("KON!! %d\n", kon);
	// lecimy od podlogi do konca
	REP(i,t) {
		//printf("Podloga %d %d\n", (dol+i)%xs, yb[i]);
		res += (x[(dol+i)%xs] | yb[i]);
	}
	return sufit + dolres + res;
}

int readB(char* b, uint* a, int len) {
	int aid = 0;
	uint g = 0;
	REP(i,2*len-2) {
		g = g*2;
		if (i >= len) {
			yb[i] = b[2*len-i-2]=='0' ? 0 : 1;
			g += b[2*len-i-2]=='0' ? 0 : 1;
		}
		else {
			yb[i] = b[i]=='0' ? 0 : 1;
			g += b[i]=='0' ? 0 : 1;
		}
		if (i % 32 == 31) {
			a[aid++] = g;
			g = 0;
		}
	}
	if ((2*len-2) % 32 != 0) {
		a[aid++] = g << (32-((2*len-2)%32));
	}
	//REP(i,2*len-2) printf("%d ", yb[i]); puts("");
	//REP(i,aid) printf("%s ", bits(y[i])); puts("");
	return aid;
}

int readA(char* b, uint* a, int len) {
	REP(i,2*len-2) {
		if (i >= len) a[i] = (b[2*len-i-2]=='0') ? 0 : 1;
		else a[i] = (b[i]=='0') ? 0 : 1;
	}
	//REP(i,2*len-2) printf("%d ", x[i]); puts("");
	return 2*len-2;
}

