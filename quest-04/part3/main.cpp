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

	std::vector<std::pair<ll, ll>> arr;
	long double left = 0, right = 0;

	std::ifstream file("notes.txt");
	std::string line;
	while (std::getline(file, line)) {
		if (line.find("|") != std::string::npos) {
			auto splitStr = splitString(line, '|');
			arr.push_back({std::stoll(splitStr[0]), std::stoll(splitStr[1])});
		} else {
			if (arr.empty()) {
				left = std::stoll(line);
			} else {
				right = std::stoll(line);
			}
		}
	}

	ll cycles = 100;

	for (auto p : arr) {
		left *= p.second;
		right *= p.first;
	}

	ll sum = cycles * left / right;

	std::cout << "Answer: " << sum << std::endl;
	return 0;
}
