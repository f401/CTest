#include <iostream>
#define MAXN 503359
int dp[MAXN];

int main(int argc, char *argv[]) {
	std::ios::sync_with_stdio(false), std::cin.tie(nullptr), std::cout.tie(nullptr);
	int m, s, t;
	std::cin >> m >> s >> t;
	
	for (int i = 1; i <= t; ++i) {
		if (m >= 10) {
			dp[i] = dp[i - 1] + 60;
			m -= 10;
		} else {
			dp[i] = dp[i - 1];
			m += 4;
		}
	}
	
	for (int i = 1; i <= t; ++i) {
		dp[i] = std::max(dp[i - 1] + 17, dp[i]);
		if (dp[i] >= s) {
			std::cout << "Yes" << std::endl << i;
			return 0;
		}
	}
	std::cout << "No" << std::endl << dp[t];
	return 0;
}
