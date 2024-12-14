#include <iostream>
#define MAXN 10005

int win[MAXN], lose[MAXN], cost[MAXN], dp[MAXN][MAXN];

int main(int argc, char *argv[])
{
	std::ios::sync_with_stdio(false), std::cin.tie(nullptr), std::cout.tie(nullptr);
	int n, x;
	std::cin >> n >> x;
	for (int i = 1; i <= n; ++i) {
		std::cin >> lose[i] >> win[i] >> cost[i];
	}
	for (int i = 1; i <= n; ++i) {
		for (int j = 0; j <= x; ++j) {
			if (j < cost[i]) {
				dp[i][j] = dp[i - 1][j] + lose[i];
			} else {
				dp[i][j] = std::max(dp[i - 1][j] + lose[i], dp[i - 1][j - cost[i]] + win[i]);
			}
		}
	}
	std::cout << 5 * dp[n][x];
	return 0;
}
