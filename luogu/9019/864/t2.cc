#include <bits/stdc++.h>

int n;
long long m;
int a[1222222];

bool __chk(long long value) {
	long long k = m;
	long long prevCount = 0;
	for (int i = 1; i <= n; ++i) {
		long long requireCount = (a[i] + value - 1) / a[i];
		if (prevCount >= requireCount) {
			if (i != n) {
				k--;
			}
			prevCount = 0;
			continue;
		} else {
			requireCount -= prevCount;
			k -= requireCount * 2 - 1;
			prevCount = requireCount - 1;
		}
		if (k < 0) {
			return false;
		}
	}
	return k >= 0;
}

void sol() {
	scanf("%d %lld", &n, &m);
	long long l = 1, r = 100000000000;	
	for (int i = 1; i <= n; ++i) {
		scanf("%d", a + i);
	}
	while (l < r) {
		long long mid = (l + r) >> 1;
		if (__chk(mid)) {
			l = mid + 1;
		} else {
			r = mid;
		}
	}
	printf("%lld\n", l - 1);
}

signed main() {
	int T;
	scanf("%d", &T);
	while (T--) {
		sol();
	}

	return 0;
}
