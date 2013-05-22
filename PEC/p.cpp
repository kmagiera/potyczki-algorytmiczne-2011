#include <cstdio>

typedef double real;

real test(int s, int w, int k) {
	real dist =  0.0;
	real rk = k, rs = s;
	real water = w;
	
	if (w%k) {
		dist = ((real)(w%k)) / ((real)(w/k*2+1));
		water -= w%k;
		if (dist >= s) {
			return w - (w/k*2+1)*s;
		}
	}
	int x = (w/k)*2 - 1;
	real step = rk / ((real)x);
	while (x > 0 && dist + step < rs) {
		water -= k;
		dist += step;
		x -= 2;
		step = rk / ((real)x);
	}
	return water - (rs-dist)*x;
}

main() {
	int s,w,k,x;
	scanf("%d%d%d", &s, &w, &k);
	printf("%.5lf\n", test(s,w,k));
}

