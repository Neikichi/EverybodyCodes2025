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

bool isCross(ll a, ll b, ll c, ll d) {
	if (a == b || c == d)
		return false;
	if (a == c || a == d || b == c || b == d)
		return false;

	if (a > b)
		std::swap(a, b);
	if (c > d)
		std::swap(c, d);

	return (a < c && c < b && b < d) || (c < a && a < d && d < b);
}

int main() {

	std::vector<ll> arr;

	std::ifstream file("notes.txt");
	std::string line;
	while (std::getline(file, line)) {
		auto splitStr = splitString(line, ',');
		for (const auto &word : splitStr) {
			arr.push_back(std::stoll(word));
		}
	}

	std::vector<std::pair<ll, ll>> pairs;
	for (size_t i = 0; i < arr.size() - 1; ++i) {
		pairs.push_back({arr[i], arr[i + 1]});
	}

	ll sum = 0;
	for (size_t i = 0; i < pairs.size() - 1; ++i) {
		for (size_t j = i + 1; j < pairs.size(); ++j) {
			if (isCross(pairs[i].first, pairs[i].second, pairs[j].first, pairs[j].second)) {
				sum++;
			}
		}
	}

	std::cout << "Answer: " << sum << std::endl;
	return 0;
}
