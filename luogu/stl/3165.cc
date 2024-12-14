#include <iostream>
#include <algorithm>
#include <vector>
#include <iterator>

int main(int argc, char *argv[])
{
	int n, tmp;
	std::cin >> n;
	std::vector<int> src;
	while (n--) {
		std::cin >> tmp;
		src.push_back(tmp);
	}
	std::vector<int>::iterator s = std::min_element(src.begin(), src.end());
	std::reverse(src.begin(), s + 1);
	std::reverse(s, src.end());
	std::copy(src.begin(), src.end(), std::ostream_iterator<int>(std::cout, " "));
	return 0;
}
