#include <bits/stdc++.h>
#include <boost/functional/hash.hpp>

typedef long long ll;

#define itN(x) x.begin(), x.end()
#define itNr(x) x.rbegin(), x.rend()
#define itNc(x) x.cbegin(), x.cend()
#define itNrc(x) x.crbegin(), x.crend()

int main() {
	auto start = std::chrono::high_resolution_clock::now();

	std::vector<ll> Seqs;

	ll y = 0, x = 0;

	std::ifstream file("notes.txt");

	for (auto [yy, line] : std::views::enumerate(std::views::istream<std::string>(file))) {
		for (auto word : std::views::split(line, ',')) {
			Seqs.emplace_back(std::stoll(std::string(word.begin(), word.end())));
		}
	}

	ll sum = 0;

	std::vector<int> vals(90, 0);

	for (const auto &s : Seqs) {
		ll count = 0;
		for (ll i = 0; i < 90; i++) {
			if (i % s == s - 1) {
				count++;
				vals[i]++;
			}
		}
		sum += count;
	}

	std::cout << "Answer: " << sum << std::endl;

	auto end = std::chrono::high_resolution_clock::now();
	auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
	auto sec = std::chrono::duration_cast<std::chrono::duration<double>>(end - start).count();

	std::cout << "Elapsed time: " << ms << " ms (" << sec << " seconds)\n";
	return 0;
}
