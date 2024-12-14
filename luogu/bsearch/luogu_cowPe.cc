#include <bits/stdc++.h>
#include <iostream>
#include <vector>
#include <algorithm>

typedef int distance_t;
int n, c;

bool check(const std::vector<int> &Srcs, int curr) {
	int now = Srcs[0], count = 1;
	for (int i = 1; i < n; ++i) {
		if (Srcs[i] - now >= curr) {
			count++;
			now = Srcs[i];
		}
	}
	return count >= curr;
}

int main(int argc, char *argv[])
{
	distance_t tmp;
	std::vector<distance_t> srcs;
	
	scanf("%d %d", &n, &c);
	while (n--) {
		std::cin >> tmp;
		srcs.push_back(tmp);
	}

	std::sort(srcs.begin(), srcs.end());

	int l = 1, r = srcs.back() - srcs.front();
	while (l + 1 != r) {
		int mid = (l + r) >> 1;
		if (check(srcs, mid)) {
			l = mid;
		} else {
			r = mid;
		}
	}
	std::cout << l;

	return 0;
}
