#include <iostream>
#define MAXN 1000

int p[MAXN], c[MAXN], dp[MAXN];

int main(int argc, char *argv[])
{
	std::ios::sync_with_stdio(false), std::cin.tie(nullptr), std::cout.tie(nullptr);
	int n, h;
	std::cin >> n >> h;
	for (int i = 1; i <= n; ++i) {
		std::cin >> p[i] >> c[i];
	}

	return 0;
}
