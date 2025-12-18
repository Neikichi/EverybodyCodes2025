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

bool isChild(const std::string &a, const std::string &b, const std::string &c) {
	for (int i = 0; i < a.size(); i++) {
		if (c[i] != a[i] && c[i] != b[i]) {
			return false;
		}
	}
	return true;
}

ll calculateScore(const std::string &a, const std::string &b, const std::string &c) {
	ll pA = 0;
	ll pB = 0;
	for (int i = 0; i < a.size(); i++) {
		if (a[i] == c[i])
			pA++;
		if (b[i] == c[i])
			pB++;
	}
	return pA * pB;
}

struct pairScore {
	ll pA;
	ll pB;
	ll child;
};

int main() {

	std::vector<std::pair<ll, std::string>> arrNotes;

	std::ifstream file("notes.txt");
	std::string line;
	while (std::getline(file, line)) {
		auto splitStr = splitString(line, ':');
		arrNotes.push_back({std::stoll(splitStr[0]), splitStr[1]});
	}

	std::vector<std::string> cmp;
	for (const auto &note : arrNotes) {
		cmp.push_back(note.second);
	}

	std::vector<ll> sumCount;
	ll arrSize = cmp.size();
	for (int i = 0; i < arrSize; i++) {
		ll bestScore = 0;
		bool foundPair = false;
		for (int j = 0; j < arrSize; j++) {
			if (j == i) {
				continue;
			}
			for (int k = j + 1; k < arrSize; k++) {
				if (k == i) {
					continue;
				}
				if (!isChild(cmp[j], cmp[k], cmp[i])) {
					continue;
				}
				bestScore = calculateScore(cmp[j], cmp[k], cmp[i]);
				foundPair = true;
				break;
			}
		}
		if (foundPair) {
			sumCount.push_back(bestScore);
		}
	}

	for (const auto &ps : sumCount) {
		std::cout << ps << std::endl;
	}

	ll sum = std::accumulate(sumCount.begin(), sumCount.end(), 0LL);
	std::cout << "Answer: " << sum << std::endl;
	return 0;
}
