#include <iostream>
#include <string>

struct item {
	std::string name;
	int weight;
};

void wstawianko_sort(item *arr, int n) {
	for(int i =1; i < n; i++) {
		item current = arr[i];
		int index = i;
		while(index > 0 && arr[index - 1].weight > current.weight) {
			arr[index] = arr[index - 1];
			index--;
		}

		arr[index] = current;
	}
}

void print_energy(item*arr, int n) {
	long int current_weight = 0;
	long int energy_sum = 0;

	for(int i = 0; i < n; i++) {
		energy_sum += arr[i].weight + current_weight;
		current_weight += arr[i].weight;
	}

	std::cout << energy_sum << "\n";
}

void print_items(item *arr, int n) {
	for(int i = 0; i < n; i++) {
		std::cout << arr[i].name + " ";
	}

	std::cout << "\n";
}

int main() {
	short t;
	int n;
	item* safe;

	std::cin >> t;

	for(short i = 0; i < t; i++) {
		std::cin >> n;

		safe = new item[n];

		for(int j = 0; j < n; j++) {
			std::cin >> safe[j].name >> safe[j].weight;
		}

		wstawianko_sort(safe, n);

		print_energy(safe, n);
		print_items(safe, n);

		delete[] safe;
	}

	return 0;
}