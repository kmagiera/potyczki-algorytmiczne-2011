#include <cstdio>
#include <vector>
using namespace std;


typedef pair<int,int> pt;

const int SIZ = 4000;
const int SIZ2 = SIZ/2;
bool map[SIZ][SIZ];

main() {
	int n;
	scanf("%d", &n);
	int k = (1<<n)-1;
	//for (int i=0;i<V1.size();i++) printf("%c", V1[i]);
	//puts("");
	
	pt a = pt(1,1), v = pt(1,1), b;
	map[SIZ2][SIZ2] = 1;
	//printf("0 0\n1 1\n");
	for (int i=1;i<=k;i++) {
		if ((((i&-i)<<1)&i) == 0) {
			if (v.first == v.second) v.first *= -1;
			else v.second *= -1;
		}
		else {
			if (v.first == v.second) v.second *= -1;
			else v.first *= -1;
		}
		b = pt(a.first + v.first, a.second + v.second);
		if (v.first == 1 && v.second == 1) map[a.first+SIZ2][a.second+SIZ2] = 1;
		else if (v.first == -1 && v.second == 1) map[b.first+SIZ2][a.second+SIZ2] = 1;
		else if (v.first == 1 && v.second == -1) map[a.first+SIZ2][b.second+SIZ2] = 1;
		else if (v.first == -1 && v.second == -1) map[b.first+SIZ2][b.second+SIZ2] = 1;
		a = b;
		//printf("%d %d\n", a.first, a.second);
	}
	for (int i=0;i<SIZ;i++) {
		int cnt = 0;
		for (int j=0;j<SIZ-1;j++) {
			if (map[j][i] != map[j+1][i]) cnt++; 
		}
		if (cnt > 0) printf("%d %d\n", i-SIZ2, cnt/2);
	}
}

