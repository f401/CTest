#include <bits/stdc++.h>
using namespace std;
const int dx[] = {0,0,1,-1};
const int dy[] = {1,-1,0,0};
struct node
{
    int left, right;
}q[505], Q[505];
typedef pair<int,int> P;
queue<P> que;
int n,m, book[505][505], mp[505][505];
void bfs(int start)
{
    while(que.size()) que.pop();
    que.push(P(1, start));
    book[1][start] = start;
    while(que.size()) {
        P p = que.front(); que.pop();
        int x = p.first, y = p.second;
        for(int i = 0; i < 4; i++) {
            int tx = x + dx[i], ty = y + dy[i];
            if(tx >= 1 && ty >= 1 && tx <= n && ty <= m && !book[tx][ty] && mp[tx][ty] < mp[x][y]) {
                book[tx][ty] = start;   /// 标记被第一行哪一个点覆盖的
                que.push(P(tx,ty));
            }
        }
    }
}
int main()
{
	std::cin >> n >> m;
    for(int i = 1; i <= n; i++) for(int j = 1; j <= m; j++) std::cin >> (mp[i][j]);
    for(int i = 1; i <= m; i++) bfs(i);   /// 对第一行跑一边BFS
    int flag = 0;
    for(int i = 1; i <= m; i++) if(!book[n][i]) flag++;    /// 如果没有被标记 输出数量
    if(flag) { printf("0\n%d\n",flag); return 0; }
    int k=0;
    for(int i = 1; i <= m; i++) {    /// 求出第一行的每一个点能在最后一行覆盖的左右端点
        int t = 1;
        memset(book,0,sizeof(book));
        bfs(i);
        for(int j = 1; j <= m; j++) {
            if(book[n][j] != i) t++;
            else break;
        }
        if(t == m + 1) continue;
        q[++k].left = t;
        q[k].right = t - 1;
        for(int j = 1; j <= m; j++) if(book[n][j] == i) q[k].right++;
		printf("Area %d %d\n", q[k].left, q[k].right);
    }
	printf("Found k %d\n", k);
    int s = 1,t = m,i = 1,num = 0;   /// 贪心求最小线段区间覆盖
    while(i <= m && s <= t) {
        int last = -1;
        while(i <= m && q[i].left <= s) last = max(last,q[i].right), i++;
        if(last < s) break;
        num++;
        s = last + 1;
    }
    printf("1\n%d\n",num);
    return 0;
}
