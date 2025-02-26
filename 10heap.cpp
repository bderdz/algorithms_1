#include <iostream>

// Left 2 * i + 1
// Right 2 * i + 2

class Heap {
protected:
	int *data;
	unsigned int max_size;
	int i;

	void swap(int a_idx, int b_idx) {
		int tmp = data[a_idx];

		data[a_idx] = data[b_idx];
		data[b_idx] = tmp;
	}

	virtual void heapify_insert(int idx) = 0;

	virtual void heapify_remove(int idx) = 0;

public:
	Heap(unsigned int max_size) {
		this->max_size = max_size;
		this->data = new int[max_size];
		this->i = 0;
	}

	void insert(int value) {
		if (i < max_size) {
			data[i] = value;

			heapify_insert(i);
			i++;
		}
	}

	int remove() {
		int tmp = data[0];
		data[0] = data[i - 1];
		i--;

		heapify_remove(0);

		return tmp;
	}

	int get_size() {
		return this->i;
	}

	void print_heap() {
		for (int j = 0; j < i; j++) {
			std::cout << data[j] << " ";
		}

		std::cout << "\n";
	}

	virtual ~Heap() {
		delete[] this->data;
	}
};

class HeapMax : public Heap {
protected:
	void heapify_insert(int idx) override {
		int parent = (idx - 1) / 2;

		if (parent >= 0 && data[idx] > data[parent]) {
			swap(idx, parent);
			heapify_insert(parent);
		}
	}

	void heapify_remove(int idx) override {
		int left = 2 * idx + 1;
		int right = 2 * idx + 2;
		int largest = idx;

		if (left < this->i && this->data[left] > this->data[largest]) {
			largest = left;
		}

		if (right < this->i && this->data[right] > this->data[largest]) {
			largest = right;
		}

		if (largest != idx) {
			swap(idx, largest);

			heapify_remove(largest);
		}
	}

public:
	using Heap::Heap;

	void modify_root(int value) {
		if (value + data[0] >= 0) {
			this->data[0] += value;

			if (this->data[0] < this->data[1] || this->data[0] < this->data[2]) {
				heapify_remove(0);
			}
		}
	};
};

class HeapMin : public Heap {
protected:
	void heapify_insert(int idx) override {
		int parent = (idx - 1) / 2;

		if (parent >= 0 && data[idx] < data[parent]) {
			swap(idx, parent);
			heapify_insert(parent);
		}
	}

	void heapify_remove(int idx) override {
		int left = 2 * idx + 1;
		int right = 2 * idx + 2;
		int smallest = idx;

		if (left < this->i && this->data[left] < this->data[smallest]) {
			smallest = left;
		}

		if (right < this->i && this->data[right] < this->data[smallest]) {
			smallest = right;
		}

		if (smallest != idx) {
			swap(idx, smallest);

			heapify_remove(smallest);
		}
	}

public:
	using Heap::Heap;
};

int main() {
	std::ios_base::sync_with_stdio(false);
	std::cout.tie(nullptr);
	std::cin.tie(nullptr);

	unsigned int n;    // n-sailors
	unsigned int o;    // n-operations
	char action;
	int p; // price
	int t; // % tax
	int x; // change action value

	std::cin >> n;

	for (int i = 0; i < n; i++) {
		std::cin >> o;

		HeapMax *prices = new HeapMax(o);
		HeapMin *taxes = new HeapMin(o);

		for (int j = 0; j < o; j++) {
			std::cin >> action;

			switch (action) {
				case 'a':
					std::cin >> p >> t;
					prices->insert(p);
					taxes->insert(t);
					//					prices->print_heap();
					//					taxes->print_heap();
					break;
				case 'p':
					std::cin >> x;
					prices->modify_root(x);
					//					prices->print_heap();
					break;
				default:
					break;
			}
		}

		// Count the tax
		int tax = 0;
		int heap_size = prices->get_size();

		for (int j = 0; j < heap_size; j++) {
			int a = prices->remove();
			int b = taxes->remove();
			tax += a * b;
		}

		std::cout << tax << "\n";

		delete prices;
		delete taxes;
	}

	return 0;
}