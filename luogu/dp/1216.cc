#include <iostream>
#define MAXN 5000

int dp[MAXN][MAXN];

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);

  int n;
  std::cin >> n;
  for (int i = 1; i <= n; ++i) {
    for (int j = 1; j <= i; ++j) {
      std::cin >> dp[i][j];
    }
  }

  int max = 0;
  for (int i = 1; i <= n; ++i) {
    for (int j = 1; j <= i; ++j) {
      dp[i][j] += std::max(dp[i - 1][j], dp[i - 1][j - 1]);
      max = std::max(max, dp[i][j]);
    }
  }

  std::cout << max;
}
