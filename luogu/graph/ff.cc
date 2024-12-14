void solve(int x, int v) {
	a[x] = v;
	for (int i = 0; i < p[x].size(); ++i)
		if (a[p[x][i]] == 0)
			solve(p[x][i], v);
	for (int i = n; i >= 0;i --) {
		if (a[i] == 0)
			solve(i, i);
	}
}
