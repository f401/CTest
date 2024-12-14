#include <iostream>
#define MAXN 13910

struct Potion {
	int lose, win, need;
} poses[MAXN];

int main(int argc, char *argv[])
{
	std::ios::sync_with_stdio(false), std::cin.tie(nullptr), std::cout.tie(nullptr);
	int n, x;
	std::cin >> n >> x;
	for (int i = 1; i <= n; ++i) {
		std::cin >> poses[i].lose >> poses[i].win >> poses[i].need;
	}
	for (int i = 1; i <= n; ++i) {
		for (int j = 1; j <= n; ++j) {
			
		}
	}
	return 0;
}
