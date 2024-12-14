#include <iostream>


long long dp[1391331];

int main(int argc, char *argv[])
{
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr), std::cout.tie(nullptr);
	int n;
	std::cin >> n;
	dp[1] = 1;
	dp[2] = 2;
	dp[3] = 4;
	for (int i = 4; i <= n; ++i) {
		dp[i] += dp[i - 1] + dp[i - 2] + dp[i - 3];
	}
	std::cout << dp[n];
	return 0;
}
