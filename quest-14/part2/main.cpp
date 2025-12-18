#include <bits/stdc++.h>

typedef long long ll;

#define itALL(v) v.begin(), v.end()
#define itALLc(v) v.cbegin(), v.cend()

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
		x = line.size() > x ? line.size() : x;
		y++;
	}

	std::sort(itALL(aMagic));
	std::sort(itALL(iMagic));

	const std::vector<std::pair<ll, ll>> dir = {{-1, -1}, // top-left
	                                            {-1, 1},  // top-right
	                                            {1, -1},  // bot-left
	                                            {1, 1}};

	int rounds = 2025;

	ll sum = 0;
	for (int r = 0; r < rounds; ++r) {
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
		sum += aMagic.size();
	}

	std::cout << "Answer: " << sum << std::endl;

	auto end = std::chrono::high_resolution_clock::now();
	auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
	auto sec = std::chrono::duration_cast<std::chrono::duration<double>>(end - start).count();

	std::cout << "Elapsed time: " << ms << " ms (" << sec << " seconds)\n";
	return 0;
}
