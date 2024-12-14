#include <iostream>
#include <vector>

int main(int argc, char *argv[])
{
	std::vector<int> src;
	int n, m, tmp;
	scanf("%d %d", &n, &m);
	while (n--) {
		std::cin >> tmp;
		src.push_back(tmp);
	}

	while (m--) {
		std::cin >> tmp;
		std::cout << src[tmp - 1] << std::endl;
	}
	return 0;
}
