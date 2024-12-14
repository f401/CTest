#include <bits/stdc++.h>

int trie[10000][26];
int end[10000], tot = 1, depth[10000];

void insert(const std::string &str) {
	int p = 1;
	for (size_t i = 0; i < str.size(); ++i) {
		int ch = str[i] - 'a';
		if (!trie[p][ch]) {
			trie[p][ch] = ++tot;
		}
		p = trie[p][ch];
		end[p]++;
		depth[p] = i;
	}
}

int dfs(int root, int curr) {
	int ans = 0;
	for (int i = 0; i < 26; ++i) {
		if (trie[root][i]) {
			ans = std::max(dfs(trie[root][i], curr + 1), curr);
		}
	}
	return ans;
}

int main(int argc, char *argv[])
{
	int n;
	std::cin >> n;
	while (n--) {
		std::string s;
		std::cin >> s;
		insert(s);
	}
	std::cout << dfs(1, 0);
	return 0;
}
