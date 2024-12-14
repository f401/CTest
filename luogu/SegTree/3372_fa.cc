#include <bits/stdc++.h>
#define lc k << 1
#define rc k << 1 | 1
struct Node {
  int l, r, v, lz;
} tree[(int)(1e5 + 9) * 4];
int n, m;
void pushdown(int k) {
  tree[lc].lz += tree[k].lz;
  tree[lc].v += tree[k].lz * (tree[lc].r - tree[lc].l + 1);
  tree[rc].lz += tree[k].lz;
  tree[rc].v += tree[k].lz * (tree[rc].r - tree[rc].l + 1);
  tree[k].lz = 0;
}

void build(int k, int l, int r) {
  tree[k].l = l;
  tree[k].r = r;
  tree[k].lz = 0;
  if (l == r) {
    scanf("%d", &tree[k].v);
    return;
  }
  int mid = (l + r) >> 1;
  build(lc, l, mid);
  build(rc, mid + 1, r);
  tree[k].v = tree[lc].v + tree[rc].v;
}

void update(int k, int l, int r, long long val) {
  if (tree[k].l == l && tree[k].r == r) {
    tree[k].v += val * (tree[k].r - tree[k].l + 1);
    tree[k].lz += val;
    return;
  }
  if (tree[k].lz != 0) {
    pushdown(k);
  }
  int mid = (tree[k].l + tree[k].r) >> 1;
  if (r <= mid) {
    update(lc, l, r, val);
  } else if (l > mid) {
    update(rc, l, r, val);
  } else {
    update(lc, l, mid, val);
    update(rc, mid + 1, r, val);
  }
  tree[k].v = tree[lc].v + tree[rc].v;
}

long long query(int k, int l, int r) {
  if (tree[k].l == l && tree[k].r == r) {
    return tree[k].v;
  }
  if (tree[k].lz != 0) {
    pushdown(k);
  }
  int mid = (tree[k].l + tree[k].r) >> 1;
  if (r <= mid) {
    return query(lc, l, r);
  } else if (l > mid) {
    return query(rc, l, r);
  } else {
    return query(lc, l, mid) + query(rc, mid + 1, r);
  }
}

int main(int argc, char *argv[]) {
  scanf("%d %d", &n, &m);
  build(1, 1, n);
  while (m--) {
    int op;
    scanf("%d", &op);
    if (op == 1) {
      int x, y, k;
      scanf("%d %d %d", &x, &y, &k);
      update(1, x, y, k);
    } else {
      int x, y;
      scanf("%d %d", &x, &y);
      printf("%lld\n", query(1, x, y));
    }
  }
  return 0;
}
