#include <bits/stdc++.h>

typedef long long ll;

int main() {

	std::map<char, std::pair<int, std::vector<int>>> nMap;
	std::map<char, int> catAll;

	std::ifstream file("notes.txt");
	std::string line;
	while (std::getline(file, line)) {
		for (char ch : line) {
			if (std::isupper(ch)) {
				nMap[ch].first++;
				catAll[ch];
			} else if (std::islower(ch)) {
				nMap[std::toupper(ch)].second.push_back(nMap[std::toupper(ch)].first);
			}
		}
	}

	ll sum = 0;

	for (auto &[k, v] : nMap) {
		int total = 0;
		for (int i : v.second) {
			total += i;
		}
		catAll[k] = total;
	}

	std::cout << "Answer: " << sum << std::endl;
	return 0;
}
