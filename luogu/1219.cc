#include <iostream>

bool table[15][15];
int n, ans, output = 0;

inline bool __chk(int line, int col) {
	for (int i = 1; i <= col; ++i) {
		if (table[line][i]) {
			return false;
		}
	}
	for (int i = col, j = line; col >= 1 && j >= 1; --i, --j) {
		if (table[j][i]) {
			return false;
		}
	}
	for (int i = col, j = line; j <= n && i >= 1; --i, ++j) {
		if (table[j][i]) {
			return false;
		}
	}
	return true;
}

static inline int findLine(int col) {
	for (int i = 1; i <= n; ++i) {
		if (table[i][col]) {
			return i;
		}
	}
	return -1;;
}

void search(int col, int count) {
	if (count > n) {
		++ans;
		if (output++ < 3) {
			for (int i = 1; i <= n; ++i)
				printf("%d ", findLine(i));
			puts("");
		}
		return ;
	}
	for (int i = 1; i <= n; ++i) {
		if (__chk(i, col)) {
			table[i][col] = true;
			search(col + 1, count + 1);
			table[i][col] = false;
		} 
	}
}

int main(int argc, char *argv[])
{
	scanf("%d", &n);
	search(1, 1);
	printf("%d", ans);
	return 0;
}
