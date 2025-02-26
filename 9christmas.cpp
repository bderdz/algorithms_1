#include <iostream>
#include <cmath>
#include <iomanip>

void find_min_max(double *arr, int n, double &min, double &max) {
	min = max = arr[0];

	for (int i = 0; i < n; i++) {
		if (arr[i] > max) {
			max = arr[i];
		}

		if (arr[i] < min) {
			min = arr[i];
		}
	}
}

double find_min(double a, double b) {
	return a > b ? b : a;
}

double find_max(double a, double b) {
	return a > b ? a : b;
}

void bucket_sorcik(double *source, int n, double max, double min, double *min_bucket, double *max_bucket) {
	double range = (max - min) / (n - 1);

	for (int i = 0; i < n; i++) {
		if (source[i] == max || source[i] == min) continue;

		int idx = std::floor(source[i] - min) / range;

		max_bucket[idx] = find_max(max_bucket[idx], source[i]);
		min_bucket[idx] = find_min(min_bucket[idx], source[i]);
	}
}

void help_elves(double *docs, int n) {
	if (n > 2) {
		double max;
		double min;

		find_min_max(docs, n, min, max);

		// Bucket alloc
		double min_bucket[n - 1];
		double max_bucket[n - 1];

		for (int i = 0; i < n - 1; i++) {
			min_bucket[i] = max;
			max_bucket[i] = min;
		}

		//-----------------------------

		bucket_sorcik(docs, n, max, min, min_bucket, max_bucket);

		double longest = 0;
		double prev_max = min;

		for (int i = 0; i < n - 1; i++) {
			if (min_bucket[i] == max) continue;

			longest = find_max(longest, min_bucket[i] - prev_max);
			prev_max = max_bucket[i];
		}

		longest = find_max(longest, max - prev_max);

		std::cout << std::fixed << std::setprecision(4) << longest << "\n";


	} else {
		std::cout << std::fixed << std::setprecision(4) << std::abs(docs[0] - docs[1]) << "\n";
	}
}


int main() {
	std::ios_base::sync_with_stdio(false);
	std::cout.tie(nullptr);
	std::cin.tie(nullptr);

	int n;
	double *docs;

	std::cin >> n;

	docs = new double[n];

	for (int i = 0; i < n; i++) {
		std::cin >> docs[i];
	}

	help_elves(docs, n);

	delete[] docs;
	return 0;
}