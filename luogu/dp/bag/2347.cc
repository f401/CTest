#include <iostream>
unsigned int srcs[10] = {0, 1, 2, 3, 5, 10, 20};
unsigned int c[10], dp[123456];

int main(int argc, char *argv[]) {
  std::ios::sync_with_stdio(false), std::cin.tie(nullptr),
      std::cout.tie(nullptr);
  for (unsigned int i = 1; i <= 6; ++i) {
    std::cin >> c[i];
  }
  dp[0] = 1;
  for (unsigned int i = 1; i <= 6; ++i) {
    for (unsigned int j = 1; j <= c[i]; j++) {
      for (int k = 1000; k >= 0; k--) { // 寻找 已成立的重量
        if (dp[k]) {                    // 若此重量成立
          dp[k + srcs[i]] = 1; // 那么这个重量加上这个未使用的砝码的总重量也成立
        }
      }
    }
  }
  int ans = 0;
  for (
      int i = 1; i <= 1000;
      i++) // 一遍扫，统计成立的重量。记住从1开始循环，因为不使用砝码的情况在这里不统计
    if (dp[i])
      ans++;
  printf("Total=%d", ans); // 输出
  return 0;
}
