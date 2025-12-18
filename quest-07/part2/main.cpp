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

	std::vector<std::pair<std::string, ll>> arr;
	std::map<char, std::vector<std::string>> idNotes;

	std::ifstream file("notes.txt");
	std::string line;
	while (std::getline(file, line)) {
		if (line.empty())
			continue;
		if (line.find(">") != std::string::npos) {
			auto splitStr = splitString(line.substr(4), ',');
			idNotes[line[0]] = splitStr;
		} else if (line.find(",") != std::string::npos) {
			auto splitStr = splitString(line, ',');
			for (const auto &word : splitStr) {
				arr.push_back({word, 0});
			}
		}
	}

	for (auto &[k, v] : idNotes) {
		for (auto &pair : arr) {
			for (auto it = pair.first.begin(); it != pair.first.end(); ++it) {
				if (*it == k && it + 1 != pair.first.end()) {
					for (const auto &word : v) {
						if (*(it + 1) == word[0]) {
							pair.second += 1;
							break;
						}
					}
					pair.second -= 1;
				}
			}
		}
	}

	ll sum = 0;

	ll maxNum = std::max_element(arr.begin(), arr.end(), [](const auto &a, const auto &b) {
		            return a.second < b.second;
	            })->second;
	for (int i = 0; i < arr.size(); i++) {
		if (arr[i].second == maxNum) {
			sum += i + 1;
		}
	}

	std::cout << "Answer: " << sum << std::endl;
	return 0;
}
