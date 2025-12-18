#include <bits/stdc++.h>

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
		if (!word.empty())
			ret.push_back(word);
		s.erase(0, pos + dlen);
	}
	if (!s.empty())
		ret.push_back(s);
	return ret;
}

int main() {
	auto start = std::chrono::high_resolution_clock::now();

	std::ifstream file("notes.txt");
	if (!file) {
		std::cerr << "Error: cannot open notes.txt\n";
		return 1;
	}

	std::vector<ll> crates;

	for (auto [yy, line] : std::views::enumerate(std::views::istream<std::string>(file))) {
		for (auto part : std::views::split(line, ',')) {
			crates.push_back(std::stoll(std::string(itN(part))));
		}
	}

	std::sort(itN(crates));

	ll sum = [&crates]() {
		std::unordered_map<ll, ll> freq;
		for (auto &n : crates) {
			freq[n]++;
		}
		return std::ranges::max(std::views::values(freq));
	}();

	std::cout << "Answer: " << sum << std::endl;

	auto end = std::chrono::high_resolution_clock::now();
	auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
	auto sec = std::chrono::duration_cast<std::chrono::duration<double>>(end - start).count();

	std::cout << "Elapsed time: " << ms << " ms (" << sec << " seconds)\n";
	return 0;
}
