#include <iostream>
#include <queue>
#include <stack>
#include <algorithm>

struct Point {
	bool status;
	int value;

	Point(int value, bool status) : value(value), status(status) {}
};

bool dfs(std::vector<int> *graph, std::vector<int> &state, int idx) {
	state[idx] = 1;

	for (int neighbor: graph[idx]) {
		if (state[neighbor] == 1) {
			return true;
		} else if (state[neighbor] == 0) {
			return dfs(graph, state, neighbor);
		}
	}

	state[idx] = 2;
	return false;
}

std::stack<int> bfs(std::vector<int> *graph, int start, int n) {
	std::queue<Point> queue;
	std::vector<bool> visited_good(n, false), visited_bad(n, false);
	std::vector<int> previous_good(n, -1), previous_bad(n, -1);

	visited_good[start] = true;
	queue.push({start, true});

	while (!queue.empty()) {
		Point current = queue.front();
		queue.pop();

		for (int neighbor: graph[current.value]) {
			if (current.status) {
				if (!visited_bad[neighbor]) {
					queue.push({neighbor, false});
					previous_bad[neighbor] = current.value;
					visited_bad[neighbor] = true;
				}
			} else {
				if (!visited_good[neighbor]) {
					queue.push({neighbor, true});
					previous_good[neighbor] = current.value;
					visited_good[neighbor] = true;
				}
			}
		}

	}

	std::stack<int> path;
	int length = -1;

	for (int i = 0; i < n; i++) {
		if (graph[i].empty() && visited_good[i]) {
			std::stack<int> tmp_path;
			int idx = i;
			bool status = true;

			while (idx != -1) {
				tmp_path.push(idx);

				if (status) {
					idx = previous_good[idx];
				} else {
					idx = previous_bad[idx];
				}

				status = !status;
			}

			if (length == -1 || length > tmp_path.size()) {
				path = tmp_path;
				length = tmp_path.size();
			}
		}
	}

	return path;
}

void back_to_the_future(std::vector<int> *graph, int start, int n) {
	std::stack<int> path = bfs(graph, start, n);

	if (!path.empty()) {
		std::cout << "TAK\n";
		while (!path.empty()) {
			std::cout << path.top() << " ";
			path.pop();
		}
		std::cout << "\n";
		return;
	}

	std::vector<int> state = std::vector<int>(n, 0);
	if (dfs(graph, state, start)) {
		std::cout << "PETLA\n";
		return;
	}

	std::cout << "NIE\n";
}

int main() {
	std::ios_base::sync_with_stdio(false);
	std::cout.tie(nullptr);
	std::cin.tie(nullptr);

	std::vector<int> *graph;
	short t;
	int n, m, start;
	int x, y;

	std::cin >> t;

	for (int i = 0; i < t; i++) {
		std::cin >> n >> m >> start;

		graph = new std::vector<int>[n];

		for (int j = 0; j < m; j++) {
			std::cin >> x >> y;

			graph[x].push_back(y);
		}

		for (int j = 0; j < n; j++) {
			if (!graph[j].empty()) {
				std::sort(graph[j].begin(), graph[j].end());
			}
		}

		back_to_the_future(graph, start, n);

		delete[] graph;
	}

	return 0;
}