#include <iostream>
#include <algorithm>

int w[5] = { 0, 2, 3, 4, 5 };
int v[5] = {0, 3, 4, 5, 6};
int bagV = 8;
int dp[5][9] = { { 0 } };
int item[5];

static void findMax() {
    for (size_t i = 1; i <= 4; i++)
    {
        for (size_t j = 1; j <= bagV; ++j) {
            if (j < w[i]) {
                dp[i][j] = dp[i - 1][j];
            }
            else {
                dp[i][j] = std::max(dp[i - 1][j], dp[i - 1][j - w[i]] + v[i]);
            }
        }
    }
}

static void findWhat(int i, int j) {
    if (i >= 0) {
        if (dp[i][j] == dp[i - 1][j]) {
            item[i] = 0;
            findWhat(i - 1, j);
        }
        else if (j - w[i] >= 0 && dp[i][j] == dp[i - 1][j - w[i]] + v[i]) {
            item[i] = 1;
            findWhat(i - 1, j - w[i]);
        }
    }
}

static multi_knapsack2(int n, int W) {
	for (int i = 1; i <= n; ++i) { 
	}
}

static void print() {
    for (size_t i = 0; i < 5; i++)
    {
        for (size_t j = 0; j < 9; ++j) {
            std::cout << dp[i][j] << ' ';
        }
        std::endl(std::cout);
    }
    std::endl(std::cout);
}

int main(int argc, char** argv, char** envp) {
    findMax();
    findWhat(4, 8);
    print();
    return 0;
}
