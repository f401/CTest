#define MAXN 100

int queue[MAXN];
int head = 0, tail = 0;
void push(int x) {
	queue[tail] = x; tail += 1;
}
void pop() {
	if (head == tail) {
		// empty
	} else {
		head++;
	}
}
int front() {
	return queue[head];
}
