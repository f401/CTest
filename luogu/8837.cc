#include <iostream>
#include <algorithm>

long long pep[100001], cost[100001];

int main(int argc, char *argv[])
{
	std::ios::sync_with_stdio(false), std::cin.tie(nullptr), std::cout.tie(nullptr);
	int n, m;
	std::cin >> n >> m;
	for (int i = 1; i <= n; ++i) {
		std::cin >> pep[i];
	}
	for (int i = 1; i <= m; i++) {
		std::cin >> cost[i];
	}
	std::sort(pep + 1, pep + 1 + n);
	std::sort(cost + 1, cost + m + 1);
	int ans = 0, cstIdx = 1, i = 1;
	for (; i <= n && cstIdx <= m; ++i) {
		if (pep[i] >= cost[cstIdx]) {
			++cstIdx;
			ans++;
		} 
	}
	std::cout << ans;
	return 0;
}
