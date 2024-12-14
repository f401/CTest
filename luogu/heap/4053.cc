#include <iostream>
#include <queue>

class Building {
public:
  Building() : Building(0, 0) {}
  Building(int need, int failedTime) : need(need), failedTime(failedTime) {}

  int get_need() const noexcept { return this->need; }
  int get_failed_time() const noexcept { return this->failedTime; }
  bool canFix(int past) const noexcept { return past + need < failedTime; }

  friend std::istream &operator>>(std::istream &input, Building &building) {
    int need, failedTime;
    input >> need >> failedTime;
    building.need = need;
    building.failedTime = failedTime;
    return input;
  }

  friend bool operator<(const Building &left, const Building &right) {
      return left.failedTime > right.failedTime;
  }

private:
  int need;
  int failedTime;
};

int main(int argc, char *argv[]) {
  int n;
  Building build;
  std::cin >> n;
  std::priority_queue<Building> src;
  std::priority_queue<int> costs;
  while (n--) {
    std::cin >> build;
    src.push(build);
  }

  long long count = 0, past = 0;
  while (src.size()) {
    const Building &b = src.top();
	past += b.get_need();
	++count;
	costs.push(b.get_need());
	if (past > b.get_failed_time()) {
		past -= costs.top();
		costs.pop();
		--count;
	}
    src.pop();
  }
  std::cout << count;
  return 0;
}
