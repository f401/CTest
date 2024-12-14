#include <bits/stdc++.h>

int n, ans = 0;
std::vector<std::string> srcs;
int vis[30];

int common(std::string &s1, std::string &s2) {
  int c = 0, loop = std::min(s1.size(), s2.size());
  for (int i = loop - 1; i >= 0; --i) {
	  for (int j = i; j < loop; ++j) {
		if (s2[j + s2.size() - loop] == s1[j - i]) {
			c++;
		} else {
			c = 0;
			break;
		}
	  }
	  if (c != 0 && c != s1.size()) return c;
  }
  return c == s1.size() ? 0: c;
}

void dfs(int curr, int num) {
  ans = std::max(ans, num);
  vis[curr]++;
  for (int i = 0; i < n; ++i) {
    int cnt;
    if (vis[i] != 2 && (cnt = common(srcs[i], srcs[curr]))) {
	  printf("Compare: %s, %s, cnt: %d, num : %d\n", srcs[curr].c_str(), srcs[i].c_str(), cnt, num + srcs[i].size() - cnt);
      dfs(i, num + srcs[i].size() - cnt);
    }
  }
  vis[curr]--;
}

signed main() {
  std::cin >> n;
  for (int i = 0; i <= n; ++i) {
    std::string str;
	std::cin >> str;
    srcs.push_back(str);
  }
  dfs(n, srcs[n].size());
  std::cout << ans;
  return 0;
}
