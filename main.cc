#include "/public/read.h"
#include <fstream>
#include <vector>
#include <unordered_set>
#include <cstdlib>
using namespace std;
//Nickolai's code

void die() {
	cout << "You dun goofed.\n";
	exit(0);
}

int main() {
	string filename = read("Please enter a filename:\n");
	ifstream infile(filename);
	if (!infile.is_open()) die();

	int n = 0;
	if (!(infile >> n) || n < 2) die();

	vector<int> briefcases(n);
	for (int i = 0; i < n; ++i) {
		if (!(infile >> briefcases[i]) || briefcases[i] <= 0) die();
	}

	unordered_set<int> opened;
	int last_offer = 0;

	while (true) {
		string input = read("Please enter a briefcase to open:\n");

		int choice;
		try {
			choice = stoi(input);
		} catch (...) {
			die();
		}

		if (choice == -1) {
			cout << "You won " << last_offer << " dollars!\n";
			break;
		}

		if (choice < 0 || choice >= n || opened.count(choice)) die();

		opened.insert(choice);
		cout << "That briefcase held " << briefcases[choice] << " dollars\n";
		if (opened.size() == n - 1) {
			for (int i = 0; i < n; ++i) {
				if (!opened.count(i)) {
					cout << "You won " << briefcases[i] << " dollars!\n";
					return 0;
				}
			}
		}

		int sum = 0;
		int count = 0;
		for (int i = 0; i < n; ++i) {
			if (!opened.count(i)) {
				sum += briefcases[i];
				++count;
			}
		}

		if (count == 0) die();
		last_offer = sum / count;
		cout << "I will offer you " << last_offer << " dollars to walk away.\n";
	}
	return 0;
}
