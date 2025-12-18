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

	std::vector<std::pair<ll, double>> arr;
	std::map<char, std::vector<std::string>> idNotes;

	std::ifstream file("notes.txt");
	std::string line;
	while (std::getline(file, line)) {
		auto splitStr = splitString(line, ',');
		for (const auto &word : splitStr) {
			arr.push_back({std::stoll(word), -1});
		}
	}

	ll maxNum = std::max_element(arr.begin(), arr.end(), [](const auto &a, const auto &b) {
		            return a.first < b.first;
	            })->first;
	double anglePoint = 360.0 / maxNum;

	ll sum = 0;
	std::vector<std::pair<ll, double>> points;
	for (ll i = 0; i < maxNum; i++) {
		points.push_back({i + 1, anglePoint * i});
	}

	for (auto &p : arr) {
		for (const auto &pt : points) {
			if (p.first == pt.first) {
				p.second = pt.second;
				break;
			}
		}
	}

	for (int i = 0; i < arr.size() - 1; i++) {
		double angleDiff = std::fmod(std::abs(arr[i].second - arr[i + 1].second), 360.0);
		if (angleDiff > 180.0) {
			angleDiff = 360.0 - angleDiff;
		}
		if (std::fabs(angleDiff - 180.0) < 1.0) {
			sum++;
		}
	}
	std::cout << "Answer: " << sum << std::endl;
	return 0;
}
