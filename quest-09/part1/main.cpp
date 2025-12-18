#include <bits/stdc++.h>

typedef long long ll;

std::vector<std::string> splitString(const std::string &str, char c) {
	std::vector<std::string> ret;
	std::string word;
	for (char ch : str) {
		if (ch == c && !word.empty()) {
			ret.push_back(word);
			word.clear();
		} else {
			word += ch;
		}
	}
	if (!word.empty()) {
		ret.push_back(word);
		word.clear();
	}
	return ret;
}

int main() {

	std::map<char, std::string> arrNotes;

	std::ifstream file("notes.txt");
	std::string line;
	while (std::getline(file, line)) {
		auto splitStr = splitString(line, ':');
		arrNotes[splitStr[0][0]] = splitStr[1];
	}

	std::vector<std::string> cmp;
	for (const auto &note : arrNotes) {
		cmp.push_back(note.second);
	}

	std::vector<ll> sumCount;
	ll arrSize = cmp.size();
	for (int i = 0; i < arrSize - 1; i++) {
		ll count = 0;
		for (int j = 0; j < cmp[arrSize - 1].size(); j++) {
			if (cmp[i][j] == cmp[arrSize - 1][j]) {
				count++;
			}
		}
		sumCount.push_back(count);
	}

	ll sum = std::accumulate(sumCount.begin(), sumCount.end(), 1LL, std::multiplies<ll>());
	std::cout << "Answer: " << sum << std::endl;
	return 0;
}
