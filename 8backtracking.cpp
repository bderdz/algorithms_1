#include <iostream>

int *tmp_path;
int *best_path;

void backtrack_garden(int **garden, int n, bool *used_rows, int &best_cost, int total_cost = 0, int col = 0) {
	for (int i = 0; i < n; i++) {
		if (!used_rows[i] && total_cost + garden[i][col] < best_cost) {
			total_cost += garden[i][col];
			used_rows[i] = true;
			tmp_path[col] = i;

			if (col + 1 < n) {
				backtrack_garden(garden, n, used_rows, best_cost, total_cost, col + 1);
			} else {
				if (total_cost < best_cost) {
					// najlepsza sciezka
					for (int j = 0; j < n; j++) {
						best_path[j] = tmp_path[j];
					}

					best_cost = total_cost;
				}
			}

			// Wracam
			used_rows[i] = false;
			total_cost -= garden[i][col];
		}
	}
}

int main() {
	int n;
	int **garden;
	bool *used_rows;
	int best_cost = 1001;

	std::cin >> n;

	// INIT
	tmp_path = new int[n];
	best_path = new int[n];
	garden = new int *[n];

	for (int i = 0; i < n; i++) {
		garden[i] = new int[n];
	}

	used_rows = new bool[n]();

	// INPUT
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			std::cin >> garden[i][j];
		}
	}

	// BACKTRACKING
	backtrack_garden(garden, n, used_rows, best_cost);

	// Printing best path
	for (int i = 0; i < n; i++) {
		std::cout << best_path[i] << " ";
	}

	// ---------------------------
	for (int i = 0; i < n; i++) {
		delete[] garden[i];
	}

	delete[] garden;
	delete[] used_rows;
	delete[] tmp_path;
	delete[] best_path;
	return 0;
}