#include <bits/stdc++.h>
#define LC(root) (root << 1)
#define RC(root) (root << 1 | 1)
#define int long long

int q, src[5000000];
struct {
  int l, r, value;

  struct {
    int mul, add;
  } tag;

  int dist() const { return r - l + 1; }
} tree[5000000];

void build(int root, int l, int r) {
  tree[root].tag.mul = 1;
  tree[root].l = l;
  tree[root].r = r;
  if (l == r) {
    tree[root].value = src[l];
    return;
  }
  int mid = (l + r) >> 1;
  build(LC(root), l, mid);
  build(RC(root), mid + 1, r);
  tree[root].value = tree[LC(root)].value + tree[RC(root)].value;
}

void pushdown(int root) {
  // if (tree[root].tag.add != 0 && tree[root].tag.mul != 1) {
  int mid = (tree[root].l + tree[root].r) >> 1;
  tree[LC(root)].value = (tree[LC(root)].value * tree[root].tag.mul +
                          (tree[LC(root)].dist() * tree[LC(root)].tag.add)) %
                         q;
  tree[RC(root)].value = (tree[RC(root)].value * tree[root].tag.mul +
                          (tree[RC(root)].dist() * tree[RC(root)].tag.add)) %
                         q;

  tree[LC(root)].tag.add =
      (tree[LC(root)].tag.add * tree[root].tag.mul + tree[root].tag.add) % q;
  tree[RC(root)].tag.add =
      (tree[RC(root)].tag.add * tree[root].tag.mul + tree[root].tag.add) % q;

  tree[LC(root)].tag.mul = (tree[LC(root)].tag.mul * tree[root].tag.mul) % q;
  tree[RC(root)].tag.mul = (tree[RC(root)].tag.mul * tree[root].tag.mul) % q;

  tree[root].tag.mul = 1, tree[root].tag.add = 0;
  // }
}

void add(int root, int l, int r, int k) {
  if (tree[root].l >= l && tree[root].r <= r) {
    tree[root].tag.add += k;
    tree[root].value += (tree[root].r - tree[root].l + 1) * k;
    return;
  }
  pushdown(root);
  int mid = (tree[root].r + tree[root].l) >> 1;
  if (l <= mid) {
    add(LC(root), l, r, k);
  }

  if (r >= mid + 1) {
    add(RC(root), l, r, k);
  }

  tree[root].value = tree[LC(root)].value + tree[RC(root)].value;
}

void mul(int root, int l, int r, int k) {
  if (tree[root].l >= l && tree[root].r <= r) {
    tree[root].tag.add *= k;
    tree[root].tag.mul *= k;
    tree[root].value *= k;
    return;
  }
  pushdown(root);
  int mid = (tree[root].r + tree[root].l) >> 1;
  if (l <= mid) {
    mul(LC(root), l, r, k);
  }

  if (r >= mid + 1) {
    mul(RC(root), l, r, k);
  }

  tree[root].value = (tree[LC(root)].value + tree[RC(root)].value) % q;
}

int query(int root, int l, int r) {
  if (tree[root].l >= l && tree[root].r <= r) {
    return tree[root].value;
  }
  pushdown(root);
  int mid = (tree[root].r + tree[root].l) >> 1, ans = 0;
  if (l <= mid) {
    ans += query(LC(root), l, r);
  }
  if (r >= mid + 1) {
    ans += query(RC(root), l, r);
  }

  return ans;
}

signed main() {
  int n, m;
  scanf("%lld %lld %lld", &n, &m, &q);
  for (int i = 1; i <= n; ++i) {
    scanf("%lld", src + i);
  }
  build(1, 1, n);
  while (m--) {
    int op, l, r, tmp;
    scanf("%lld %lld %lld", &op, &l, &r);
    switch (op) {
    case 1:
      scanf("%lld", &tmp);
      mul(1, l, r, tmp);
      break;
    case 2:
      scanf("%lld", &tmp);
      add(1, l, r, tmp);
      break;
    case 3:
      printf("%lld\n", query(1, l, r));
    }
  }
  return 0;
}
