#include <bits/stdc++.h>
#include <boost/functional/hash.hpp>

typedef long long ll;
using C = std::complex<ll>;

#define itN(x) x.begin(), x.end()
#define itNr(x) x.rbegin(), x.rend()
#define itNc(x) x.cbegin(), x.cend()
#define itNrc(x) x.crbegin(), x.crend()

int main() {
	auto start = std::chrono::high_resolution_clock::now();

	std::vector<std::string> board;

	ll maxY = 0, maxX = 0;
	C stPos;

	std::ifstream file("notes.txt");

	for (auto [yy, line] : std::views::enumerate(std::views::istream<std::string>(file))) {
		maxX = std::max(maxX, (ll)line.size());
		if (line.find('@') != std::string::npos) {
			stPos = C(line.find('@'), yy);
		}
		board.emplace_back(line);
		maxY++;
	}

	ll sum = 0;

	ll radius = 10;

	for (ll y = 0; y < maxY; y++) {
		for (ll x = 0; x < maxX; x++) {
			C currPos(x, y);
			if (currPos == stPos)
				continue;
			ll val = board[y][x] - '0';
			if (std::norm(currPos - stPos) <= radius * radius) {
				sum += val;
			}
		}
	}

	std::cout << "Answer: " << sum << std::endl;

	auto end = std::chrono::high_resolution_clock::now();
	auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
	auto sec = std::chrono::duration_cast<std::chrono::duration<double>>(end - start).count();

	std::cout << "Elapsed time: " << ms << " ms (" << sec << " seconds)\n";
	return 0;
}
