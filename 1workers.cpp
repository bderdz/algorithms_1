#include <iostream>

struct worker {
	int C, K;	// efficiency
	int zero_index; // last not zero elem
};

int main() {
	std::ios_base::sync_with_stdio(false);
	std::cout.tie(nullptr);
	std::cin.tie(nullptr);

	int t;
	int n, d, m;	// set
	int day;
	int done_days = 0;
	long int progress = 0;
	worker* workers;

	std::cin >> t;

	for(int i = 0; i < t; i++) {
		std::cin >> n >> d >> m;
		workers = new worker[n];

		for(int j = 0; j < n; j++) {
			std::cin >> workers[j].C >> workers[j].K;

			workers[j].zero_index = 1 + workers[j].C / workers[j].K;
		}

		for(int j = 0; j < d; j++) {
			std::cin >> day;

			for(int k = 0; k < n; k++) {
				int last = workers[k].zero_index > day ? day : workers[k].zero_index;

				progress += (2 * workers[k].C - (last - 1) * workers[k].K) * last / 2;
			}

			if(progress >= m) {
				done_days++;
			}

			std::cout << progress << " ";
			progress = 0;
		}

		std::cout << "\n" << done_days << "\n";

		delete[] workers;
		done_days = 0;
	}

	return 0;
}