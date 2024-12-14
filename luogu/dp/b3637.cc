#include <iostream>

long long dp[10000], src[10000];

int main(int argc, char *argv[])
{
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr), std::cout.tie(nullptr);
	int n;
	std::cin >> n;
	for (int i = 1; i <= n; ++i) {
		std::cin >> src[i];
	}

	long long ans = 0;
	for (int i = 1; i <= n; ++i) {
		dp[i] = 1;
		for (int j = 1; j < i; ++j) {
			if (src[j] < src[i]) {
				dp[i] = std::max(dp[i], dp[j] + 1);
			}
		}
		ans = std::max(ans, dp[i]);
	}
	std::cout << ans;
	return 0;
}
