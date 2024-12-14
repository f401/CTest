#include <bits/stdc++.h>

int s[4000][4000];
int pre[4000];
int dx[] = {1, 0, -1, 0};
int dy[] = {0, 1, 0, -1};

void dfs(int i, int j) {
  if (s[i][j] == 0) {
    s[i][j] = 2;
    for (int k = 0; k < 4; ++k) {
      if (s[i + dx[k]][j + dy[k]] == 0) {
        dfs(i + dx[k], j + dy[k]);
      }
    }
  }
}

signed main() {
  int n;
  std::cin >> n;
  std::vector<std::pair<int, int>> det;
  for (int i = 1; i <= n; ++i) {
    int t = 0;
    for (int j = 1; j <= n; ++j) {
      int tmp;
      std::cin >> tmp;
      s[i][j] = tmp;
      if (t == 0 && tmp == 1)
        t = j;
    }
    pre[i] = t;
  }
  for (int i = n; i > 0; --i) {
    if (pre[i] != 0) {
      if (s[i][pre[i] + 1] == 0) {
        dfs(i, pre[i] + 1);
		break;
      }
    }
  }
  for (int i = 1; i <= n; ++i) {
	  for (int j = 1; j <= n; ++j) {
		  printf("%d ", s[i][j]);
	  }
	  putchar('\n');
  }
  return 0;
}
