#include <cstdio>
#include <cstring>

char szach[2000][2000];
int r[2000],c[2000];

void test() {
	int n;
	char *q;
	scanf("%d", &n);
	for (int i=0;i<n;i++) {
		scanf("%s", szach[i]);
		q = strchr(szach[i], 'W');
		if (q != NULL) {
			c[i] = 1;
			r[q - szach[i]] = 1;
		}
	}
	int k=0;
	for (int i=0;i<n;i++) {
		if (c[i] == 0) {
			while (r[k]) k++;
			szach[i][k++] = 'W';
		}
		printf("%s\n", szach[i]);
	}
}

main() {
	test();
}

