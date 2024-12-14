#include <iostream>

#define LC(K) ((K) << 1)     // K * 2
#define RC(K) ((K) << 1 | 1) // k * 2 + 1
#define MAXN 10005
#define INF 0x3f3f3f3f
int n, a[MAXN];

struct Node {
  int l, r, mx, lazy;
} tree[MAXN * 4];

void lazy(int k, int v) {
  tree[k].mx = v;   // 更新最值
  tree[k].lazy = v; // 做懒标记
}

void pushdown(int k) {
  lazy(LC(k), tree[k].lazy); // 传递给左孩子
  lazy(RC(k), tree[k].lazy); // 传递给右孩子
  tree[k].lazy = -1;         // 清除自己的懒标记
}

void build(int k, int l, int r) { // k 存储下标
  tree[k].l = l;
  tree[k].r = r;
  tree[k].lazy = -1;
  if (l == r) {
    tree[k].mx = a[l];
    return;
  }
  int mid = (l + r) >> 1;
  build(LC(k), l, mid);     // 创建左子树
  build(RC(k), mid + 1, r); // 递归创建右子树
  tree[k].mx = std::max(tree[LC(k)].mx,
                        tree[RC(k)].mx); // 更新结点的最值等于左右孩子的最值
}

void update(int k, int l, int r, int v) { // 将区间[l...r]修改更新为v
  if (tree[k].l >= l && tree[k].r <= r) { // 找到该区间
    return lazy(k, v); // 更新并做懒标记
  }
  if (tree[k].lazy != -1) { 
    pushdown(k);
  }
  int mid = (tree[k].l + tree[k].r) >> 1; // 划分点
  if (l <= mid)
    update(LC(k), l, r, v); // 去左子树更新
  else
    update(RC(k), l, r, v); // 去右子树更新
  tree[k].mx = std::max(tree[LC(k)].mx,
                        tree[RC(k)].mx); // 更新结点的最值等于左右孩子的最值
}

void update(int k, int i, int v) { // 点更新, 将a[i]的值改成v
  if (tree[k].l == tree[k].r && tree[k].l == i) {
    tree[k].mx = v;
    return;
  }
  int mid = (tree[k].l + tree[k].r) >> 1; // 划分点
  if (i <= mid) {
    update(LC(k), i, v); // 去左孩子找
  } else {
    update(RC(k), i, v); // 去右孩子找
  }
  tree[k].mx = std::max(tree[LC(k)].mx,
                        tree[RC(k)].mx); // 更新结点的最值等于左右孩子的最值
}

int query(int k, int l, int r) { // 区间最值
  if (tree[k].l >= l && tree[k].r <= r) {
    return tree[k].mx;
  }
  if (tree[k].lazy != -1) {
	  pushdown(k); // 懒标记下移
  }
  int mid = (tree[k].l + tree[k].r) >> 1; // 划分点
  int max = -INF;
  if (l <= mid) {
    max = std::max(max, query(LC(k), l, r)); // 左子树
  }
  if (r > mid) {
    max = std::max(max, query(RC(k), l, r)); // 右子树
  }
  return max;
}

void print(int x) {
  if (tree[x].mx) {
    std::cout << x << "\t" << tree[x].l << "\t" << tree[x].r << "\t"
              << tree[x].mx << std::endl;
    print(LC(x));
    print(RC(x));
  }
}

signed main(int argc, char *argv[]) {
  std::cin >> n;
  for (int i = 1; i <= n; i++) {
    std::cin >> a[i];
  }
  build(1, 1, n);
  print(1);
  std::cout << "查询最值区间: " << std::endl;
  int l, r;
  std::cin >> l >> r;
  std::cout << query(1, l, r) << std::endl;
  std::cout << "修改元素下标和值: " << std::endl;
  int i, v;
  std::cin >> i >> v;
  update(1, i, v);
  std::cout << "最值区间: " << std::endl;
  std::cin >> l >> r;
  std::cout << query(1, l, r) << std::endl;
  return 0;
}
