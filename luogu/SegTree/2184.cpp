#include <bits/stdc++.h>
#define LC(k) (k << 1)
#define RC(k) (k << 1 | 1)

class SegementTree {
public:
  struct {
    int l, r, value;
  } tree[50000];
  SegementTree() {
	  memset(this, 0, sizeof(SegementTree));
  }

  void build(int k, int l, int r) {
    tree[k].l = l;
    tree[k].r = r;
    if (l == r) {
      return;
    }
    int mid = (l + r) >> 1;
    build(LC(k), l, mid);
    build(RC(k), mid + 1, r);
  }

  void add(int k, int l) {
    if (tree[k].l == tree[k].r) {
	  tree[k].value++;
	  return;
    }
	if (l <= ((tree[k].r + tree[k].l) >> 1))
		add(LC(k), l);
	else
		add(RC(k), l);
    tree[k].value = tree[LC(k)].value + tree[RC(k)].value;
  }

  int qry(int k, int l, int r) {
	if (tree[k].l > r || tree[k].r < l) return 0;
    if (l <= tree[k].l && tree[k].r <= r) {
      return tree[k].value;
    }
    return qry(LC(k), l, r) + qry(RC(k), l, r);
  }
};

int main(int argc, char *argv[]) {
  int n, m;
  scanf("%d %d", &n, &m);
  SegementTree start, end;
  start.build(1, 1, n);
  end.build(1, 1, n);
  while (m--) {
    int op, l, r;
    scanf("%d %d %d", &op, &l, &r);
    if (op == 1) {
		start.add(1, l);
		end.add(1, r);
    } else {
      printf("%d\n", start.qry(1, 1, r) - end.qry(1, 1, l - 1));
    }
  }
  return 0;
}
