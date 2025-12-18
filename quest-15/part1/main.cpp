#include <bits/stdc++.h>
#include <boost/functional/hash.hpp>

typedef long long ll;
using C = std::complex<ll>;

void printGrid(const std::vector<std::pair<C, char>> &grid) {
	ll minX = std::ranges::min(grid, {}, [](auto &p) { return p.first.real(); }).first.real();
	ll maxX = std::ranges::max(grid, {}, [](auto &p) { return p.first.real(); }).first.real();
	ll minY = std::ranges::min(grid, {}, [](auto &p) { return p.first.imag(); }).first.imag();
	ll maxY = std::ranges::max(grid, {}, [](auto &p) { return p.first.imag(); }).first.imag();
	for (ll y = maxY; y >= minY; --y) {
		for (ll x = minX; x <= maxX; ++x) {
			auto it = std::find_if(grid.begin(), grid.end(), [x, y](auto &p) {
				return p.first.real() == x && p.first.imag() == y;
			});
			if (it != grid.end()) {
				std::cout << it->second;
			} else {
				std::cout << ' ';
			}
		}
		std::cout << std::endl;
	}
}

int main() {
	auto start = std::chrono::high_resolution_clock::now();

	std::vector<std::pair<char, ll>> arr;

	std::ifstream file("notes.txt");

	for (auto [ay, line] : std::views::enumerate(std::views::istream<std::string>(file))) {
		for (auto word : std::views::split(line, ',')) {
			arr.emplace_back(word[0], std::stoll(std::string(word.begin() + 1, word.end())));
		}
	}

	// directions
	C N(0, 1);
	C E(1, 0);
	C S(0, -1);
	C W(-1, 0);
	C dir4[4] = {N, E, S, W};

	// rotate
	C tR(0, -1);
	C tL(0, 1);

	std::unordered_set<C, boost::hash<C>> walls;

	C pos(0, 0), dir = N, sPos = pos, ePos;

	ll minX = 0, maxX = 0, minY = 0, maxY = 0;

	for (auto &[turn, steps] : arr) {
		dir *= (turn == 'R') ? tR : tL;
		for (auto i : std::views::iota(0LL, steps)) {
			pos += dir;
			walls.insert(pos);

			ll x = pos.real(), y = pos.imag();
			minX = std::min(minX, x);
			maxX = std::max(maxX, x);
			minY = std::min(minY, y);
			maxY = std::max(maxY, y);
		}
	}

	ePos = pos;
	walls.erase(ePos);

	// printGrid(grid);

	std::queue<std::pair<C, ll>> q;
	q.push({sPos, 0});

	ll sum = 0;

	std::unordered_set<C, boost::hash<C>> visited;

	while (!q.empty()) {
		auto [cur, dist] = q.front();
		q.pop();

		if (cur == ePos) {
			sum = dist;
			break;
		}

		for (C &dir : dir4) {
			C next = cur + dir;

			ll x = next.real(), y = next.imag();
			if (walls.count(next) || !visited.insert(next).second || x < minX || x > maxX ||
			    y < minY || y > maxY)
				continue;
			q.push(std::make_pair(next, dist + 1));
		}
	}

	std::cout << "Sum of steps: " << sum << std::endl;

	auto end = std::chrono::high_resolution_clock::now();
	auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
	auto sec = std::chrono::duration_cast<std::chrono::duration<double>>(end - start).count();

	std::cout << "Elapsed time: " << ms << " ms (" << sec << " seconds)\n";
	return 0;
}
