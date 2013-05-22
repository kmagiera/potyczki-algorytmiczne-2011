#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#include <vector>
#include <string>
#include <iostream>

#define FOR(i,s,e) for (int i=(s);i<(e);i++)
#define REP(i,n) FOR(i,0,n)
#define FOREACH(i,c) for(typeof((c).begin()) i = (c).begin(); i != (c).end(); i++)
#define PB push_back
using namespace std;

typedef unsigned int uint32_t;

#define PRIMES 19
uint32_t PRIMEST[PRIMES] = {
	4118140291u,
	1937858827u,
	2709025367u,
	2875343293u,
	3216585923u,
	2222899649u,
	3866814299u,
	1809026267u,
	2036899177u,
	1134341051u,
	242290469u,
	3029020289u,
	2776369109u,
	1085184701u,
	2057056783u,
	2175824437u,
	41475827u,
	826020707u,
	448273937u
};

struct hasht {
	uint32_t hd[3];
	
	hasht() {
		hd[0] = PRIMEST[5];
		hd[1] = PRIMEST[2];
		hd[2] = PRIMEST[11];
	}
	
	void update(const hasht& a) {
		hd[0] = hashF(hd[0] + a.hd[2] + a.hd[0]);
		hd[1] = hashF(hd[1] + a.hd[0] + a.hd[1]);
		hd[2] = hashF(hd[2] + a.hd[1] + a.hd[2]);
	}
	void update(uint32_t dig) {
		hd[dig%3] = hashF(hd[0]+hd[1]+hd[2]+dig);
	}
	
	uint32_t hash32shift(uint32_t key) {
	  key = ~key + (key << 15); // key = (key << 15) - key - 1;
	  key = key ^ (key >> 12);
	  key = key + (key << 2);
	  key = key ^ (key >> 4);
	  key = key * 2057; // key = (key + (key << 3)) + (key << 11);
	  key = key ^ (key >> 16);
	  return key;
	}
	
	uint32_t hashF(uint32_t key) {
	  uint32_t c2 = 0x27d4eb2d; // a prime or an odd constant
	  key = (key ^ 61) ^ (key >> 16);
	  key = key + (key << 3);
	  key = key ^ (key >> 4);
	  key = key * c2;
	  key = key ^ (key >> 15);
	  return key;
	}
	
	bool operator==(const hasht& b) const {
		return hd[0]==b.hd[0] && hd[1]==b.hd[1] && hd[2]==b.hd[2];
	}
	bool operator<(const hasht& b) const {
		int i=0;
		while (i<2 && hd[i]==b.hd[i]) i++;
		return hd[i]<b.hd[i];
	}
};

typedef unsigned long long int ulld;
const ulld mod = 1000000007;

vector<int> G[500000];
int que[500000]; int qr = 0, qw = 0;
int used[500000];
bool vis[500000];
hasht hh[500000];
hasht hash[500000];

inline void hashinit(int id) {
	hash[id] = hasht();
}
inline void hashup(int id, const hasht& data) {
	hash[id].update(data);
}
inline void hashend(int id, int lvl) {
	hash[id].update(PRIMEST[lvl%PRIMES]);
//	hash[id] = hasz.hexdigest();
}

main() {
	int n,a,b,v;
	scanf("%d", &n);
	ulld res = 1;
	REP(i,n-1) {
		scanf("%d%d", &a, &b);
		G[a-1].PB(b-1);
		G[b-1].PB(a-1);
	}
	REP(i,n) if (G[i].size() == 1) {
		vis[i] = true;
		used[i] = 1;
		que[qw++] = i;
	}
	while (qr < qw) {
		v = que[qr++];
		vis[v] = true;
		//printf("Vertex %d\n", v+1);
		int hid = 0;
		FOREACH(next,G[v]) {
			//printf(" next %d siz %d used %d\n", *next+1, G[*next].size(), used[*next]);
			used[*next]++;
			if (!vis[*next]) {
				if (used[*next] == G[*next].size()-1) {
					que[qw++] = *next;
				}
			}
			else hh[hid++] = hash[*next];
		}
		sort(hh, hh+hid);
		/*printf("Childs: ");
		REP(i,hid) printf("%llu ", hh[i]);
		puts("");*/
		hashinit(v);
		if (hid > 0) hashup(v,hh[0]);
		ulld len = 1;
		FOR(i,1,hid) {
			hashup(v,hh[i]);
			if (hh[i] == hh[i-1]) len++;
			else len = 1;
			res = (res*len) % mod;
		}
		hashend(v,hid);
		//printf("Hash: %llu, res = %llu\n", hash[v], res); 
	}
	FOR(l,n-2,n) {
		v = que[l];
		int hid = 0;
		FOREACH(next,G[v]) if (*next != que[n-1] && *next != que[n-2]) hh[hid++] = hash[*next];
		sort(hh, hh+hid);
		hashinit(v);
		REP(i,hid) hashup(v,hh[i]);
		hashend(v,hid);
		//printf("Lasth %llu\n", hash[v]);
	}
	if (hash[que[n-1]]==hash[que[n-2]]) res = (res*2) % mod;
	printf("%llu\n", res);
}


