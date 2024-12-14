#include <iostream>
#define MAXN 50000

int src1[MAXN], src2[MAXN], dp[MAXN][MAXN];

int main(int argc, char *argv[]) {
	std::ios::sync_with_stdio(false), std::cin.tie(nullptr), std::cout.tie(nullptr);
	int n;
	std::cin >> n;
	for (int i = 1; i <= n; ++i) {
		std::cin >> src1[i];
	}
	for (int i = 1; i <= n; ++i) {
		std::cin >> src2[i];
	}
	for (int i = 1; i <= n; ++i) {
		for (int j = 1; j <= n; ++j) {
			if (src1[i] == src2[j]) {
				dp[i][j] = dp[i - 1][j - 1] + 1;
			} else {
				dp[i][j] = std::max(dp[i - 1][j], dp[i][j - 1]);
			}
		}
	}
	std::cout << dp[n][n];
	return 0;
}
