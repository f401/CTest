#include <iostream>
#include <vector>
#include <algorithm>

std::vector<int> src;
int l, n, k, tmp;

static inline bool __chk(int curr) {
	int count = 0, now = src[0];
	for (int i = 1; i < src.size(); ++i) { 
		int c = src[i];
		if (std::abs((float) now - c) / (float) curr >= 1) {
			count += std::abs(now - c) / curr;
			if (std::abs(now -c) % curr == 0) {
				--count;
			}
			now = c;
		}
	}
	return count <= k;
}

int main(int argc, char *argv[])
{
	scanf("%d %d %d", &l, &n, &k);
	for (int i = 1; i <= n; ++i) {
		scanf("%d", &tmp);
		src.push_back(tmp);
	}
	std::sort(src.begin(), src.end());

	int left = 0, right = l;
	while (left + 1 != right) {
		int mid = (left + right) >> 1;
		if (__chk(mid)) {
			right = mid;
		} else {
			left = mid;
		}
	}
	std::cout<< right; 
	return 0;
}
