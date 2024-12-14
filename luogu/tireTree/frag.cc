#include <bits/stdc++.h>

int trie[10000][26], tot = 1;
bool end[10000];

void insert(std::string s) {
	int p = 1;
	for (int i = 0; i < s.length(); i++) {
		int ch = s[i] - 'a'; // 转换成数字
		if (!trie[p][ch])
			trie[p][ch] = ++tot; // 记录下标
		p = trie[p][ch];
	}
	end[p] = true;// 标记单词结束
}

bool search(std::string s) {
	int p = 1; // 树根开始查
	for (int i = 0; i < s.length(); ++i) {
		p = trie[p][s[i] - 'a'];
		if (!p) {
			return false;
		}
	}
	return end[p];
}

bool prefix(std::string s) {
	int p = 1; // 树根开始查
	for (int i = 0; i < s.length(); ++i) {
		p = trie[p][s[i] - 'a'];
		if (!p) {
			return false;
		}
	}
	return true;
}

void dfs(int p) {
	for (int i = 0; i < 26; ++i) {
		if (trie[p][i]) {
			printf("%c", i + 'a');
			dfs(trie[p][i]);
		}
	}
	putchar('\n');
}

int main(int argc, char *argv[])
{
	int n;
	scanf("%d", &n);
	while (n--) {
		std::string s;
		std::cin >> s;
		insert(s);
	}
	dfs(1);
	printf("Search: ");
	std::string s;
	std::cin >> s;
	printf("%d", search(s));
	return 0;
}
