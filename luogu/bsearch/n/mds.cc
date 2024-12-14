#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>

int main(int argc, char *argv[])
{
	int n, m, tmp;
	scanf("%d %d", &n, &m);
	std::vector<int> a1, a2; 
	for (int i = 0; i < n; ++i) {
		scanf("%d", &tmp);
		a1.push_back(tmp);
	}
	for (int j = 0; j < m; ++j) {
		scanf("%d", &tmp);
		a2.push_back(tmp);
	}
	std::sort(a2.begin(), a2.end());
	for (int i : a1) {
		if (std::binary_search(a2.cbegin(), a2.cend(), i)) {
			std::cout << i << " ";
		}
	}
	return 0;
}
