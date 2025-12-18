#include <bits/stdc++.h>
#include <boost/functional/hash.hpp>

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
	std::unordered_set<std::string, boost::hash<std::string>> uniqueWords;

	std::function<void(std::string)> recCount = [&](std::string word) {
		if (word.size() >= 7 && word.size() <= 11) {
			uniqueWords.insert(word);
		}
		if (word.size() > 11)
			return;
		for (auto &[k, v] : idNotes) {
			if (*(word.end() - 1) == k) {
				for (const auto &nextWord : v) {
					auto newWord = word + nextWord[0];
					recCount(newWord);
				}
			}
		}
		return;
	};

	for (int i = 0; i < arr.size(); i++) {
		if (arr[i].second == maxNum && arr[i].first.size() <= 11) {
			if (arr[i].first.size() >= 7 && arr[i].first.size() <= 11)
				uniqueWords.insert(arr[i].first);
			recCount(arr[i].first);
		}
	}

	std::cout << "Answer: " << uniqueWords.size() << std::endl;
	return 0;
}
