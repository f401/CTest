#include <iostream>
#include <algorithm>
#define MAXN 10005
#define M 105
int dp[MAXN]; // dp[j] 表示当前放入容量为j的背包获得的最大价值
int w[M][M], v[M][M], c[M]; // w[i][j] 表示第i组第j个物品的数量, v[i][j]表示第i组第j个物品的价值, c[i]表示第i个物品的数量
int n, W; 

void group_knapsack(int n, int W) { // 分组背包
	for (int i = 1; i <= n; ++i) {
		for (int j = W; j >= 0; --j) {
			for (int k = 1; k <= c[i]; ++k) { // 枚举组内各个物品
				if (j >= w[i][k]) {
					dp[j] = std::max(dp[j], dp[j - w[i][k]] + v[i][k]);
				}
			}
		}
	}
}
int main(int argc, char *argv[])
{
	std::cout << "请输入物品组数: ";
	std::cin >> n;
	std::cout << "请输入背包容量: ";
	std::cin >> W;
	for (int i = 1; i <= n; ++i) {
		std::cin >> c[i];
		for (int j = 1; j <= c[i]; ++j) {
			std::cin >> w[i][j] >> v[i][j];
		}
	}
	group_knapsack(n, W);
	std::cout << "背包最大容量: " << dp[W] << std::endl;
	return 0;
}
