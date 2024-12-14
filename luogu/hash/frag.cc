#include <bits/stdc++.h>

const int MOD = 189, base = 1993;

int n, ans;
char s[10000];
std::vector<std::string> linker[MOD + 2];

void insert() {
	int hash = 1;
	for (int i = 0; s[i]; ++i) {
		hash = (hash * 1ll * base + s[i]) % MOD;
	}
	std::string t = s;
	for (int i = 0; i < linker[hash].size(); i++) {
		if (linker[hash][i] == t) {
			return;
		}
	}
	linker[hash].push_back(t);
	++ans;
}
