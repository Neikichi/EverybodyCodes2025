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

	constexpr C UR(1, -1);  // up right
	constexpr C UL(-1, -1); // up left
	constexpr C DR(1, 1);   // down right
	constexpr C DL(-1, 1);  // down left
	constexpr C N(0, -1);   // up
	constexpr C S(0, 1);    // down
	constexpr C E(1, 0);    // right
	constexpr C W(-1, 0);   // left

	constexpr auto dirz = std::array<C, 2>{S, E};

	std::ifstream file("notes.txt");
	if (!file) {
		std::cerr << "Error: cannot open notes.txt\n";
		return 1;
	}

	std::vector<std::tuple<C, C, ll>> notTriangles;
	std::unordered_set<C, boost::hash<C>> visited;
	std::unordered_map<C, C, boost::hash<C>> allT;

	ll maxY = 0, maxX = 0;

	for (auto [yy, line] : std::views::enumerate(std::views::istream<std::string>(file))) {
		ll startX = -1;
		for (auto [xx, parts] : std::views::enumerate(line)) {
			if (xx > maxX)
				maxX = xx;
			if (parts == '.') {
				continue;
			} else if (parts == 'T') {
				if (startX == -1)
					startX = xx;
				ll mod = startX % 2;
				if (xx % 2 == mod) {
					notTriangles.emplace_back(C(xx, yy), S, 1);
					allT[C(xx, yy)] = S;
					continue;
				}
				notTriangles.emplace_back(C(xx, yy), N, 1);
				allT[C(xx, yy)] = N;
				continue;
			} else if (parts == '#') {
				if (startX == -1)
					startX = xx;
				notTriangles.emplace_back(C(xx, yy), C(), 0);
				continue;
			}
		}
		if (yy > maxY)
			maxY = yy;
	}

	ll sum = 0;

	for (const auto &[k, v] : allT) {
		for (const auto &dir : dirz) {
			C npos = k + dir;
			if (allT.count(npos)) {
				if (dir == S && v == S) {
					continue;
				}
				sum += 1;
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
