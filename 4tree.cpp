#include <iostream>

class MeasurementsTree {
private:
	struct Node {
		int repeats;
		unsigned int f, l;
		Node *left;
		Node *right;

		Node(unsigned int f, unsigned int l) {
			left = right = nullptr;
			this->f = f;
			this->l = l;
			this->repeats = 1;
		}
	};

	Node *koreshok;
public:
	MeasurementsTree() {
		koreshok = nullptr;
	}

	void add(unsigned int f, unsigned int l) {
		if (koreshok == nullptr) {
			koreshok = new Node(f, l);
			return;
		}

		Node *current = koreshok;

		while (current != nullptr) {
			if (f == current->f && l == current->l) {
				current->repeats++;
				break;
			}

			if (f < current->f || (f == current->f && l < current->l)) {
				if (current->left == nullptr) {
					current->left = new Node(f, l);
					break;
				}

				current = current->left;
			} else {
				if (current->right == nullptr) {
					current->right = new Node(f, l);
					break;
				}

				current = current->right;
			}
		}
	}

	void print_nodes(Node *node) {
		if (node == nullptr) return;

		print_nodes(node->left);

		for (int i = 0; i < node->repeats; i++) {
			std::cout << "(" << node->f << "," << node->l << ") ";
		}

		print_nodes(node->right);
	}

	void CutTree(Node *node) {
		if (node != nullptr) {
			CutTree(node->right);
			CutTree(node->left);
			delete node;
		}
	}

	Node *get_koreshok() {
		return koreshok;
	}

	~MeasurementsTree() {
		CutTree(koreshok);
	}
};


class YearTree {
public:
	struct Node {
		unsigned int year;
		MeasurementsTree *data;
		Node *left;
		Node *right;

		Node(unsigned int year) {
			left = right = nullptr;
			this->year = year;
			this->data = new MeasurementsTree();
		}

		~Node() {
			delete data;
		}
	};

	Node *koreshok;

	YearTree() {
		koreshok = nullptr;
	}

	Node *add(unsigned int year) {
		if (koreshok == nullptr) {
			koreshok = new Node(year);

			return koreshok;
		}

		Node *current = koreshok;

		while (current != nullptr) {
			if (year == current->year) {
				return current;
			}

			if (year < current->year) {
				if (current->left == nullptr) {
					current->left = new Node(year);
					return current->left;
				}
				current = current->left;
			} else {
				if (current->right == nullptr) {
					current->right = new Node(year);
					return current->right;
				}
				current = current->right;
			}
		}

		return nullptr;
	}

	void print_nodes(Node *node) {
		if (node == nullptr) return;

		print_nodes(node->left);

		std::cout << node->year << ": ";
		node->data->print_nodes(node->data->get_koreshok());
		std::cout << "\n";

		print_nodes(node->right);

	}

	void CutTree(Node *node) {
		if (node != nullptr) {
			CutTree(node->right);
			CutTree(node->left);
			delete node;
		}
	}

	Node *get_koreshok() {
		return koreshok;
	}

	~YearTree() {
		CutTree(koreshok);
	}
};

int main() {
	std::ios_base::sync_with_stdio(false);
	std::cout.tie(nullptr);
	std::cin.tie(nullptr);

	YearTree *years = new YearTree();
	int n;
	unsigned int y, f, l;    //	rok, częstotliwość, długość
	float sound_speed;
	bool engine_start = true;
	bool valid_sound = false;

	std::cin >> n;

	for (int i = 0; i < n; i++) {
		std::cin >> y >> f >> l;

		if (f >= 20 && f <= 20000) {
			sound_speed = f * (l / 100.0);

			if (sound_speed >= 313.0 && sound_speed <= 350.0) {
				valid_sound = true;

				YearTree::Node *current = years->add(y);
				current->data->add(f, l);

				if (f < 275 || f > 325) {
					engine_start = false;
				}
			}
		}
	}

	if (!valid_sound) {
		engine_start = false;
	}

	// OUTPUT
	years->print_nodes(years->get_koreshok());
	std::cout << (engine_start ? "TAK" : "NIE") << "\n";

	delete years;
	return 0;
}
