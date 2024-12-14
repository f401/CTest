#include <iostream>
#define MAXN 10000

int v[MAXN], w[MAXN], c[MAXN], dp[MAXN];

int main(int argc, char *argv[])
{
	std::ios::sync_with_stdio(false), std::cin.tie(nullptr), std::cout.tie(nullptr);
	int n, W;
	std::cin >> n >> W;
	for (int i = 1; i <= n; ++i) {
		std::cin >> v[i] >> w[i] >> c[i];
	}

	for (int i = 1; i <= n; ++i) {
		if (c[i] * w[i] >= W) {
			for (int j = w[i]; j <= W; ++j) {
				dp[j] = std::max(dp[j], dp[j - w[i]] + v[i]);
			}
		} else {
			for (int k = 1; c[i] > 0; k <<= 1) {
				int x = std::min(k, c[i]);
				for (int j = W; j >= w[i] * x; --j) {
					dp[j] = std::max(dp[j], dp[j - w[i] * x] + x * v[i]);
				}
				c[i] -= x;
			}
		}
	}
	std::cout << dp[W] << std::endl;
	return 0;
}
