#include <bits/stdc++.h>

bool is[(long)1e8];

bool has7(int v) {
	for (; v ; v /= 10) {
		if (v % 10 == 7) return true;
	}
	return false;
}

int main(int argc, char *argv[])
{
	int T, mx = -1;
	std::cin >> T;
	std::vector<int> vec;
	while (T--) {
		int tmp;
		std::cin >> tmp;
		mx = std::max(mx, tmp);
		vec.push_back(tmp);
	}
	for (int i = 1; i <= mx * 2; ++i) {
		if (!is[i] && has7(i)) {
			for (int j = 1; j * i <= mx * 2; ++j) {
				is[i * j] = true;
			}
		}
	}
	for (int v : vec) {
		if (!is[v]) {
			v++;
			while (is[v]) {
				v++;
			}
			std::cout << v << std::endl;
		} else {
			std::cout << -1 << std::endl;
		}
	}
	return 0;
}
