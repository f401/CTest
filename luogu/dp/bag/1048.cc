#include <iostream>
#define MAXN 123456

int dp[MAXN], v[MAXN], weight[MAXN];

int main(int argc, char *argv[])
{
	std::ios::sync_with_stdio(false), std::cin.tie(nullptr), std::cout.tie(nullptr);
	int m, t;
	std::cin >> t >> m;
	for (int i = 1; i <= m; ++i){ 
		std::cin >> weight[i] >> v[i];
	}
	for (int i = 1; i <= m; ++i) {
		for (int w = t; w >= weight[i]; --w) {
			dp[w] = std::max(dp[w], dp[w - weight[i]] + v[i]);
		}
	}
	std::cout << dp[m];
	return 0;
}
