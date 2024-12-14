#include <bits/stdc++.h>

int trie[5000000][80], tot = 1;
int end[5000000];

void insert(const std::string &s) {
  int p = 1;
  for (int i = 0; i < s.length(); ++i) {
    int ch = s[i] - '0';
    if (!trie[p][ch]) {
      trie[p][ch] = ++tot;
    }
    p = trie[p][ch];
  ++end[p];
  }
}

int search(const std::string &s) {
  int p = 1, result = 0;
  for (int i = 0; i < s.length(); ++i) {
    p = trie[p][s[i] - '0'];
    if (!p) {
      return 0;
    }
  }
  return end[p];
}

int main(int argc, char *argv[]) {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr), std::cout.tie(nullptr);
  int n, m, T = 1;
  std::cin >> T;
  while (T--) {
    for(int i=0;i<=tot;i++)
        for(int j=0;j<=122;j++)
                trie[i][j]=0;
        for(int i=0;i<=tot;i++)
            end[i]=0;
tot = 1;
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
  }
  return 0;
}
