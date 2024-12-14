#include <bits/stdc++.h>

int trie[100000][26], tot = 1;
int end[100000];

void insert(const std::string &s) {
	int p = 1;
	for (int i = 0; i < s.length(); ++i) {
		int ch = s[i] - 'a';
		if (!trie[p][ch]) {
			trie[p][ch] = ++tot;
		}
		p = trie[p][ch];
	}
	++end[p];
}

int search(const std::string &s) {
	int p = 1, result = 0;
	for (int i = 0; i < s.length(); ++i) {
		p = trie[p][s[i] - 'a'];
		if (!p) {
			return result;
		}
		if (end[p]) {
			result += end[p];
		}
	}
	return result;
}

int main(int argc, char *argv[])
{
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr), std::cout.tie(nullptr);
	int n, m;
	std::cin >> n >> m;
	std::string s;
	while (n--) {
		std::cin >> s;
		insert(s);
	}
	while (m--) {
		std::cin >> s;
		std::cout << search(s) << std::endl;
	}
	return 0;
}
