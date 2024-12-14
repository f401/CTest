#include <iostream>
#include <queue>

struct Data 
{
	int idx, value;
	
	struct Compartor {
		bool operator() (const Data& left, const Data &right) const noexcept {
			return left.value > right.value;
		}
	};
};

int main(int argc, char *argv[])
{
	int n;
	scanf("%d", &n);
	std::priority_queue<Data, std::vector<Data>, Data::Compartor> queue;
	for (int i = 1; i <= n; ++i) {
		Data tmp;
		scanf("%d", &tmp.value);
		tmp.idx = i;
		queue.push(tmp);
	}
	double result = 0.0;
	int sum = 0, people = 0;
	while (queue.size()) {
		++people;
		const Data &data = queue.top();
		printf("%d ", data.idx);
		result += data.value * (n - people);
		sum += data.value;
		queue.pop();
	}
	printf("%.2lf", result/n);
	return 0;
}
