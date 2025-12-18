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

	std::vector<ll> swords;

	for (auto [yy, line] : std::views::enumerate(std::views::istream<std::string>(file))) {
		auto splits = splitString(line.substr(line.find(':') + 1), ",");
		for (const auto &n : splits) {
			swords.push_back(std::stoll(n));
		}
	}

	auto buildSpine = [](auto &bones) {
		std::vector<std::tuple<ll, ll, ll>> spine;

		spine.emplace_back(std::make_tuple(-1, -1, -1));
		for (const auto &n : bones) {
			bool inserted = false;
			for (auto &[l, m, r] : spine) {
				if (m == -1) {
					m = n;
					inserted = true;
					break;
				} else if (n < m && l == -1) {
					l = n;
					inserted = true;
					break;
				} else if (n > m && r == -1) {
					r = n;
					inserted = true;
					break;
				}
			}
			if (!inserted)
				spine.emplace_back(std::make_tuple(-1, n, -1));
		}

		ll bonesVal = [&spine]() {
			std::string val;
			for (const auto &[_, m, __] : spine) {
				val.append(std::to_string(m));
			}
			return std::stoll(val);
		}();
		return std::make_pair(spine, bonesVal);
	};

	std::pair<std::vector<std::tuple<ll, ll, ll>>, ll> swordsBone = buildSpine(swords);

	ll sum = swordsBone.second;

	std::cout << "Answer: " << sum << std::endl;

	auto end = std::chrono::high_resolution_clock::now();
	auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
	auto sec = std::chrono::duration_cast<std::chrono::duration<double>>(end - start).count();

	std::cout << "Elapsed time: " << ms << " ms (" << sec << " seconds)\n";
	return 0;
}
