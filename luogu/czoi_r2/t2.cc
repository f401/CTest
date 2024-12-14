#include <bits/stdc++.h>

enum { None = 0, Oi = 1, S = 2 };
int g[1005], g2[1005][1005];
std::vector<std::tuple<int, int, int>> g3S;
struct Range {
int l, r;
Range (int l, int r): l(std::min(l, r)), r(std::max(l, r)) {
}
bool contains(int pos) const {
return l < pos && pos < r;
}
};

signed main() {
  int n, k, m, x, y;
  std::cin >> n >> k >> m >> x >> y;
  if (k == 1) {
    std::vector<int> jiaolian;
    for (int i = 1, tmp; i <= m; ++i)
      std::cin >> tmp, g[tmp] = Oi;
    for (int i = 1, tmp; i <= x; ++i)
      std::cin >> tmp, g[tmp] = S;
    for (int i = 1, tmp, ans = 0; i <= y; ++i)
      std::cin >> tmp, g[tmp] = S, jiaolian.push_back(tmp);
    for (int tmp : jiaolian) {
      int ans = 0;
      for (int j = tmp + 1; j <= n; ++j) {
        if (g[j] == Oi) {
          ++ans;
          break;
        } else if (g[j] == S)
          break;
      }
      for (int j = tmp - 1; j; --j) {
        if (g[j] == Oi) {
          ++ans;
          break;
        } else if (g[j] == S)
          break;
      }
      printf("%d ", ans);
    }
  } else if (k == 2) {
    std::vector<std::pair<int, int>> vec;
    for (int i = 1, tmpX, tmpY; i <= m; ++i)
      std::cin >> tmpX >> tmpY, g2[tmpX][tmpY] = Oi;
    for (int i = 1, tmpX, tmpY; i <= x; ++i)
      std::cin >> tmpX >> tmpY, g2[tmpX][tmpY] = S;
    for (int i = 1, tmpX, tmpY; i <= y; ++i)
      std::cin >> tmpX >> tmpY, vec.push_back({tmpX, tmpY}), g2[tmpX][tmpY] = S;
    for (auto [tmpX, tmpY] : vec) {
      int ans = 0;
      for (int i = tmpX + 1; i <= n; ++i) {
        if (g2[i][tmpY] == Oi) {
          ++ans;
          break;
        } else if (g2[i][tmpY] == S)
          break;
      }
      for (int i = tmpX - 1; i; --i) {
        if (g2[i][tmpY] == Oi) {
          ++ans;
          break;
        } else if (g2[i][tmpY] == S)
          break;
      }
      for (int i = tmpY + 1; i <= n; ++i) {
        if (g2[tmpX][i] == Oi) {
          ++ans;
          break;
        } else if (g2[tmpX][i] == S)
          break;
      }
      for (int i = tmpY - 1; i; --i) {
        if (g2[tmpX][i] == Oi) {
          ++ans;
          break;
        } else if (g2[tmpX][i] == S)
          break;
      }
      printf("%d ", ans);
    }
  } else if (k == 3) {
    std::vector<std::tuple<int, int, int>> jiaolian, oiers;
    for (int i = 1, tmpX, tmpY, z; i <= m; ++i)
      std::cin >> tmpX >> tmpY >> z, oiers.push_back({tmpX, tmpY, z}), g3S.emplace_back(tmpX, tmpY, z);
    std::sort(oiers.begin(), oiers.begin());
    for (int i = 1, tmpX, tmpY, z; i <= x; ++i)
      std::cin >> tmpX >> tmpY >> z, g3S.emplace_back(tmpX, tmpY, z);
    for (int i = 1, tmpX, tmpY, z; i <= y; ++i)
      std::cin >> tmpX >> tmpY >> z, jiaolian.push_back({tmpX, tmpY, z}),
          g3S.emplace_back(tmpX, tmpY, z);
    std::sort(g3S.begin(), g3S.begin());
    for (auto [tmpX, tmpY, tmpZ] : jiaolian) {
      int ans = 0;
      for (auto [ox, oy, oz] : oiers) {
        if (tmpX == ox && tmpY == oy) {
bool flg = true;
for (auto [sx, sy, sz]: g3S) {
Range range(tmpZ, oz);
if (tmpX == sx && tmpY == sy && range.contains(sz)) { 
flg = false;
break;
}
}
if (flg) ++ans;
        }

        if (tmpX == ox && tmpZ == oz) {
bool flg = true;
for (auto [sx, sy, sz]: g3S) {
Range range(tmpY, oy);
if (tmpX == sx && tmpZ == sz && range.contains(sy)) { 
flg = false;
break;
}
}
if (flg) ++ans;
        }
if (tmpZ == oz && tmpY == oy) {
bool flg = true;
for (auto [sx, sy, sz] : g3S) {
Range range(tmpX, ox);
if (tmpZ == sz && tmpY == sy && range.contains(sx)) {
flg = false;
break;
}
}
if (flg) ++ans;
}
      }
      printf("%d ", ans);
    }
  }

  return 0;
}
