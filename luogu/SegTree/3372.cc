#include <iostream>

#define LC(K) ((K) << 1)     // K * 2
#define RC(K) ((K) << 1 | 1) // k * 2 + 1
#define MAXN 10005
#define INF 0x3f3f3f3f
int n, a[MAXN];

struct Node {
  int l, r, lazy, sum;
} tree[MAXN * 4];

void makeLazy(int k, int v) {
  tree[k].sum += v; // 更新最值
  if (tree[k].lazy == -1)
    tree[k].lazy = v;
  else
    tree[k].lazy += v;
}

void pushdown(int k) {
  float fenSHu = tree[k].lazy / (tree[k].r - tree[k].l + 1);
  makeLazy(LC(k), fenSHu);
  makeLazy(RC(k), fenSHu);
  tree[k].lazy = -1;
}

void build(int k, int l, int r) { // k 存储下标
  tree[k].l = l;
  tree[k].r = r;
  tree[k].lazy = -1;
  if (l == r) {
    tree[k].sum = a[l];
    return;
  }
  int mid = (l + r) >> 1;
  build(LC(k), l, mid);     // 创建左子树
  build(RC(k), mid + 1, r); // 递归创建右子树
  tree[k].sum =
      tree[LC(k)].sum + tree[RC(k)].sum; // 更新结点的最值等于左右孩子的最值
}

void update(int k, int l, int r, int v) { // 将区间[l...r]修改更新为v
  if (tree[k].l >= l && tree[k].r <= r) { // 找到该区间
    if (tree[k].l != tree[k].r) {
      makeLazy(k, v * (tree[k].r - tree[k].l + 1));
      tree[k].sum =
          tree[LC(k)].sum + tree[RC(k)].sum;
    } else {
      tree[k].sum += v;
    }
    return;
  }
  if (tree[k].lazy != -1) {
    pushdown(k);
  }
  int mid = (tree[k].l + tree[k].r) >> 1; // 划分点
  if (l <= mid)
    update(LC(k), l, r, v); // 去左子树更新
  if (r > mid)
    update(RC(k), l, r, v); // 去右子树更新
  tree[k].sum =
      tree[LC(k)].sum + tree[RC(k)].sum; // 更新结点的最值等于左右孩子的最值
}

int querySum(int k, int l, int r) { // 区间最值
  if (tree[k].l >= l && tree[k].r <= r) {
    return tree[k].sum;
  }
  if (tree[k].lazy != -1) {
    pushdown(k); // 懒标记下移
  }
  int mid = (tree[k].l + tree[k].r) >> 1; // 划分点
  if (l <= mid) {
    return querySum(LC(k), l, r); // 左子树
  } else if (r > mid) {
    return querySum(RC(k), l, r); // 右子树
  }
  return querySum(LC(k), l, r) + querySum(RC(k), l, r);
}

signed main(int argc, char *argv[]) {
  int m;
  std::cin >> n >> m;
  for (int i = 1; i <= n; i++) {
    std::cin >> a[i];
  }
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
      printf("%d\n", querySum(1, x, y));
    }
  }
  return 0;
}
