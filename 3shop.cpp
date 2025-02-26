#include <iostream>
#include <string>

class Checkout {
private:
	struct Client {
		int service_time;
		Client *next;

		Client(unsigned short service_time) {
			this->service_time = service_time;
			this->next = nullptr;
		}
	};

	bool open;
	int num_clients;
	int waiting_time;
	Client *head;
	Client *tail;

public:
	Checkout() {
		this->open = false;
		this->head = nullptr;
		this->tail = head;
		this->num_clients = 0;
		this->waiting_time = 0;
	}

	// FOR DEBUG
	std::string print_clients() {
		std::string result;

		Client *current = head;

		while (current != nullptr) {
			result += std::to_string(current->service_time) + ",";
			current = current->next;
		}

		return result;
	}

	void push(int service_time) {
		num_clients++;
		waiting_time += service_time;

		if (head != nullptr) {
			tail->next = new Client(service_time);
			tail = tail->next;
		} else {
			head = new Client(service_time);
			tail = head;
		}
	};

	int pop() {
		if (head != nullptr) {
			Client *tmp = head;
			int service_time = tmp->service_time;
			waiting_time -= service_time;

			head = head->next;
			delete tmp;
			num_clients--;

			return service_time;
		} else {
			return 0;
		}
	};

	void next_sec(unsigned short s) {
		unsigned short remain_sec = s;

		while (remain_sec > 0 && !isEmpty()) {
			if (remain_sec >= head->service_time) {
				remain_sec = remain_sec - head->service_time;
				pop();
			} else {
				head->service_time -= remain_sec;
				this->waiting_time -= remain_sec;
				return;
			}
		}
	}

	int get_waiting_time() const {
		return this->waiting_time;
	}

	int get_num_clients() const {
		return this->num_clients;
	}

	void toggle_open() {
		this->open = !open;
	}

	bool isOpen() const {
		return this->open;
	}

	bool isEmpty() const {
		return head == nullptr;
	}

	~Checkout() {
		while (head != nullptr) {
			Client *tmp = head;
			head = tmp->next;

			delete tmp;
		}

		tail = nullptr;
	}
};

unsigned short find_best_checkout(Checkout *arr, unsigned short n) {
	int best;
	unsigned short idx = 0;

	while (!arr[idx].isOpen()) {
		idx++;
	}

	best = arr[idx].get_waiting_time();

	for (unsigned short i = idx; i < n; i++) {
		if (arr[i].isOpen()) {
			int current = arr[i].get_waiting_time();

			if (current < best) {
				best = current;
				idx = i;
			}
		}
	}

	return idx;
}

void print_result(Checkout *arr, unsigned short n) {
	for (unsigned short i = 0; i < n; i++) {
		std::cout << "K" << i << ": "
				  << (arr[i].isOpen() ? (std::to_string(arr[i].get_num_clients()) +
										 "o " +
										 std::to_string(arr[i].get_waiting_time()) +
										 "s") : "z")
				  << (i + 1 != n ? ", " : "");
	}
}

int main() {
	std::ios_base::sync_with_stdio(false);
	std::cout.tie(nullptr);
	std::cin.tie(nullptr);

	Checkout *shop;
	short t;
	unsigned short l, s, z;        // Czas symulacji; Ilosc kas; czas na skan; czas na platnosc
	char flag;        // Flaga zdarzenia
	unsigned short p, r, a;        // Czas od poprzedniego klienta; Ilosc produktow; numer kasy
	unsigned short service_time, best;

	std::cin >> t >> l >> s >> z;

	shop = new Checkout[l];

	while (t > 0) {
		std::cin >> flag;

		switch (flag) {
			case 'o':
				std::cin >> a;
				shop[a].toggle_open();
				break;
			case 'z':
				std::cin >> a;
				shop[a].toggle_open();
				shop[a].pop();

				while (!shop[a].isEmpty()) {
					best = find_best_checkout(shop, l);
					shop[best].push(shop[a].pop());
				}
				break;
			case 'k':
				std::cin >> p >> r;

				if (p > 0) {
					t -= p;

					for (unsigned short i = 0; i < l; i++) {
						if (shop[i].isOpen() && !shop[i].isEmpty()) {
							if (t < 0) {
								shop[i].next_sec(p + t);
							} else {
								shop[i].next_sec(p);
							}
						}
					}
				}

				if (t >= 0) {
					service_time = r * s + z;
					best = find_best_checkout(shop, l);
					shop[best].push(service_time);
				}
				break;
			default:
				break;
		}

		for (int i = 0; i < l; i++) {
			std::cout << i << " kasa: " << shop[i].isOpen() << " czas oczekiwania: "
					  << shop[i].get_waiting_time() << " klienci: "
					  << shop[i].print_clients() << " czas symulacji: " << t
					  << "\n";
		}

		std::cout << "----------------\n";
	}

	print_result(shop, l);

	delete[] shop;
	return 0;
}