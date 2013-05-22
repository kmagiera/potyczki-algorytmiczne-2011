#include <cstdio>
#include <vector>
#include <algorithm>
#include <set>
using namespace std;

#define FOR(i,n) for(int i=0;i<(n);i++)
#define INF 20000000

typedef pair<int,int> para;

vector<int> full[1050000];
set<para> pts;
int dist[500005];
para ints[500005];
int n,m,p,N = 1;

void insertIntFull(int vid, const para& inter, int pid, const para& p) {
	if (inter.first >= p.first && inter.second <= p.second) {
		full[vid].push_back(pid);
		return;
	}
	int mid = (inter.first + inter.second)/2;
	if (p.first <= mid) insertIntFull(2*vid+1, para(inter.first, mid), pid, p);
	if (p.second > mid) insertIntFull(2*vid+2, para(mid+1,inter.second), pid, p);
}

void findIntFull(int vid, const para& inter, const para& p, vector<int>& q) {
	q.insert(q.end(), full[vid].begin(), full[vid].end());
	full[vid].clear();
	if (inter.first >= p.first && inter.second <= p.second) return;
	int mid = (inter.first + inter.second)/2;
	if (p.first <= mid) findIntFull(2*vid+1, para(inter.first, mid), p, q);
	if (p.second > mid) findIntFull(2*vid+2, para(mid+1,inter.second), p, q);
}

void insertInt(int pid, const para& p) {
	insertIntFull(0, para(0,N-1), pid, p);
	pts.insert(para(p.first,pid));
	pts.insert(para(p.second,pid));
}

void findInt(const para& p, vector<int>& q) {
	findIntFull(0, para(0,N-1), p, q);
	set<para>::iterator it = pts.lower_bound(para(p.first, -1)),
		end = pts.lower_bound(para(p.second, INF));
	for (; it != end; pts.erase(it++)) {
		q.push_back(it->second);
	}
}

main() {
	int a,b;
	scanf("%d%d%d", &n, &m, &p);
	vector<int> q, nq;
	while (N-1 < n) N <<= 1;
	FOR(i,2*m) {
		scanf("%d%d", &ints[i].first, &ints[i].second);
		dist[i] = INF;
		insertInt(i, ints[i]);
	}
	findInt(para(p,p), q);
	for (int d = 1; !q.empty(); d++) {
		nq = q;
		q.clear();
		FOR(i,nq.size()) {
			if (dist[nq[i]^1] == INF) {
				findInt(ints[nq[i]^1], q);
				dist[nq[i]^1] = d;
			}
		}
	}
	//FOR(i,2*m) printf("%d %d -> %d\n", ints[i].first, ints[i].second, dist[i]);
	vector<para> t;
	FOR(i,2*m) {
		t.push_back(para(ints[i].first, -i-1));
		t.push_back(para(ints[i].second, i+1));
	}
	sort(t.begin(), t.end());
	multiset<int> ms;
	int k = 0;
	for (int i = 1; i <= n; i++) {
		while (k < t.size() && (t[k].first < i || (t[k].first == i && t[k].second < 0))) {
			if (t[k].second < 0) ms.insert(dist[-t[k++].second-1]);
			else ms.erase(ms.find(dist[t[k++].second-1]));
		}
		printf("%d\n", (ms.empty() || p == i) ? 0 : *ms.begin());
		while (k < t.size() && t[k].first == i)
			ms.erase(ms.find(dist[t[k++].second-1]));
	}
}

