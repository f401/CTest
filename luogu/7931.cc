#include <bits/stdc++.h>

struct Plan {
  int l, r;
  friend bool operator<(const Plan &l, const Plan &r) { return l.l > r.l; }
} plan1[5000000], plan2[5000000];

int n, res1[5000000], res2[5000000];

void pr(Plan *plan, int *res, int m) {
  std::priority_queue<std::pair<Plan, int>> wait;
  std::priority_queue<int, std::vector<int>, std::greater<>> empty;
  for (int i = 1; i <= n; ++i) {
    empty.push(i);
  }
  for (int i = 1; i <= m; ++i) {
    while (wait.size() && wait.top().first.r <= plan[i].l) {
      empty.push(wait.top().second);
      wait.pop();
    }
    if (empty.empty())
      continue;
    int use = empty.top();
    empty.pop();
    res[use]++;
    wait.push(std::make_pair(plan[i], use));
  }
  for (int i = 1; i <= n; ++i) {
    res[i] += res[i - 1];
  }
}

int main(int argc, char *argv[]) {
  int m1, m2;
  scanf("%d %d %d", &n, &m1, &m2);
  for (int i = 1; i <= m1; ++i)
    scanf("%d %d", &plan1[i].l, &plan1[i].r);
  for (int i = 1; i <= m2; ++i)
    scanf("%d %d", &plan2[i].l, &plan2[i].r);
  std::sort(plan1 + 1, plan1 + 1 + m1,
            [](const Plan &l, const Plan &r) { return l.l < r.l; });
  std::sort(plan2 + 1, plan2 + 1 + m2,
            [](const Plan &l, const Plan &r) { return l.l < r.l; });

  pr(plan1, res1, m1);
  pr(plan2, res2, m2);

  int ans = 0;
  for (int i = 0; i <= n; ++i) {
    ans = std::max(ans, res1[i] + res2[n - i]);
  }
  printf("%d", ans);
  return 0;
}
