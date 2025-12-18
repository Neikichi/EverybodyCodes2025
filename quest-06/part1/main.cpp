#include <bits/stdc++.h>

typedef long long ll;

int main() {

	std::map<char, std::pair<int, std::vector<int>>> nMap;

	std::ifstream file("notes.txt");
	std::string line;
	while (std::getline(file, line)) {
		for (char ch : line) {
			if (std::isupper(ch)) {
				nMap[ch].first++;
			} else if (std::islower(ch)) {
				nMap[std::toupper(ch)].second.push_back(nMap[std::toupper(ch)].first);
			}
		}
	}

	ll sum = 0;

	for (auto &[k, v] : nMap) {
		if (k == 'A') {
			for (auto &num : v.second) {
				std::cout << num << " ";
				sum += num;
			}
			std::cout << std::endl;
		}
	}

	std::cout << "Answer: " << sum << std::endl;
	return 0;
}
