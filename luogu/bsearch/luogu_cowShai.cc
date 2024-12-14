#include <iostream>
#include <vector>
#include <algorithm>

std::vector<int> srcs;
int n, a, b, tmp;

bool check(int curr, int r) {
	int cnt = 0;
	for (int i = 0; i < b; ++i) {
		if (curr * a >= srcs[i]) {
			continue;
		} else {
			int remain = (srcs[i] - a * curr)/b;
			if ((srcs[i] - a * curr) % b != 0) 
				++remain;
			cnt += remain;
		}
	}
	return cnt <= curr;
}

int main(int argc, char *argv[])
{
	std::cin >> n >> a >> b;
	for (int i = 0; i < n; ++i) {
		std::cin >> tmp;
		srcs.push_back(tmp);
	}
	std::sort(srcs.begin(), srcs.end());
	int l = -1, r = srcs.size();

	while (l + 1 != r) {
		int mid = (l + r) >> 1;
		if (check(mid, r)) {
			r = mid;
		} else {
			l = mid;
		}
	}
	std::cout << r;
	return 0;
}
