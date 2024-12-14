#include <bits/stdc++.h>
#define LC (k << 1)
#define RC (k << 1 | 1)

struct Tree {
	int lc, rc, w;
} tree[800000];

int srcs[800000];

void build(int n) {
	std::stack<int> st;
	int lstPop = 0;
	for (int i = 1; i <= n; ++i) {
		int sz = st.size();
		while (st.size() && tree[st.top()].w > srcs[i]) {
			lstPop = st.top();
			st.pop();
		}

		if (st.empty()) {
			tree[i].lc = lstPop;
		} else if (sz == st.size()) {
			tree[st.top()].rc = i;
		} else {
			tree[i].lc = lstPop;
			tree[st.top()].rc = i;
		}
		tree[i].w = srcs[i];
		st.push(i);
	}
}

int main(int argc, char *argv[])
{
	int n;
	std::cin >> n;
	for (int i = 1; i <= n; ++i) {
		scanf("%d", srcs + i);
	}
	build(n);
	int ans0 = 0, ans1 = 0;
	for (int i = 1; i <= n; ++i) {
		ans0 ^= i * (tree[i].lc + 1);
		ans1 ^= i * (tree[i].rc + 1);
	}
	printf("%d %d", ans0, ans1);
	return 0;
}
