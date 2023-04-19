#include <iostream>
#include <vector>
#include <algorithm>
#include <time.h>

using namespace std;

class Set {
	struct List {
		int data;
		List* left;
		List* right;
		List(int data, List* left, List* right) : data(data), left(left), right(right) {};
	};

	List* root;

	List* _copying(List* copy) {
		if (!copy) {
			return nullptr;
		}
		List* root_copy = new List(copy->data, nullptr, nullptr);
		root_copy->left = _copying(copy->left);
		root_copy->right = _copying(copy->right);
		return root_copy;
	}

	static void to_vector(vector<int>& value, const List* root) {
		if (!root) {
			return;
		}
		to_vector(value, root->left);
		value.push_back(root->data);
		to_vector(value, root->right);
	}

	void print_list(const List* root) {
		if (!root) {
			return;
		}
		print_list(root->left);
		cout << root->data << " ";
		print_list(root->right);
	}

	void free_tree(List* root) {
		if (!root) {
			return;
		}
		if (root->left) {
			free_tree(root->left);
		}
		if (root->right) {
			free_tree(root->right);
		}
		root = nullptr;
	}

	bool _contains(int key, List* root) {
		if (!root) {
			return false;
		}
		if (key == root->data) {
			return true;
		}
		if (key < root->data) {
			return _contains(key, root->left);
		}
		if (key > root->data) {
			return _contains(key, root->right);
		}

	}

	List* _insert(int key, List* root) {
		if (!root) {
			return new List(key, nullptr, nullptr);
		}
		if (key < root->data) {
			root->left = _insert(key, root->left);
		}
		if (key > root->data) {
			root->right = _insert(key, root->right);
		}
		return root;
	}

	List* min(List* root) {
		if (!root->left) {
			return root;
		}
		return min(root->left);
	}

	List* _erase(List* root, int key) {
		if (root == nullptr) {
			return root;
		}
		else if (key < root->data) {
			root->left = _erase(root->left, key);
		}
		else if (key > root->data) {
			root->right = _erase(root->right, key);
		}
		else {
			if (root->left == nullptr && root->right == nullptr) {
				delete root;
				root = nullptr;
			}
			else if (root->left == nullptr) {
				struct List* temp = root;
				root = root->right;
				delete temp;
			}
			else if (root->right == nullptr) {
				struct List* temp = root;
				root = root->left;
				delete temp;
			}
			else {
				struct List* temp = min(root->right);
				root->data = temp->data;
				root->right = _erase(root->right, temp->data);
			}
		}
		return root;
	}

public:
	Set() {
		root = nullptr;
	}
	~Set() {
		if (root) {
			free_tree(root);
			delete root;
		}
	}
	Set& operator= (const Set& copy) {
		if (!copy.root) {
			free_tree(root);
			delete root;
			return *this;
		}
		else {
			if (!root) {
				root = _copying(copy.root);
			}
			else {
				free_tree(root);
				delete root;
				root = _copying(copy.root);
			}
			return *this;
		}
	}

	void tree_print() {
		print_list(root);
	}

	bool insert(int key) {
		if (!_contains(key, root)) {
			root = _insert(key, root);
			return true;
		}
		return false;
	}

	bool contains(int key) {
		return _contains(key, root);
	}

	bool erase(int key) {
		if (_contains(key, root)) {
			_erase(root, key);
			return true;
		}
		return false;
	}

	vector<int> to_vector() const {
		vector<int> tmp;
		to_vector(tmp, root);
		return tmp;
	}

	void clear() {
		free_tree(root);
	}
};

vector<int> task(const vector<int>& value) {
	Set temp;
	vector<int> tmp;
	for (auto i : value) {
		if (!temp.insert(i)) {
			tmp.push_back(i);
		}
	}
	for (auto i : tmp) {
		temp.erase(i);
	}
	return temp.to_vector();
}

size_t lcg() {
	static size_t x = 0;
	x = (1021 * x + 24631) % 116640;
	return x;
}

double avg(const double* ar) {
	double sum = 0;
	for (size_t i = 0; i < 100; ++i) {
		sum += ar[i];
	}
	return sum / 100;
}

double avg1000(const double* ar) {
	double sum = 0;
	for (size_t i = 0; i < 1000; ++i) {
		sum += ar[i];
	}
	return sum / 1000;
}

int main() {
	vector<int> f_vector = { 3,1,4,5,3,6,2,7,4 };
	Set time_test_tree_1000, time_test_tree_10000, time_test_tree_100000;
	vector<int> fill_test1000, fill_test10000, fill_test100000;
	double fill_vattempts_1000[100], fill_vattempts_10000[100], fill_vattempts_100000[100];
	double fillattempts_1000[100], fillattempts_10000[100], fillattempts_100000[100];

	while (true) {

		int i;
		cout << "1. Check the list" << endl;
		cout << "2. Processing of the vector<int> container" << endl;
		cout << "3. Check the tests" << endl;
		cout << "4. Exit" << endl;
		cin >> i;
		switch (i) {
		case 1: {

			Set proverka_1;
			Set proverka_2;
			proverka_1.insert(21);
			proverka_1.insert(9);
			proverka_1.insert(3);
			proverka_1.insert(1);
			proverka_1.insert(14);
			proverka_1.insert(13);
			proverka_1.insert(11);
			proverka_1.insert(16);
			proverka_1.insert(2);
			cout << "Source list: ";
			proverka_1.tree_print();
			cout << endl;
			proverka_2 = proverka_1;
			cout << "The values of the first list were assigned to the second. Result: ";
			proverka_2.tree_print();
			cout << endl;
			cout << "Deleting a nonexistent node.Result: ";
			proverka_2.erase(29);
			proverka_2.tree_print();
			cout << endl;
			proverka_2.erase(11);
			cout << "Node 11 has been deleted. Result: ";
			proverka_2.tree_print();
			cout << endl;
			break;
		}
		case 2: {
			cout << "contents of the container: ";
			for (auto i : f_vector) {
				cout << i << " ";
			}
			cout << endl;
			cout << "Container after processing: ";
			vector<int> s_vector = task(f_vector);
			for (auto i : s_vector) {
				cout << i << " ";
			}
			cout << endl;
			break;
		}
		case 3: {
			//ÇÀÏÎËÍÅÍÈÅ ÄÅÐÅÂÀ ÍÀ 1000

			for (size_t i = 0; i < 100; ++i) {
				int counter = 0;

				clock_t begin = clock();
				while (counter != 1000) {
					time_test_tree_1000.insert(lcg());
					++counter;
				}
				clock_t end = clock();

				if (i != 99) {
					time_test_tree_1000.clear();
				}
				fillattempts_1000[i] = double(end - begin) / double(CLOCKS_PER_SEC);
			}
			cout << "Average time to fill tree with 1000 elements: " << avg(fillattempts_1000) << endl;
			cout << endl;

			//ÇÀÏÎËÍÅÍÈÅ ÄÅÐÅÂÀ ÍÀ 10000
			for (size_t i = 0; i < 100; ++i) {
				int counter = 0;

				clock_t begin = clock();
				while (counter != 10000) {
					time_test_tree_10000.insert(lcg());
					++counter;
				}
				clock_t end = clock();

				if (i != 99) {
					time_test_tree_10000.clear();
				}
				fillattempts_10000[i] = double(end - begin) / double(CLOCKS_PER_SEC);
			}
			cout << "Average time to fill tree with 10000 elements: " << avg(fillattempts_10000) << endl;
			cout << endl;

			//ÇÀÏÎËÍÅÍÈÅ ÄÅÐÅÂÀ ÍÀ 100000
			for (size_t i = 0; i < 100; ++i) {
				int counter = 0;

				clock_t begin = clock();
				while (counter != 100000) {
					time_test_tree_100000.insert(lcg());
					++counter;
				}
				clock_t end = clock();

				if (i != 99) {
					time_test_tree_100000.clear();
				}
				fillattempts_100000[i] = double(end - begin) / double(CLOCKS_PER_SEC);
			}
			cout << "Average time to fill tree with 100000 elements: " << avg(fillattempts_100000) << endl;
			cout << endl;

			//ÇÀÏÎËÍÅÍÈÅ ÊÎÍÒÅÉÍÅÐÀ ÍÀ 1000
			for (size_t i = 0; i < 100; ++i) {
				int counter = 0;

				clock_t begin = clock();
				while (counter != 1000) {
					fill_test1000.push_back(lcg());
					++counter;
				}
				clock_t end = clock();

				if (i != 99) {
					fill_test1000.clear();
				}
				fill_vattempts_1000[i] = double(end - begin) / double(CLOCKS_PER_SEC);
			}
			cout << "Average time to fill vector with 1000 elements: " << avg(fill_vattempts_1000) << endl;
			cout << endl;

			//ÇÀÏÎËÍÅÍÈÅ ÊÎÍÒÅÉÍÅÐÀ ÍÀ 10000
			for (size_t i = 0; i < 100; ++i) {
				int counter = 0;

				clock_t begin = clock();
				while (counter != 10000) {
					fill_test10000.push_back(lcg());
					++counter;
				}
				clock_t end = clock();

				if (i != 99) {
					fill_test10000.clear();
				}
				fill_vattempts_10000[i] = double(end - begin) / double(CLOCKS_PER_SEC);
			}
			cout << "Average time to fill vector with 10000 elements: " << avg(fill_vattempts_10000) << endl;
			cout << endl;

			//ÇÀÏÎËÍÅÍÈÅ ÊÎÍÒÅÉÍÅÐÀ ÍÀ 100000
			for (size_t i = 0; i < 100; ++i) {
				int counter = 0;

				clock_t begin = clock();
				while (counter != 100000) {
					fill_test100000.push_back(lcg());
					++counter;
				}
				clock_t end = clock();

				if (i != 99) {
					fill_test100000.clear();
				}
				fill_vattempts_100000[i] = double(end - begin) / double(CLOCKS_PER_SEC);
			}
			cout << "Average time to fill vector with 100000 elements: " << avg(fill_vattempts_100000) << endl;
			cout << endl;

			double findattempts_1000[1000], findattempts_10000[1000], findattempts_100000[1000];

			//ÏÎÈÑÊ ÝËÅÌÅÍÒÀ Â ÄÅÐÅÂÅ 1000
			for (size_t i = 0; i < 1000; ++i) {

				clock_t begin = clock();
				time_test_tree_1000.contains(lcg());
				clock_t end = clock();

				findattempts_1000[i] = double(end - begin) / double(CLOCKS_PER_SEC);
			}
			cout << "Average time to find elem in tree with 1000 elements: " << avg1000(findattempts_1000) << endl;

			//ÏÎÈÑÊ ÝËÅÌÅÍÒÀ Â ÄÅÐÅÂÅ 10000
			for (size_t i = 0; i < 1000; ++i) {
				clock_t begin = clock();
				time_test_tree_10000.contains(lcg());
				clock_t end = clock();

				findattempts_10000[i] = double(end - begin) / double(CLOCKS_PER_SEC);
			}
			cout << "Average time to find elem in tree with 10000 elements: " << avg1000(findattempts_10000) << endl;

			//ÏÎÈÑÊ ÝËÅÌÅÍÒÀ Â ÄÅÐÅÂÅ 100000
			for (size_t i = 0; i < 1000; ++i) {
				clock_t begin = clock();
				time_test_tree_100000.contains(lcg());
				clock_t end = clock();

				findattempts_100000[i] = double(end - begin) / double(CLOCKS_PER_SEC);
			}
			cout << "Average time to find elem in tree with 100000 elements: " << avg1000(findattempts_100000) << endl << endl;

			double vfindattempts_1000[1000], vfindattempts_10000[1000], vfindattempts_100000[1000];

			//ÏÎÈÑÊ ÝËÅÌÅÍÒÀ Â ÊÎÍÒÅÉÍÅÐÅ 1000
			for (size_t i = 0; i < 1000; ++i) {
				int elem = lcg();
				clock_t begin = clock();
				for (size_t i = 0; i < fill_test1000.size(); ++i) {
					if (fill_test1000[i] == elem) {
						break;
					}
				}
				clock_t end = clock();

				vfindattempts_1000[i] = double(end - begin) / double(CLOCKS_PER_SEC);
			}
			cout << "Average time to find elem in std::vector with 1000 elements: " << avg1000(vfindattempts_1000) << endl;

			//ÏÎÈÑÊ ÝËÅÌÅÍÒÀ Â ÊÎÍÒÅÉÍÅÐÅ 10000
			for (size_t i = 0; i < 1000; ++i) {
				int elem = lcg();
				clock_t begin = clock();
				for (size_t i = 0; i < fill_test10000.size(); ++i) {
					if (fill_test10000[i] == elem) {
						break;
					}
				}
				clock_t end = clock();

				vfindattempts_10000[i] = double(end - begin) / double(CLOCKS_PER_SEC);
			}
			cout << "Average time to find elem in std::vector with 10000 elements: " << avg1000(vfindattempts_10000) << endl;

			//ÏÎÈÑÊ ÝËÅÌÅÍÒÀ Â ÊÎÍÒÅÉÍÅÐÅ 100000
			for (size_t i = 0; i < 1000; ++i) {
				int elem = lcg();
				clock_t begin = clock();
				for (size_t i = 0; i < fill_test100000.size(); ++i) {
					if (fill_test100000[i] == elem) { break; }
				}
				clock_t end = clock();

				vfindattempts_100000[i] = double(end - begin) / double(CLOCKS_PER_SEC);
			}
			cout << "Average time to find elem in std::vector with 100000 elements: " << avg1000(vfindattempts_100000) << endl << endl;

			double add_del_attempts_1000[1000], add_del_attempts_10000[1000], add_del_attempts_100000[1000];

			//ÄÎÁÀÂËÅÍÈÅ È ÓÄÀËÅÍÈÅ Â ÄÅÐÅÂÅ 1000
			for (size_t i = 0; i < 1000; ++i) {
				int elem = lcg();
				clock_t begin = clock();
				time_test_tree_1000.insert(elem);
				time_test_tree_1000.erase(elem);
				clock_t end = clock();

				add_del_attempts_1000[i] = double(end - begin) / double(CLOCKS_PER_SEC);
			}
			cout << "Average time to add and delete elem in set with 1000 elements: " << avg1000(add_del_attempts_1000) << endl;

			//ÄÎÁÀÂËÅÍÈÅ È ÓÄÀËÅÍÈÅ Â ÄÅÐÅÂÅ 10000
			for (size_t i = 0; i < 1000; ++i) {
				int elem = lcg();
				clock_t begin = clock();
				time_test_tree_10000.insert(elem);
				time_test_tree_10000.erase(elem);
				clock_t end = clock();

				add_del_attempts_10000[i] = double(end - begin) / double(CLOCKS_PER_SEC);
			}
			cout << "Average time to add and delete elem in set with 10000 elem: " << avg1000(add_del_attempts_10000) << endl;

			//ÄÎÁÀÂËÅÍÈÅ È ÓÄÀËÅÍÈÅ Â ÄÅÐÅÂÅ 100000
			for (size_t i = 0; i < 1000; ++i) {
				int elem = lcg();
				clock_t begin = clock();
				time_test_tree_100000.insert(elem);
				time_test_tree_1000.erase(elem);
				clock_t end = clock();

				add_del_attempts_100000[i] = double(end - begin) / double(CLOCKS_PER_SEC);
			}
			cout << "Average time to add and delete elem in set with 100000 elements: " << avg1000(add_del_attempts_100000) << endl << endl;

			double add_del_vecattempts_1000[1000], add_del_vecattempts_10000[1000], add_del_vecattempts_100000[1000];

			//ÄÎÁÀÂËÅÍÈÅ È ÓÄÀËÅÍÈÅ Â ÊÎÍÒÅÉÍÅÐÅ 1000
			for (size_t i = 0; i < 1000; ++i) {
				int elem = lcg();
				clock_t begin = clock();
				fill_test1000.push_back(elem);
				fill_test1000.pop_back();
				clock_t end = clock();

				add_del_vecattempts_1000[i] = double(end - begin) / double(CLOCKS_PER_SEC);
			}
			cout << "Average time to add and delete elem in set with 100000 elements: " << avg1000(add_del_vecattempts_1000) << endl;

			//ÄÎÁÀÂËÅÍÈÅ È ÓÄÀËÅÍÈÅ Â ÊÎÍÒÅÉÍÅÐÅ 10000
			for (size_t i = 0; i < 1000; ++i) {
				int elem = lcg();
				clock_t begin = clock();
				fill_test10000.push_back(elem);
				fill_test10000.pop_back();
				clock_t end = clock();

				add_del_vecattempts_10000[i] = double(end - begin) / double(CLOCKS_PER_SEC);
			}
			cout << "Average time to add and delete elem in set with 100000 elements: " << avg1000(add_del_vecattempts_10000) << endl;

			//ÄÎÁÀÂËÅÍÈÅ È ÓÄÀËÅÍÈÅ Â VECTOR 100000
			for (size_t i = 0; i < 1000; ++i) {
				int elem = lcg();
				clock_t begin = clock();
				fill_test100000.push_back(elem);
				fill_test100000.pop_back();
				clock_t end = clock();

				add_del_vecattempts_100000[i] = double(end - begin) / double(CLOCKS_PER_SEC);
			}

			cout << "Average time to add and delete elem in set with 100000 elements: " << avg1000(add_del_vecattempts_100000) << endl << endl;
			break;
		}
		case 4: {
			cout << "Thanks for your attention" << endl;
			return 0;
		}
		}
	}
}