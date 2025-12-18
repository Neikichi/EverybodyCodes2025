#include <bits/stdc++.h>
#include <boost/functional/hash.hpp>

typedef long long ll;
using C = std::complex<ll>;

#define itN(x) x.begin(), x.end()
#define itNr(x) x.rbegin(), x.rend()
#define itNc(x) x.cbegin(), x.cend()
#define itNrc(x) x.crbegin(), x.crend()

struct pqCmp {
	bool operator()(const auto &a, const auto &b) const {
		auto &[pa, da] = a;
		auto &[pb, db] = b;

		if (da == db) {
			if (pa.real() == pb.real()) {
				return pa.imag() > pb.imag();
			}
			return pa.real() > pb.real();
		}
		return da > db;
	}
};

int main() {
	auto start = std::chrono::high_resolution_clock::now();

	std::ifstream file("notes.txt");
	if (!file) {
		std::cerr << "Error: cannot open notes.txt\n";
		return 1;
	}

	std::vector<std::tuple<ll, ll, ll>> obstacles;
	ll maxY = 0, maxX = 0;

	for (auto line : std::views::istream<std::string>(file)) {
		auto [a, b, c] = std::make_tuple(0LL, 0LL, 0LL);
		for (auto [i, parts] : std::views::enumerate(std::views::split(line, ','))) {
			ll val = std::stoll(std::string(parts.begin(), parts.end()));
			if (i == 0)
				a = val;
			else if (i == 1)
				b = val;
			else if (i == 2)
				c = val;
		}
		obstacles.emplace_back(a, b, c);
		if (a > maxX)
			maxX = a;
		if (b + c > maxY)
			maxY = b + c;
	}

	C startPos(0, maxY - 1);

	constexpr C UR(1, -1);  // up right
	constexpr C UL(-1, -1); // up left
	constexpr C DR(1, 1);   // down right
	constexpr C DL(-1, 1);  // down left

	// diagnal movement only
	std::vector<C> diagDir = {
	    UR,
	    DR,
	};

	std::unordered_set<C, boost::hash<C>> walls, holes, visited;
	for (const auto &[c, h, d] : obstacles) {
		for (ll i = maxY - 1, j = 0; i >= 0; --i, ++j) {
			if (j >= h && j < h + d) {
				holes.insert(C(c, i));
			} else {
				walls.insert(C(c, i));
			}
		}
	}

	for (const auto &hole : holes) {
		if (walls.count(hole)) {
			walls.erase(hole);
		}
	}

	std::priority_queue<std::pair<C, ll>, std::vector<std::pair<C, ll>>, pqCmp> pq;
	pq.push({startPos, 0});

	ll sum = 0;
	while (!pq.empty()) {
		auto &[curr, dist] = pq.top();
		pq.pop();

		if (curr.real() == maxX) {
			sum = dist;
			break;
		}

		for (const auto &dir : diagDir) {
			C next = curr + dir;
			if (next.real() < 0 || next.real() > maxX || next.imag() < 0 || next.imag() >= maxY)
				continue;
			if (walls.count(next))
				continue;
			if (!visited.insert(next).second)
				continue;
			ll nextDist = dir == UR ? dist + 1 : dist;
			pq.push({next, nextDist});
		}
	}

	std::cout << "Answer: " << sum << std::endl;

	auto end = std::chrono::high_resolution_clock::now();
	auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
	auto sec = std::chrono::duration_cast<std::chrono::duration<double>>(end - start).count();

	std::cout << "Elapsed time: " << ms << " ms (" << sec << " seconds)\n";
	return 0;
}
