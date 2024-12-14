#include <bits/stdc++.h>
#define int long long

const int MOD = 1e9+7, MAXN = 1e7+7;

int ksm(int base, int l) {
	int res = 1;
	while (l) {
		if (l & 1) {
			res = res * base % MOD;
		}
		base = base * base % MOD;
		l >>= 1;
	}
	return res;
}

int fact[MAXN];
int inv[MAXN];

void init(int n) {
	fact[0] =  1;
	for (int i = 1; i <= n; ++i) {
		fact[i] = (fact[i - 1] * i) % MOD;
	}
	inv[n] = ksm(fact[n], MOD - 2);
	for (int i = n; i >= 1; i--) inv[i - 1] = 1ll * inv[i] * i % MOD;
}

int A(int a, int b) {
	if (b == 0) return 1;
	if (b > a) return 0;
	return fact[a] * inv[a - b] % MOD;
}

int C(int a, int b) {
	if (b == 0) return 1;
	if (b > a) return 0;
	return A(a, b) * inv[b] % MOD;
}
// n = 1/2 (MOd)
// 2n = 1 (MOD)
// 2n = 1 + MOD
signed main() {
	int n, m, ans = 0;
	std::cin >> n >> m;
	init(m + n + 10);
	int inv2 = ksm(2, MOD - 2);
	printf("INV2: %lld\n", inv2);
	if (m == n) {
		printf("%lld", (fact[n - 1] * inv2) % MOD);
		return 0;
	}

	if (m == 0) {
		puts("1");
		return 0;
	}

	for (int i = 1; i <= n - m; ++i) {
		(ans += C(n, n - m - i) % MOD * fact[m] % MOD * C(m + i, i) % MOD * C(m - 1, i - 1) % MOD * ksm(inv2, i) % MOD) %= MOD;
	}
	printf("%lld", ans);
	return 0;
}
