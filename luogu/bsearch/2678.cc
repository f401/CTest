#include <iostream>
#include <vector>
#include <algorithm>

int l, n, m, tmp;
std::vector<int> src;

static inline bool __chk(int curr) {
	int now = 0, count = 0;
	for (int i = 0; i < src.size(); ++i) {
		if (src[i] - now <= curr) {
			count++;
			continue;
		}
		now = src[i];
	}
	if (l - now <= curr) ++count;
	return count <= m;
}

int main(int argc, char *argv[])
{
	std::cin >> l >> n >> m;
	
	while (n--) {
		std::cin >> tmp;
		src.push_back(tmp);
	}
	std::sort(src.begin(), src.end());
	int left = 1, right = l;
	while (left < right) {
		int mid = (left + right) >> 1;
		if (__chk(mid)) {
			left = mid + 1;
		} else 
			right = mid;
	}
	std::cout << left;
	return 0;
}
