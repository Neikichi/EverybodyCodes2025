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
	Seqs.push_back(0);

	ll y = 0, x = 0;

	std::ifstream file("notes.txt");

	for (auto [yy, line] : std::views::enumerate(std::views::istream<std::string>(file))) {
		for (auto word : std::views::split(line, ',')) {
			Seqs.emplace_back(std::stoll(std::string(word.begin(), word.end())));
		}
	}

	std::vector<ll> initSeq;

	ll sum = 0;

	for (ll i = 1; i < Seqs.size(); i++) {
		if (Seqs[i] > 0) {
			initSeq.push_back(i);
			for (ll j = i; j < Seqs.size(); j += i) {
				Seqs[j]--;
			}
		}
	}

	sum = std::accumulate(itN(initSeq), 1LL, std::multiplies<ll>());

	std::cout << "Answer: " << sum << std::endl;

	auto end = std::chrono::high_resolution_clock::now();
	auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
	auto sec = std::chrono::duration_cast<std::chrono::duration<double>>(end - start).count();

	std::cout << "Elapsed time: " << ms << " ms (" << sec << " seconds)\n";
	return 0;
}
