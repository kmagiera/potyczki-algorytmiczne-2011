#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;


typedef pair<int,int> pt;

const int SIZ = 4000;
const int SIZ2 = SIZ/2;
int map[SIZ][SIZ];

main() {
	int n;
	scanf("%d", &n);
	int k = (1<<n)-1;
	//for (int i=0;i<V1.size();i++) printf("%c", V1[i]);
	//puts("");
	
	pt a = pt(1,1), v = pt(1,1), b;
	map[SIZ2][SIZ2] = 1;
	//printf("0 0\n1 1\n");
	int mid=2,dwa=2;
	for (int i=1;i<=k;i++) {
		if (i==dwa) {
			mid++;
			dwa *= 2;
		}
		if ((((i&-i)<<1)&i) == 0) {
			if (v.first == v.second) v.first *= -1;
			else v.second *= -1;
		}
		else {
			if (v.first == v.second) v.second *= -1;
			else v.first *= -1;
		}
		b = pt(a.first + v.first, a.second + v.second);
		if (v.first == 1 && v.second == 1) map[a.first+SIZ2][a.second+SIZ2] = mid;
		else if (v.first == -1 && v.second == 1) map[b.first+SIZ2][a.second+SIZ2] = mid;
		else if (v.first == 1 && v.second == -1) map[a.first+SIZ2][b.second+SIZ2] = mid;
		else if (v.first == -1 && v.second == -1) map[b.first+SIZ2][b.second+SIZ2] = mid;
		a = b;
		//printf("%d %d\n", a.first, a.second);
	}
	int minx = SIZ, maxx = -1, miny = SIZ, maxy = -1;
	for (int x=0;x<SIZ;x++) {
		for (int y=0;y<SIZ;y++)
			if (map[x][y]) {
				minx = min(minx,x);
				maxx = max(maxx,x);
				miny = min(miny,y);
				maxy = max(maxy,y);
			}
	}
	for (int y=miny; y<=maxy; y++) {
		for (int x=minx; x<=maxx;x++)
			printf("%d ", map[x][y]);
		printf("\n");
	}
}

