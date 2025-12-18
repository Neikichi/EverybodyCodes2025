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
	if ((a == c && b == d) || (a == d && b == c))
		return true;

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

	ll maxN = *std::max_element(arr.begin(), arr.end());

	std::vector<std::pair<std::pair<ll, ll>, ll>> swordPairs;
	for (int i = 1; i <= maxN; ++i) {
		for (int j = i + 1; j <= maxN; ++j) {
			swordPairs.push_back({{i, j}, 0});
		}
	}

	std::vector<std::pair<ll, ll>> pairs;
	for (size_t i = 0; i < arr.size() - 1; ++i) {
		pairs.push_back({arr[i], arr[i + 1]});
	}

	ll sum = 0;

	for (auto &swordPair : swordPairs) {
		ll count = 0;
		for (const auto &p : pairs) {
			if (isCross(swordPair.first.first, swordPair.first.second, p.first, p.second)) {
				count++;
			}
		}
		swordPair.second = count;
	}

	auto maxPair =
	    *std::max_element(swordPairs.begin(), swordPairs.end(), [](const auto &a, const auto &b) {
		    return a.second < b.second;
	    });

	std::cout << "Answer: " << sum << std::endl;
	return 0;
}
