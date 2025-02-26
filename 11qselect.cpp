#include <iostream>
#include <vector>

int count_prime_dividers(int x) {
	int count = 0;

	for (int i = 2; i * i <= x; i++) {
		if (x % i == 0) {
			count++;

			while (x % i == 0) {
				x /= i;
			}
		}
	}

	if (x > 1) count++;

	return count;
}

int partition(std::vector<int> &A, std::vector<int> &B, std::vector<int> &C, std::vector<int> &D) {
	if (A.empty()) return -1;

	int pivot = A[0];

	for (int n: A) {
		if (n > pivot) {
			D.push_back(n);
		} else if (n == pivot) {
			C.push_back(n);
		} else {
			B.push_back(n);
		}
	}

	return pivot;
}


int quick_select(std::vector<int> &array, int k) {
	if (array.empty() || k >= array.size()) {
		return -1;
	}

	std::vector<int> B, C, D;

	int a = partition(array, B, C, D);

	if (k < B.size()) {
		return quick_select(B, k);
	} else if (k < B.size() + C.size()) {
		return a;
	} else {
		return quick_select(D, k - (B.size() + C.size()));
	}
}

int main() {
	std::ios_base::sync_with_stdio(false);
	std::cout.tie(nullptr);
	std::cin.tie(nullptr);

	int t;

	std::cin >> t;

	for (int i = 0; i < t; i++) {
		std::vector<int> arr;
		int n, k;

		std::cin >> n;

		for (int j = 0; j < n; j++) {
			int v;
			std::cin >> v;

			if (count_prime_dividers(v) % 2 == 0) {
				arr.push_back(v);
			}
		}

		std::cin >> k;

		int result = quick_select(arr, k);

		if (result == -1) {
			std::cout << "BRAK DANYCH\n";
		} else {
			std::cout << result << "\n";
		}
	}

	return 0;
}