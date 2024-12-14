#include <bits/stdc++.h>
#define int long lon

int srcs[500000];

signed main() {
	int n, k, maxn = 0, gcd;
	std::cin >> n >> k;
	for (int i = 1; i <= n; ++i) {
		std::cin >> srcs[i];
		maxn = std::max(maxn, srcs[i]);
	}
	for (int i = 1; i <= n; ++i, gcd = std::max(gcd, std::gcd(srcs[i], maxn)));
	int op = 0;
	for (int i = 1; i <= n; ++i) {
		if ((gcd - srcs[i]) % k == 0) {
			op += (maxn - srcs[i]) / k;
		} else {
			puts("NO");
			return 0;
		}
	}
	std::cout << "YES " << op;

	return 0;
}
