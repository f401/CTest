#include <bits/stdc++.h>
using namespace std;
int n, m, x, y, k, op;
const int len = 1e5 + 9, inf = 0x3f3f3f3f;
#define lc k << 1 // lc=k*2(k时时更新)
#define rc k << 1 | 1
struct Node {
  int l, r;
  long long v, lz;
} tree[len * 4];
int a[len];
void pushdown(int k) { // 向下传递懒标记
  tree[lc].lz += tree[k].lz;
  tree[lc].v += tree[k].lz * (tree[lc].r - tree[lc].l + 1);
  tree[rc].lz += tree[k].lz;
  tree[rc].v += tree[k].lz * (tree[rc].r - tree[rc].l + 1);
  tree[k].lz = 0;
}
void build(int k, int l, int r) { // k存储下标，区间（l,r）
  tree[k].l = l;
  tree[k].r = r;
  tree[k].lz = 0; // 初始化操作
  if (l == r) {   // 叶子节点
    scanf("%d", &tree[k].v);
    return;
  }
  int mid = (l + r) / 2;
  build(lc, l, mid);                   // 递归创建左子树
  build(rc, mid + 1, r);               // 递归创建右子树
  tree[k].v = tree[lc].v + tree[rc].v; // 更新节点的最值等于左右孩子的最值
}
void update(int k, int l, int r, long long val) { // 将区间[l..r]修改更新为v
  if (tree[k].l == l && tree[k].r == r) {
    tree[k].v += val * (tree[k].r - tree[k].l + 1);
    tree[k].lz += val;
    return;
  }
  if (tree[k].lz != 0)
    pushdown(k); // 懒标记下移
  int mid;
  mid = (tree[k].l + tree[k].r) >> 1; // 划分点
  if (r <= mid)
    update(lc, l, r, val); // 到左子树更新
  else if (l > mid)
    update(rc, l, r, val); // 到右子树更新
  else
    update(lc, l, mid, val), update(rc, mid + 1, r, val);
  tree[k].v = tree[lc].v + tree[rc].v;
}

long long query(int k, int l, int r) { // 求区间[l..r]的最值
  if (tree[k].l == l && tree[k].r == r)
    return tree[k].v; // 找到该区间
  if (tree[k].lz != 0)
    pushdown(k);                          // 懒标记下移
  int mid = (tree[k].l + tree[k].r) >> 1; // 划分点
  if (r <= mid) {                         // 左右两边都有可能
    return query(lc, l, r);
  } else if (l > mid) {
    return query(rc, l, r);
  } else
    return query(lc, l, mid) + query(rc, mid + 1, r);
}
int main() {
  scanf("%d%d", &n, &m);
  build(1, 1, n);
  while (m--) {
    scanf("%d", &op);
    if (op == 1) {
      scanf("%d%d%d", &x, &y, &k);
      update(1, x, y, k);
    } else {
      scanf("%d%d", &x, &y);
      printf("%lld\n", query(1, x, y));
    }
  }
  return 0;
}
