#include <bits/stdc++.h>
#include <boost/functional/hash.hpp>

typedef long long ll;
using C = std::complex<ll>;

#define itN(x) x.begin(), x.end()
#define itNr(x) x.rbegin(), x.rend()
#define itNc(x) x.cbegin(), x.cend()
#define itNrc(x) x.crbegin(), x.crend()

std::vector<std::string> splitString(const std::string &str, std::string delimiter) {
	std::vector<std::string> ret;
	std::string word;
	size_t pos = 0, dlen = delimiter.length();
	std::string s = str;
	while ((pos = s.find(delimiter)) != std::string::npos) {
		word = s.substr(0, pos);
		ret.push_back(word);
		s.erase(0, pos + dlen);
	}
	if (!s.empty())
		ret.push_back(s);
	return ret;
}

ll dfs(const auto &plants, ll idx) {
	if (idx == 0) {
		return 1;
	}

	ll totalThickness = 0;

	for (const auto &[branchTo, branchThickness] : plants[idx].second) {
		totalThickness += branchThickness * dfs(plants, branchTo);
	}

	if (totalThickness < plants[idx].first) {
		return 0;
	}
	return totalThickness;
}

int main() {
	auto start = std::chrono::high_resolution_clock::now();

	std::ifstream file("notes.txt");
	if (!file) {
		std::cerr << "Error: cannot open notes.txt\n";
		return 1;
	}

	std::string data((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
	file.close();

	std::vector<std::pair<ll, std::vector<std::pair<ll, ll>>>> plants;

	auto blocks = splitString(data, "\n\n");

	plants.resize(blocks.size() + 1);

	for (auto &block : blocks) {
		auto lines = splitString(block, "\n");
		ll curIdx = 0;
		for (auto &line : lines) {
			auto splitLine = splitString(line, " ");
			if (splitLine[0] == "Plant") {
				ll plantIdx = std::stoll(splitLine[1]);
				curIdx = plantIdx;
				ll plantThickness = std::stoll(splitLine[splitLine.size() - 1]);
				plants[plantIdx].first = plantThickness;
			} else if (splitLine[1] == "branch") {
				ll branchTo = std::stoll(splitLine[4]);
				ll branchThickness = std::stoll(splitLine[splitLine.size() - 1]);
				plants[curIdx].second.push_back({branchTo, branchThickness});
			} else if (splitLine[1] == "free") {
				ll branchTo = 0;
				ll branchThickness = std::stoll(splitLine[splitLine.size() - 1]);
				plants[curIdx].second.push_back({branchTo, branchThickness});
			}
		}
	}

	if (plants[0].first <= 0) {
		plants[0].first = 1;
	}

	ll sum = dfs(plants, plants.size() - 1);

	std::cout << "Answer: " << sum << std::endl;

	auto end = std::chrono::high_resolution_clock::now();
	auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
	auto sec = std::chrono::duration_cast<std::chrono::duration<double>>(end - start).count();

	std::cout << "Elapsed time: " << ms << " ms (" << sec << " seconds)\n";
	return 0;
}
