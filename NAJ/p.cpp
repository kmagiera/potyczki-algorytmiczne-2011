/**
 * Wykorzystano fragment kodu KMR z ksiazki AGH codebook 2010
 */
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

int tcount[1000000];
template<class T>
void count_sort(T* t, int n, int(*f)(T)) {
	T*tmp = new T[n];
	int high = 0;
	for (int i = 0; i < n; i++) {
		int h = f(t[i]);
		if (h > high)
			high = h;
	}
	for (int i = 0; i <= high; i++)
		tcount[i] = 0;
	for (int i = 0; i < n; i++)
		tcount[f(t[i])]++;
	for (int i = 1; i <= high; i++)
		tcount[i] += tcount[i - 1];
	for (int i = n - 1; i >= 0; i--)
		tmp[--tcount[f(t[i])]] = t[i];
	for (int i = 0; i < n; i++)
		t[i] = tmp[i];
	delete[] tmp;
}

typedef pair<pair<int,int>,int> para;

int getfirst(para p) {
	return p.first.first;
}

int getsecond(para p) {
	return p.first.second;
}

int KMRt[20][400200];
para tmp[400200];
int helper[400200];

void KMRprepare(char * T) {
	int n;
	for (n = 0; T[n]; n++)
		KMRt[0][n] = T[n];
	for (int k = 1; k < 20; k++) {
		int dist = 1 << (k - 1);
		for (int i = 0; i < n; i++)
			tmp[i] = para(pair<int, int> (KMRt[k - 1][i], (k + dist >= n ? 0
					: KMRt[k - 1][i + dist])), i);
		count_sort(tmp, n, getsecond);
		count_sort(tmp, n, getfirst);
		int akt = 1;
		for (int i = 0; i < n; i++) {
			if (i > 0 && tmp[i - 1].first != tmp[i].first)
				akt++;
			KMRt[k][tmp[i].second] = akt;
		}
	}
	int akt = 0;
	for (int i = 1; i <= n; i++) {
		if (1 << akt + 1 == i)
			akt++;
		helper[i] = akt;
	}
}

bool compare(int a, int b, int l) {
	int k = helper[l];
	if (KMRt[k][a] != KMRt[k][b])
		return 0;
	if (KMRt[k][a + l - (1 << k)] != KMRt[k][b + l - (1 << k)])
		return 0;
	return 1;
}

int n;
char T[200200];

bool singleFault(int p, int len) {
	if (p+len < n && T[len-1] != T[p+len]) return false;
	//printf("Smig\n");
	int l = 1, r = len;
	while (l != r) {
		int mid = (l + r)/2;
		if (compare(0,p,mid)) l = mid+1;
		else r = mid;
	}
	//printf("Odl %d\n", l);
	//printf("Test %d,%d,%d => %d\n", l-1, p+l, len-l, int( compare(0+l,p+l+1,len-l-1)));
	return l==len || compare(l-1,p+l,len-l);
}

bool testOkr(int len) {
	bool fault = false;
	for (int i=len;i<n;i+=len) {
		if (!compare(0,i,min(len,n-i))) {
			//printf("zawiodlo %d,%d,%d\n", 0,i,min(len,n-i));
			if (fault) return false;
			if (singleFault(i,min(len,n-i))) {
				i++;
				fault = true;
			}
			else return false;
		}
	}
	return true;
}

bool singleFaultRev(int p, int len) {
	if (p-len-1 >= 0 && T[p-len-1] != T[n-len]) return false;
	//printf("Smig\n");
	int l = 1, r = len;
	while (l != r) {
		int mid = (l + r)/2;
		//printf("Comp %d %d %d => %d\n" , n-mid,p-mid,mid, compare(n-mid,p-mid,mid));
		if (compare(n-mid,p-mid,mid)) l = mid+1;
		else r = mid;
	}
	//printf("Odl %d\n", l);
	//printf("Test %d,%d,%d => %d\n", p-len,n-len+1,len-l, int( compare(p-len,n-len+1,len-l)));
	return l==len || compare(p-len,n-len+1,len-l);
}

bool testOkrRev(int len) {
	bool fault = false;
	for (int i=len;i<n;i+=len) {
		if (!compare(max(0,n-i-len)+i,max(0,n-i-len),min(len,n-i))) {
			//printf("zawiodlo (%d) %d,%d,%d\n", i,max(0,n-i-len)+i,max(0,n-i-len),min(len,n-i));
			if (fault) return false;
			if (singleFaultRev(max(0,n-i),min(len,n-i))) {
				i++;
				fault = true;
			}
			else return false;
		}
	}
	return true;
}

int test() {
	scanf("%d%s", &n, T);
	KMRprepare(T);
	FOR(i,1,n) {
		if (testOkr(i) || testOkrRev(i)) return i;
	}
}

main() {
	int z; scanf("%d", &z);
	while (z--) printf("%d\n", test());
}

