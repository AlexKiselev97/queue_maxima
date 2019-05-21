#include <iostream>
#include <algorithm>
#include <vector>
#include <stack>

using namespace std;

class stack_maxima
{
	stack<pair<int, int>> s;
public:
	void push(int x) {
		int maxima = s.empty() ? x : max(x, s.top().second);
		s.push(make_pair(x, maxima));
	}
	void pop() { s.pop(); }
	int top() const { return s.top().first; }
	int get_maxima() const { return s.top().second; }
	bool empty() const { return s.empty(); }
};

class queue_maxima
{
	stack_maxima s1, s2;
public:
	void push(int x) { s1.push(x); }
	int pop() {
		if (s2.empty())
			while (!s1.empty()) {
				s2.push(s1.top());
				s1.pop();
			}
		int x = s2.top();
		s2.pop();
		return x;
	}
	int get_maxima() const {
		if (s1.empty() || s2.empty())
			return s1.empty() ? s2.get_maxima() : s1.get_maxima();
		else
			return max(s1.get_maxima(), s2.get_maxima());
	}
	bool empty() const { return s1.empty() && s2.empty(); }
};

int main()
{
	/* example program - Sliding Window Maximum for O(n)
	input:
		enter n - length of array
		enter array
		enter m - length of sliding window
	output:
		n - m + 1 maximums
	*/
	int n;
	cin >> n;
	vector<int> v(n);
	for (int i = 0; i < n; ++i)
		cin >> v[i];
	int m;
	cin >> m;

	queue_maxima qm;
	for (int i = 0; i < m; ++i)
		qm.push(v[i]);
	for (int i = m; i < n; ++i)
	{
		cout << qm.get_maxima() << ' ';
		qm.pop();
		qm.push(v[i]);
	}
	cout << qm.get_maxima() << endl;
	return 0;
}