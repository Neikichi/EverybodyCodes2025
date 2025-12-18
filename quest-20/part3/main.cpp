#include <bits/stdc++.h>
#include <boost/functional/hash.hpp>

typedef long long ll;
using C = std::complex<ll>;

#define itN(x) x.begin(), x.end()
#define itNr(x) x.rbegin(), x.rend()
#define itNc(x) x.cbegin(), x.cend()
#define itNrc(x) x.crbegin(), x.crend()

struct pqCmp {
	bool operator()(const std::tuple<ll, C, ll> &a, const std::tuple<ll, C, ll> &b) const {
		auto &[da, _, __] = a;
		auto &[db, ___, ____] = b;
		return da > db;
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

	std::unordered_map<C, C, boost::hash<C>> allT[3];

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
					allT[0][C(xx, yy)] = S;
					continue;
				}
				allT[0][C(xx, yy)] = N;
				continue;
			} else if (parts == '#') {
				if (startX == -1)
					startX = xx;
				continue;
			}
		}
		if (yy > maxY)
			maxY = yy;
	}

	auto rotate120ccw = [maxY](const C &point) -> C {
		ll r = point.imag(), c = point.real();
		ll new_r = (2 * maxY - c - r) / 2;
		ll new_c = maxY + r - (c - r) / 2;
		return C(new_c, new_r);
	};

	auto rotate120cw = [maxY](const C &point) -> C {
		ll r = point.imag(), c = point.real();
		ll new_r = (c - r) / 2;
		ll new_c = (4 * maxY - 3 * r - c) / 2;
		return C(new_c, new_r);
	};

	std::unordered_multimap<C, C, boost::hash<C>> fwdPairs[3], revPairs[3];

	allT[0][stPos] = (stPos.imag() + stPos.real()) % 2 == 0 ? S : N;
	allT[0][endPos] = (endPos.imag() + endPos.real()) % 2 == 0 ? S : N;

	for (const auto &[k, v] : allT[0]) {
		C rotCw = rotate120cw(k);
		C rotCcw = rotate120ccw(k);
		allT[1][rotCw] = (rotCw.imag() + rotCw.real()) % 2 == 0 ? S : N;
		allT[2][rotCcw] = (rotCcw.imag() + rotCcw.real()) % 2 == 0 ? S : N;
	}

	std::priority_queue<std::tuple<ll, C, ll>, std::vector<std::tuple<ll, C, ll>>, pqCmp> pq;
	pq.push({0, stPos, 0});

	std::unordered_set<C, boost::hash<C>> visited[3];
	ll sum = -1;
	while (!pq.empty()) {
		auto [dist, curr, rot] = pq.top();
		pq.pop();

		if (!visited[rot].insert(curr).second) {
			continue;
		}

		if (curr == endPos) {
			sum = dist;
			break;
		}

		ll nRot = (rot + 1) % 3;

		if (allT[nRot].count(curr)) {
			pq.push({dist + 1, curr, nRot});
		}

		for (const auto &dir : dirz) {
			C npos = curr + dir;

			if (allT[nRot].count(npos)) {
				auto cc = curr.real(), cr = curr.imag();
				auto nc = npos.real(), nr = npos.imag();

				if (dir == E || dir == W) {
					pq.push({dist + 1, npos, nRot});
				}
				if (dir == N) {
					if (allT[nRot][npos] == N && allT[rot][curr] == S) {
						pq.push({dist + 1, npos, nRot});
					}
				} else if (dir == S) {
					if (allT[nRot][npos] == S && allT[rot][curr] == N) {
						pq.push({dist + 1, npos, nRot});
					}
				}
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
