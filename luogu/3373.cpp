#include <iostream>
using data_t = long long;
using idx_t = int;
#define LC(K) (K << 1)
#define RC(K) (K << 1 | 1)

struct Tags {
  data_t add, mul;
  Tags() : add(0), mul(1) {}

  inline void resetTag() noexcept {
    this->add = 0;
    this->mul = 1;
  }

  void operator+=(const Tags &right) {
    this->add += right.add;
    this->mul *= right.mul;
  }
};
data_t srcs[100004];

struct SegTree {
  idx_t left, right;
  data_t value;
  Tags tag;

  inline idx_t childCount() const noexcept { return right - left + 1; }

  inline void resetTag() noexcept { this->tag.resetTag(); }
} tree[100004];

void build(idx_t root, idx_t l, idx_t r) {
  tree[root].left = l, tree[root].right = r;
  if (l == r) {
    tree[root].value = srcs[l];
    return;
  }
  idx_t mid = (l + r) >> 1;
  build(LC(root), l, mid);
  build(RC(root), mid + 1, r);
  tree[root].value = tree[LC(root)].value + tree[RC(root)].value;
}

void spread(idx_t root) {
  if (tree[root].tag.add != 0 || tree[root].tag.mul != 1) {
    tree[LC(root)].value = tree[root].tag.mul * tree[LC(root)].value +
                           tree[LC(root)].childCount() * tree[root].tag.add;
    tree[RC(root)].value = tree[root].tag.mul * tree[RC(root)].value +
                           tree[RC(root)].childCount() * tree[root].tag.add;

    tree[LC(root)].tag += tree[root].tag;
    tree[RC(root)].tag += tree[root].tag;
    tree[root].resetTag();
  }
}

void add(idx_t root, idx_t l, idx_t r, data_t value) {
  if (tree[root].left <= l && tree[root].right >= r) {
    tree[root].tag.add += value;
    tree[root].value += value * tree[root].childCount();
    return;
  }
  spread(root);
  idx_t mid = (tree[root].left + tree[root].right) >> 1;
  if (l <= mid) {
    add(LC(root), l, r, value);
  }

  if (r > mid) {
    add(RC(root), l, r, value);
  }
  tree[root].value = tree[LC(root)].value + tree[RC(root)].value;
}

void mul(idx_t root, idx_t l, idx_t r, data_t value) {
  if (tree[root].left <= l && tree[root].right >= r) {
    tree[root].tag.add *= value;
	tree[root].tag.mul *= value;
    tree[root].value *= value;
    return;
  }
  spread(root);
  idx_t mid = (tree[root].left + tree[root].right) >> 1;
  if (l <= mid) {
    mul(LC(root), l, r, value);
  }

  if (r > mid) {
    mul(RC(root), l, r, value);
  }
  tree[root].value = tree[LC(root)].value + tree[RC(root)].value;
}

int main(int argc, char *argv[]) {
  std::ios::sync_with_stdio(false), std::cin.tie(nullptr),
      std::cout.tie(nullptr);
  int n, q, m;
  std::cin >> n >> q >> m;
  build(1, 1, n);

  return 0;
}
