#include <bits/stdc++.h>
#include <boost/functional/hash.hpp>

typedef long long ll;
using C = std::complex<ll>;

#define itN(x) x.begin(), x.end()
#define itNr(x) x.rbegin(), x.rend()
#define itNc(x) x.cbegin(), x.cend()
#define itNrc(x) x.crbegin(), x.crend()

std::vector<std::string> splitString(const std::string &str, std::string delimiter) {
	std::vector<std::string> ret;
	size_t pos = 0, dlen = delimiter.length();
	std::string s = str;
	while ((pos = s.find(delimiter)) != std::string::npos) {
		std::string word = s.substr(0, pos);
		if (!word.empty())
			ret.push_back(word);
		s.erase(0, pos + dlen);
	}
	if (!s.empty())
		ret.push_back(s);
	return ret;
}

struct Walls {
	C st, end;
	std::ranges::minmax_result<ll> mmX, mmY;

	Walls(const C &s, const C &e) : st(s), end(e) {
		mmX = std::ranges::minmax({st.real(), end.real()});
		mmY = std::ranges::minmax({st.imag(), end.imag()});
	}

	bool isWithinX(ll pos) const {
		return (pos >= mmX.min && pos <= mmX.max);
	}

	bool isWithinY(ll pos) const {
		return (pos >= mmY.min && pos <= mmY.max);
	}
};

struct pqCmp {
	bool operator()(const auto &a, const auto &b) const {
		auto &[distA, tieA, _] = a;
		auto &[distB, tieB, __] = b;
		if (distA == distB)
			return tieA > tieB;
		return distA > distB;
	}
};

int main() {
	auto chronoSt = std::chrono::high_resolution_clock::now();

	constexpr C UR(1, -1);  // up right
	constexpr C UL(-1, -1); // up left
	constexpr C DR(1, 1);   // down right
	constexpr C DL(-1, 1);  // down left
	constexpr C N(0, -1);   // up
	constexpr C S(0, 1);    // down
	constexpr C E(1, 0);    // right
	constexpr C W(-1, 0);   // left
	constexpr C tR(0, 1);   // rotate right
	constexpr C tL(0, -1);  // rotate left

	constexpr auto dirz = std::array<C, 4>{N, S, E, W};
	constexpr auto dTurns = std::array<C, 2>{tR, tL};

	std::ifstream file("notes.txt");
	if (!file) {
		std::cerr << "Error: cannot open notes.txt\n";
		return 1;
	}

	std::vector<std::pair<char, ll>> instructions;

	for (auto [yy, line] : std::views::enumerate(std::views::istream<std::string>(file))) {
		auto words = splitString(line, ",");
		for (auto &word : words) {
			instructions.emplace_back(word[0], std::stoll(word.substr(1)));
		}
	}

	C pos(0, 0), dir = N, stPos(0, 0), endPos;

	std::vector<Walls> walls;
	std::set<ll> poi_x, poi_y;

	for (const auto &[idx, instr] : std::views::enumerate(instructions)) {
		const auto &[turn, steps] = instr;
		dir *= (turn == 'R') ? tR : tL;
		endPos = (idx == instructions.size() - 1) ? ((pos + dir * steps) - dir) : pos + dir * steps;

		Walls curWall(pos + dir, endPos);
		walls.emplace_back(curWall);
		pos += dir * steps;

		if (dir.imag() == 0) {
			poi_y.insert(pos.imag() - 1);
			poi_y.insert(pos.imag());
			poi_y.insert(pos.imag() + 1);
		} else {
			poi_x.insert(pos.real() - 1);
			poi_x.insert(pos.real());
			poi_x.insert(pos.real() + 1);
		}
	}

	endPos = pos;
	poi_x.insert(stPos.real());
	poi_y.insert(stPos.imag());
	poi_x.insert(endPos.real());
	poi_y.insert(endPos.imag());

	auto getNearestWallDist = [&](const C &curr, const C &dir) -> ll {
		ll wallDist = LLONG_MAX;

		for (const auto &wall : walls) {
			if (dir.imag() == 0) {
				if (!wall.isWithinY(curr.imag()))
					continue;

				if (dir.real() > 0 && wall.mmX.min > curr.real()) {
					wallDist = std::min(wallDist, wall.mmX.min - curr.real() - 1);
				} else if (dir.real() < 0 && wall.mmX.max < curr.real()) {
					wallDist = std::min(wallDist, curr.real() - wall.mmX.max - 1);
				}
			} else {
				if (!wall.isWithinX(curr.real()))
					continue;

				if (dir.imag() > 0 && wall.mmY.min > curr.imag()) {
					wallDist = std::min(wallDist, wall.mmY.min - curr.imag() - 1);
				} else if (dir.imag() < 0 && wall.mmY.max < curr.imag()) {
					wallDist = std::min(wallDist, curr.imag() - wall.mmY.max - 1);
				}
			}
		}

		return wallDist;
	};

	std::priority_queue<std::tuple<ll, ll, C>, std::vector<std::tuple<ll, ll, C>>, pqCmp> pq;
	std::unordered_set<C, boost::hash<C>> visited;
	pq.push({0, 0, stPos});
	visited.insert(stPos);

	ll sum = 0, inc = 0;

	while (!pq.empty()) {
		auto [dist, _, curr] = pq.top();
		pq.pop();

		if (curr == endPos) {
			sum = dist;
			break;
		}

		for (const auto &dir : dirz) {
			auto maxDist = getNearestWallDist(curr, dir);

			if (maxDist <= 0)
				continue;

			if (dir.imag() == 0) {
				for (auto &poi : poi_x) {
					if ((dir.real() > 0 && poi <= curr.real()) ||
					    (dir.real() < 0 && poi >= curr.real()))
						continue;
					ll moveDist = std::abs(poi - curr.real());

					if (moveDist > maxDist)
						continue;

					C nPos(poi, curr.imag());
					if (!visited.insert(nPos).second)
						continue;

					pq.push({dist + moveDist, inc++, nPos});
				}
			} else {
				for (auto &poi : poi_y) {
					if ((dir.imag() > 0 && poi <= curr.imag()) ||
					    (dir.imag() < 0 && poi >= curr.imag()))
						continue;

					ll moveDist = std::abs(poi - curr.imag());

					if (moveDist > maxDist)
						continue;

					C nPos(curr.real(), poi);

					if (!visited.insert(nPos).second)
						continue;
					pq.push({dist + moveDist, inc++, nPos});
				}
			}
		}
		// }
	}

	std::cout << "Answer: " << sum << "\n";

	{
		// End computation time
		auto chronoEnd = std::chrono::high_resolution_clock::now();
		auto chronoMS =
		    std::chrono::duration_cast<std::chrono::milliseconds>(chronoEnd - chronoSt).count();
		auto sec =
		    std::chrono::duration_cast<std::chrono::duration<double>>(chronoEnd - chronoSt).count();

		std::cout << "Elapsed time: " << chronoMS << " ms (" << sec << " seconds)\n";
	}
	return 0;
}
