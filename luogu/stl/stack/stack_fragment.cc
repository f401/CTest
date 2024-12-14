#include <bits/stdc++.h>

#define MAXN 100
int stack[MAXN];
int p = 0;

void push(int x) {
	if (p >= MAXN) {
		// Stack Over flow
	} else {
		stack[p] = x; ++p;
	}
}

void pop() {
	if (p == 0) {
		// Stack is empty
	} else {
		p--;
	}
}

int top() {
	if (p == 0) {
		// Stack is empty
		return -1;
	} else {
		return stack[p - 1];
	}
}
