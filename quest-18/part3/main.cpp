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

ll dfs(const auto &plants, ll idx, const auto &testCase) {
	if (idx == 0) {
		return 1;
	}
	ll totalThickness = 0;

	for (const auto &[branchTo, branchThickness] : plants[idx].second) {
		if (branchTo == 0) {
			totalThickness += branchThickness * testCase[idx];
			continue;
		}
		totalThickness += branchThickness * dfs(plants, branchTo, testCase);
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
	std::vector<std::vector<ll>> testCase;

	auto blocks = splitString(data, "\n\n");

	plants.resize(blocks.size() + 1);

	for (auto &block : blocks) {
		auto lines = splitString(block, "\n");
		ll curIdx = 0;
		for (auto &line : lines) {
			if (line.empty()) {
				continue;
			}
			auto splitLine = splitString(line, " ");
			if (splitLine[0] == "Plant") {
				ll plantIdx = std::stoll(splitLine[1]);
				curIdx = plantIdx;
				// std::cout << "Plant index: " << plantIdx << "\n";
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
			} else {
				std::vector<ll> testRow(1, -1);
				for (const auto &val : splitLine) {
					testRow.push_back(std::stoll(val));
				}
				testCase.push_back(testRow);
			}
		}
	}

	if (!testCase.empty()) {
		plants.pop_back();
	}

	int size = testCase[0].size();
	std::unordered_map<std::vector<ll>, ll, boost::hash<std::vector<ll>>> memo;
	int testSize = testCase[0].size() - 1;
	std::vector<ll> best(testSize + 1, 0);

	for (int plant = 1; plant < plants.size(); ++plant) {
		for (auto &[src, weight] : plants[plant].second) {
			if (src > 0 && src <= testSize && weight > 0) {
				best[src] = 1;
			}
		}
	}

	ll optimal = dfs(plants, plants.size() - 1, best);

	ll sum = 0;

	for (const auto &row : testCase) {
		auto ret = dfs(plants, plants.size() - 1, row);
		memo[row] = ret;
	}

	ll maxMemo = [&memo]() {
		ll maxVal = 0;
		for (const auto &[key, val] : memo) {
			if (val > maxVal) {
				maxVal = val;
			}
		}
		return maxVal;
	}();

	for (const auto &row : testCase) {
		ll val = memo[row];
		if (val) {
			sum += std::abs(optimal - val);
		}
	}

	std::cout << "Answer: " << sum << std::endl;

	auto end = std::chrono::high_resolution_clock::now();
	auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
	auto sec = std::chrono::duration_cast<std::chrono::duration<double>>(end - start).count();

	std::cout << "Elapsed time: " << ms << " ms (" << sec << " seconds)\n";
	return 0;
}
