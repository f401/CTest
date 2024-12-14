#include <iostream>
#define MAXN 4000

int dp[MAXN];

int main(int argc, char *argv[])
{
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr), std::cout.tie(nullptr);
	int n;
	std::cin >> n;
	for (int i = 1; i <= n; ++i) {
		std::cin >> dp[i];
	}
	int maxn = -0x3f3f3f3f;
	for (int i = 1; i <= n; ++i) {
		dp[i] = std::max(dp[i - 1] + dp[i], dp[i]);
		maxn = std::max(maxn, dp[i]);
	}
	std::cout << maxn;
	return 0;
}
