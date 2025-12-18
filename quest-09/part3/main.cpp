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

struct duck {
	ll pA;
	ll pB;
	ll c;
};

int main() {

	std::vector<std::pair<ll, std::string>> arrNotes;
	// std::map<char, std::string> arrNotes;

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

	std::vector<duck> ducks;
	for (int i = 0; i < arrSize; i++) {
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
				ducks.push_back({j, k, i});
				break;
			}
		}
	}

	std::vector<std::vector<ll>> trees(arrSize);

	for (auto &[pA, pB, c] : ducks) {
		if (pA == -1 || pB == -1) {
			continue;
		}
		trees[c].push_back(pA);
		trees[pA].push_back(c);
		trees[c].push_back(pB);
		trees[pB].push_back(c);
	}

	std::vector<bool> vis(arrSize, false);
	ll bestSize = 0;
	ll bestSum = 0;

	for (int i = 0; i < arrSize; i++) {
		if (vis[i])
			continue;

		std::queue<int> q;
		q.push(i);
		vis[i] = true;

		ll famSize = 0;
		ll famSum = 0;

		while (!q.empty()) {
			int u = q.front();
			q.pop();
			famSize++;
			famSum += arrNotes[u].first;

			for (int v : trees[u]) {
				if (!vis[v]) {
					vis[v] = true;
					q.push(v);
				}
			}
		}

		if (famSize > bestSize) {
			bestSize = famSize;
			bestSum = famSum;
		}
	}

	std::cout << "Answer: " << bestSum << std::endl;

	return 0;
}
