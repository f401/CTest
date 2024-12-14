#include <iostream>
#include <vector>
#include <algorithm>


int mbsearch(const std::vector<int>& src, int target) {
	int l = -1, r = src.size();
	while (l != r - 1) {
		int mid = ( l + r ) >> 1;
		if (src[mid] < target) {
			l = mid;
		} else {
			r = mid;
		}
	}
	if (src[r] == target)
		return r;
	else 
		return -2;
}

int main(int argc, char *argv[])
{
	int n, m, index = 0;
	scanf("%d %d", &n, &m);
	std::vector<int> src;
	while (n--) {
		int tmp;
		scanf("%d", &tmp);
		src.push_back(tmp);
	}
	while (m--) {
		int tmp;
		scanf("%d", &tmp);
		std::cout << mbsearch(src,tmp) + 1 << " ";
	}
	return 0;
}
