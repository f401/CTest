#include <bits/stdc++.h>
#include <iostream>
#define MAXN 1234567

unsigned int cost[MAXN];

unsigned int dp[MAXN][MAXN];

int main(int argc, char *argv[]) {
  std::ios::sync_with_stdio(false), std::cin.tie(nullptr),
      std::cout.tie(nullptr);
  unsigned int n, m; // m 背包容量
  std::cin >> n >> m;
  for (unsigned int i = 1; i <= n; ++i) {
    std::cin >> cost[i];
  }
  size_t cnt = 0;
  for (unsigned int i = 1; i <= n; ++i) { // 数量
    for (unsigned int j = 1; j <= m; ++j) {
      if (j == cost[i]) {
        dp[i][j] = dp[i - 1][j] + 1;
      }
      if (j > cost[i]) {
        dp[i][j] = dp[i - 1][j] + dp[i - 1][j - cost[i]];
      }
      if (j < cost[i]) {
        dp[i][j] = dp[i - 1][j];
      }
    }
  }
  std::cout << dp[n][m];

  return 0;
}
