#include <iostream>
#include <vector>
#include <map>

int main(int argc, char *argv[])
{
	int n, q;
	scanf("%d %d", &n, &q);
	std::map<int, int> data[n];
	while (q--) {
		int op;
		scanf("%d", &op);
		switch (op) {
			case 1: {
				int i, j, k;
				scanf("%d %d %d", &i, &j, &k);
				data[i][j] = k;
			}
			break;
			case 2:
			{
				int i, j;
				scanf("%d %d", &i, &j);
				printf("%d\n", data[i][j]);
			}
				
		}
	}
	return 0;
}
