#include <algorithm>
#include <iostream>
#define MAXN 10005
#define M 105
int dp[MAXN]; // dp[j]表示当前已放入容量为j的背包获得的最大价值
int w[M], v[M], c[M]; // w[i]表示第i个物品的重量, v[i]表示第i个物品价值,
                      // c[i]表示第i个物品的数量
int n, W; // n表示第n个物品, W表示背包容量

void multi_knapsack1(int n, int k) { // 暴力拆分, 容易超时
  for (int i = 1; i <= n; ++i) {
    for (int k = 1; k <= c[i]; ++k) { // 多一层循环
      for (int j = W; j >= w[i]; j--) {
        dp[j] = std::max(dp[j], dp[j - w[i]] + v[i]);
      }
    }
  }
}

void multi_knapsack2(int n, int W) { // 二进制拆分
  for (int i = 1; i <= n; ++i) {
    if (c[i] * w[i] >= W) { // 转换为完全背包
      for (int j = w[i]; j <= W; ++j) {
        dp[j] = std::max(dp[j], dp[j - w[i]] + v[i]);
      }
    } else {
      for (int k = 1; c[i] > 0; k <<= 1) { // 二进制拆分
        int x = std::min(k, c[i]);
        for (int j = W; j >= w[i] * x; --j) { // 转换为01背包
          dp[j] = std::max(dp[j], dp[j - w[i] * x] + x * v[i]);
        }
        c[i] -= x;
      }
    }
  }
}

int main(int argc, char *argv[])
{
	std::cout << "请输入物品个数n: ";
	std::cin >> n;
	std::cout << "请输入背包容量W: ";
	std::cin >> W;
	for (int i = 1; i <= n; ++i) {
		std::cin >> w[i] >> v[i] >> c[i];
	}
	for (int j = 1; j <= W; ++j) {
		dp[j] = 0;
	}
	multi_knapsack1(n, W);
	std::cout << "最大价值: " << dp[W] << &std::endl;
	for (int j = 1; j <= W; ++j) {
		std::cout << dp[j] << " ";
	}
	std::endl(std::cout);
	return 0;
}
