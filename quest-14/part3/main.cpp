#include <bits/stdc++.h>
#include <boost/functional/hash.hpp>

typedef long long ll;

#define itALL(v) v.begin(), v.end()
#define itALLc(v) v.cbegin(), v.cend()

size_t hashState(const auto &a, const auto &b) {
	size_t h = 0;
	boost::hash_combine(h, boost::hash<decltype(a)>()(a));
	boost::hash_combine(h, boost::hash<decltype(b)>()(b));
	return h;
}

bool isMatch(const std::vector<std::pair<ll, ll>> &aMagic,
             const std::vector<std::pair<ll, ll>> &iMagic,
             const std::vector<std::pair<ll, ll>> &laMagic,
             const std::vector<std::pair<ll, ll>> &liMagic) {

	for (auto &[y, x] : laMagic) {
		if (!std::binary_search(aMagic.begin(), aMagic.end(), std::make_pair(y, x)))
			return false;
	}

	for (auto &[y, x] : liMagic) {
		if (!std::binary_search(iMagic.begin(), iMagic.end(), std::make_pair(y, x)))
			return false;
	}

	return true;
}

int main() {

	auto start = std::chrono::high_resolution_clock::now();
	std::vector<std::pair<ll, ll>> aMagic, iMagic;

	ll x = 0, y = 0, tx = 0;

	std::ifstream file("notes.txt");
	std::string line;
	while (std::getline(file, line)) {
		tx = 0;
		for (char &ch : line) {
			if (ch == '#') {
				aMagic.push_back({y, tx});
			} else {
				iMagic.push_back({y, tx});
			}
			tx++;
		}
		x = static_cast<ll>(line.size()) > x ? line.size() : x;
		y++;
	}

	std::sort(itALL(aMagic));
	std::sort(itALL(iMagic));

	const std::vector<std::pair<ll, ll>> dir = {{-1, -1}, // top-left
	                                            {-1, 1},  // top-right
	                                            {1, -1},  // bot-left
	                                            {1, 1}};

	std::vector<std::pair<ll, ll>> laMagic, liMagic;

	// create a 34 x 34 grid with border of inactive magic tiles
	ll sy = 34;
	ll sx = 34;
	for (int yy = 0; yy < sy; ++yy) {
		for (int xx = 0; xx < sx; ++xx) {
			liMagic.push_back({yy, xx});
		}
	}

	std::sort(itALL(laMagic));
	std::sort(itALL(liMagic));

	ll oy = (sy / 2) - (y / 2);
	ll ox = (sx / 2) - (x / 2);

	for (auto &[y, x] : aMagic) {
		y = y + oy;
		x = x + ox;
	}
	for (auto &[y, x] : iMagic) {
		y = y + oy;
		x = x + ox;
	}

	aMagic.swap(laMagic);
	iMagic.swap(liMagic);

	ll rounds = 1000000000;
	ll cycle = 0;
	ll cycleStart = 0;
	ll cycleLen = 0;

	std::vector<std::pair<ll, ll>> matchRounds;

	std::unordered_map<size_t, ll, boost::hash<size_t>> memo;

	ll sum = 0;
	for (ll r = 0; r < rounds; ++r) {
		std::vector<std::pair<ll, ll>> naMagic, niMagic;

		for (auto &[y, x] : aMagic) {
			ll aDiag = 0;
			for (const auto &[dy, dx] : dir) {
				ll ny = y + dy;
				ll nx = x + dx;

				if (std::binary_search(itALL(aMagic), std::make_pair(ny, nx))) {
					aDiag++;
				}
			}
			ll iDiag = 4 - aDiag;
			if (aDiag && aDiag % 2 == 1) {
				naMagic.push_back({y, x});
			} else {
				niMagic.push_back({y, x});
			}
		}

		for (auto &[y, x] : iMagic) {
			ll aDiag = 0;
			for (const auto &[dy, dx] : dir) {
				ll ny = y + dy;
				ll nx = x + dx;

				if (std::binary_search(itALL(aMagic), std::make_pair(ny, nx))) {
					aDiag++;
				}
			}
			ll iDiag = 4 - aDiag;
			if (aDiag % 2 == 0) {
				naMagic.push_back({y, x});
			} else {
				niMagic.push_back({y, x});
			}
		}
		std::sort(itALL(naMagic));
		std::sort(itALL(niMagic));
		aMagic.swap(naMagic);
		iMagic.swap(niMagic);

		size_t stateHash = hashState(aMagic, iMagic);

		if (memo.find(stateHash) != memo.end()) {

			cycleStart = memo[stateHash];
			cycleLen = (r + 1) - cycleStart;

			break;
		} else {
			memo[stateHash] = r + 1;
		}

		if (isMatch(aMagic, iMagic, laMagic, liMagic)) {
			matchRounds.push_back({r + 1, aMagic.size()});
		}
	}

	ll cycleSum = 0;
	for (auto &[ri, activeCount] : matchRounds) {
		if (ri >= cycleStart && ri < cycleStart + cycleLen) {
			cycleSum += activeCount;
		}
	}

	ll cyclesRound = rounds / cycleLen;
	ll remRounds = rounds % cycleLen;

	ll remSum = 0;
	for (auto &[ri, activeCount] : matchRounds) {
		if (ri < cycleStart)
			continue; // not in cycle

		if ((ri - cycleStart) < remRounds) {
			remSum += activeCount;
		}
	}

	sum = cyclesRound * cycleSum + remSum;

	std::cout << "Answer: " << sum << std::endl;

	auto end = std::chrono::high_resolution_clock::now();
	auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
	auto sec = std::chrono::duration_cast<std::chrono::duration<double>>(end - start).count();

	std::cout << "Elapsed time: " << ms << " ms (" << sec << " seconds)\n";
	return 0;
}
