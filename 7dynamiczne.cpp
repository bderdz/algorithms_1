#include <iostream>
#include <algorithm>

void count_artifacts(int **city, int **path_map, int &counter, int n) {
	int x = n - 1;
	int y = n - 1;

	while (x >= 0 && y >= 0) {
		if (city[y][x]) {
			counter++;
			city[y][x] = 0;
		}

		if (y == 0) {
			x--;
		} else if (x == 0) {
			y--;
		} else {
			if (path_map[y][x - 1] > path_map[y - 1][x]) {
				x--;
			} else {
				y--;
			}
		}
	}
}

void generate_path_map(int **city, int **path_map, int n) {
	path_map[0][0] = city[0][0];

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (i == 0 && j == 0) {
				continue;
			} else if (i == 0) {
				path_map[i][j] = path_map[i][j - 1] + city[i][j];
			} else if (j == 0) {
				path_map[i][j] = path_map[i - 1][j] + city[i][j];
			} else {
				path_map[i][j] =
						std::max(path_map[i - 1][j], path_map[i][j - 1]) + city[i][j];
			}
		}
	}
}

int main() {
	int n, a;
	int **city;
	int **path_map;
	int counter = 0;

	std::cin >> n;

	city = new int *[n];
	path_map = new int *[n];

	for (int i = 0; i < n; i++) {
		city[i] = new int[n];
		path_map[i] = new int[n];
	}

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			std::cin >> a;
			city[i][j] = a;
		}
	}

	for (int i = 0; i < 2; i++) {
		generate_path_map(city, path_map, n);
		count_artifacts(city, path_map, counter, n);
	}

	//OUTPUT
	std::cout << counter << "\n";

	//----------------
	for (int i = 0; i < n; i++) {
		delete[] city[i];
		delete[] path_map[i];
	}

	delete[] city;
	delete[] path_map;

	return 0;
}