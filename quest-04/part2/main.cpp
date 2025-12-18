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

	std::vector<ll> arr;

	std::ifstream file("notes.txt");
	std::string line;
	while (std::getline(file, line)) {
		auto splitStr = splitString(line, ' ');
		for (const auto &word : splitStr) {
			arr.push_back(std::stoll(word));
		}
	}

	ll min = *std::min_element(arr.begin(), arr.end());
	ll max = *std::max_element(arr.begin(), arr.end());

	ll cycles = 10000000000000;

	ll sum = std::ceil(static_cast<long double>(cycles) * min / max);

	std::cout << "Answer: " << sum << std::endl;
	return 0;
}
