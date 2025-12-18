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

	std::ifstream file("notes.txt");
	if (!file) {
		std::cerr << "Error: cannot open notes.txt\n";
		return 1;
	}

	std::map<ll, std::vector<std::pair<ll, ll>>> obstacles;
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
		obstacles[a].push_back({b, c});
		if (a > maxX)
			maxX = a;
		if (b + c > maxY)
			maxY = b + c;
	}

	// merge intersect holes at same x
	for (const auto &[x, vh] : obstacles) {
		std::vector<std::pair<ll, ll>> merged;
		for (const auto &[h, dist] : vh) {
			ll nDist = h + dist - 1;
			if (!merged.empty() && h <= merged.back().second + 1) {
				merged.back().second = std::max(merged.back().second, nDist);
				continue;
			}
			merged.push_back({h, nDist});
		}
		obstacles[x] = merged;
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

	auto mergingBand = [](std::vector<std::pair<ll, ll>> vi) {
		if (vi.empty())
			return vi;

		std::sort(itN(vi));
		std::vector<std::pair<ll, ll>> ret;
		ret.push_back(vi[0]);
		for (auto &[minH, maxH] : vi) {
			auto &[lastMinH, lastMaxH] = ret.back();
			if (minH <= lastMaxH + 1) {
				lastMaxH = std::max(lastMaxH, maxH);
			} else {
				ret.push_back({minH, maxH});
			}
		}
		return ret;
	};

	auto intersectBand = [](const std::vector<std::pair<ll, ll>> &bandA,
	                        const std::vector<std::pair<ll, ll>> &holeB) {
		std::vector<std::pair<ll, ll>> ret;
		size_t i = 0, j = 0;

		while (i < bandA.size() && j < holeB.size()) {
			ll lo = std::max(bandA[i].first, holeB[j].first);
			ll hi = std::min(bandA[i].second, holeB[j].second);

			if (lo <= hi)
				ret.push_back({lo, hi});

			if (bandA[i].second < holeB[j].second)
				i++;
			else
				j++;
		}

		return ret;
	};

	std::vector<std::pair<ll, ll>> band = {{0, 0}};

	ll prevX = startPos.real();
	for (auto &[x, holes] : obstacles) {
		ll dx = x - prevX;

		for (auto &[minH, maxH] : band) {
			minH -= dx;
			maxH += dx;
			if (minH < 0)
				minH = 0;
		}

		band = mergingBand(band);

		band = intersectBand(band, holes);
		if (band.empty()) {
			std::cout << "Blocked at x=" << x << "\n";
			return 0;
		}

		prevX = x;
	}

	ll sdx = maxX - prevX;
	for (auto &[minH, maxH] : band) {
		minH -= sdx;
		maxH += sdx;
		if (minH < 0)
			minH = 0;
	}

	band = mergingBand(band);

	ll bestMinH = -1;
	for (const auto &[minH, maxH] : band) {
		ll candidate = minH;
		if ((maxX + candidate) % 2 != 0) {
			candidate++;
		}
		if (candidate <= maxH) {
			bestMinH = candidate;
			break;
		}
	}

	if (bestMinH != -1) {
		ll answer = (maxX + bestMinH) / 2;
		std::cout << "Answer: " << answer << std::endl;
	} else {
		std::cout << "No valid answer.\n";
		return 0;
	}

	auto end = std::chrono::high_resolution_clock::now();
	auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
	auto sec = std::chrono::duration_cast<std::chrono::duration<double>>(end - start).count();

	std::cout << "Elapsed time: " << ms << " ms (" << sec << " seconds)\n";
	return 0;
}
