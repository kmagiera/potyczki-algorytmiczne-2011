#include <cstdio>
#include <ctime>
#include <cstdlib>

const double eps = 1e-6;

main() {
	double x,y,ox,oy;
	int t,r;
	scanf("%d", &t);
	srand(time(NULL));
	while (t--) {
		x = 0.0;
		y = 0.0;
		while (true) {
			r = rand()%3;
			ox = x;
			oy = y;
			if (r == 0) {
				x = (x-y)/4.-0.5;
				y = (x+y)/4.+1.;
			}
			else if (r == 1) {
				x = (y-x)/4.+0.5;
				y = -(x+y)/4.+1.;
			}
			else {
				x = (x+y)/2.+ 1.;
				y = (y-x)/2.;
			}
			if ((ox-x)*(ox-x) + (oy-y)*(oy-y) < eps*eps) break;
		}
		printf("%lf %lf\n", x, y);
	}
}

