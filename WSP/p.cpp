#include <cstdio>
#include <algorithm>
using namespace std;

const int MAXI = 2000000100;

void test() {
	int n, a, b, pairs = -1;
	scanf("%d", &n);
	int minl[2] = {MAXI, MAXI}, minr[2] = {MAXI,MAXI}, curr = 0;
	while (n--) {
		scanf("%d%d", &a, &b);
		if (a+b >= curr) {
			minl[n%2] = min(minl[n%2], curr);
			curr = a + b - curr;
			minr[n%2] = min(minr[n%2], curr);
			pairs++;
		}
		else {
			int diff = curr - a - b;
			if (minr[(n+1)%2] >= diff && minl[n%2] >= diff) {
				minr[(n+1)%2] -= minr[(n+1)%2] == MAXI ? 0 : diff;
				minl[(n+1)%2] += minl[(n+1)%2] == MAXI ? 0 : diff;
				minl[n%2] = min(minl[n%2]-diff, a+b);
				minr[n%2] = curr = 0;
				pairs++;
			}
			else {
				minl[0] = minl[1] = minr[0] = minr[1] = MAXI;
				minl[n%2] = 0;
				minr[n%2] = curr = a+b;
			}
		}
	}
	printf("%d\n", pairs);
}

main() {
	test();
}

