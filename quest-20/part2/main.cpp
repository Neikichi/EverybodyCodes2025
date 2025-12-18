#include <bits/stdc++.h>
#include <boost/functional/hash.hpp>

typedef long long ll;
using C = std::complex<ll>;

#define itN(x) x.begin(), x.end()
#define itNr(x) x.rbegin(), x.rend()
#define itNc(x) x.cbegin(), x.cend()
#define itNrc(x) x.crbegin(), x.crend()

struct pqCmp {
	bool operator()(const std::pair<ll, C> &a, const std::pair<ll, C> &b) const {
		return a.first > b.first; // min-heap on distance
	}
};

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

	constexpr auto dirz = std::array<C, 4>{N, E, S, W};

	std::ifstream file("notes.txt");
	if (!file) {
		std::cerr << "Error: cannot open notes.txt\n";
		return 1;
	}

	std::vector<std::tuple<C, C, ll>> notTriangles;
	std::unordered_set<C, boost::hash<C>> visited;
	std::unordered_map<C, C, boost::hash<C>> allT;

	ll maxY = 0, maxX = 0;
	C stPos, endPos;

	for (auto [yy, line] : std::views::enumerate(std::views::istream<std::string>(file))) {
		ll startX = -1;
		for (auto [xx, parts] : std::views::enumerate(line)) {
			if (xx > maxX)
				maxX = xx;
			if (parts == 'S') {
				stPos = C(xx, yy);
			}
			if (parts == 'E') {
				endPos = C(xx, yy);
			}
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

	ll pairCount = 0;

	std::unordered_multimap<C, C, boost::hash<C>> fwdPairs, revPairs;

	for (const auto &[k, v] : allT) {
		for (const auto &dir : {S, E}) {
			C npos = k + dir;
			if (allT.count(npos)) {
				if (dir == S && v == S) {
					continue;
				}
				pairCount += 1;
				fwdPairs.insert({k, npos});
				revPairs.insert({npos, k});
			}
		}
	}

	std::priority_queue<std::pair<ll, C>, std::vector<std::pair<ll, C>>, pqCmp> pq;
	pq.push({1, stPos + N});

	ll sum = 0;

	while (!pq.empty()) {
		auto [dist, curr] = pq.top();
		pq.pop();

		bool reachedEnd = false;
		for (const auto &dir : dirz) {
			C npos = curr + dir;
			if (npos == endPos) {
				sum += dist + 1;
				reachedEnd = true;
			}
		}

		if (reachedEnd)
			break;

		C npos = curr;
		if (npos == endPos) {
			if (!visited.insert(endPos).second)
				continue;
			pq.push({dist + 1, endPos});
			continue;
		}
		if (npos.imag() < 0 || npos.imag() > maxY || npos.real() < 0 || npos.real() > maxX)
			continue;
		auto fwd = fwdPairs.equal_range(npos);
		auto rev = revPairs.equal_range(npos);

		if (fwd.first == fwd.second && rev.first == rev.second) {
			continue;
		}

		for (auto it = fwd.first; it != fwd.second; ++it) {
			C toPos = it->second;
			if (!visited.insert(toPos).second)
				continue;
			pq.push({dist + 1, toPos});
		}

		for (auto it = rev.first; it != rev.second; ++it) {
			C toPos = it->second;
			if (!visited.insert(toPos).second)
				continue;
			pq.push({dist + 1, toPos});
		}
	}

	std::cout << "Answer: " << sum << std::endl;

	auto end = std::chrono::high_resolution_clock::now();
	auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
	auto sec = std::chrono::duration_cast<std::chrono::duration<double>>(end - start).count();

	std::cout << "Elapsed time: " << ms << " ms (" << sec << " seconds)\n";
	return 0;
}
