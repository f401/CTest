#include <iostream>
#include <cstring>

int n, m, t, ans = 0;
int startX, startY;
int endX, endY;

int src[20][20];

void dfs(bool** visited, int currX, int currY) {
	if (src[currX][currY] || visited[currX][currY]) {
		return ;
	}

	if (currX == endX && currY == endY) {
		++ans;
		return;
	}
	visited[currX][currY] = true;
	dfs(visited, currX + 1, currY);
	dfs(visited, currX - 1, currY);
	dfs(visited, currX, currY + 1);
	dfs(visited, currX, currY - 1);
	visited[currX][currY] = false;
}

int main(int argc, char *argv[])
{
	scanf("%d %d %d", &n, &m, &t);
	scanf("%d %d %d %d", &startX, &startY, &endX, &endY);
	for (int i = 0; i <= n + 1; ++i) {
		src[i][0] = 1;
		src[n + 1][i] = 1;
	}
	for (int i = 0; i <= m + 1; ++i) {
		src[0][i] = 1;
		src[i][n + 1] = 1;
	}
	src[startX][startY] = src[endX][endY] = 0;
	int x, y;
	while (t--) {
		scanf("%d %d", &x, &y);
		src[x][y] = 1;
	}
	bool** visited = new bool*[20];
	for (int i = 0; i < 20; ++i) {
		visited[i] = new bool[20] { false };
	}
	dfs(visited, startX, startY);
	printf("%d", ans);
	return 0;
}
