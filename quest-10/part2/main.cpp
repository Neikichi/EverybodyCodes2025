#include <bits/stdc++.h>

typedef long long ll;

#define rnc(y, x) ((y) * arrSize.second + (x))
#define gRow(rnc) ((rnc) / arrSize.second)
#define gCol(rnc) ((rnc) % arrSize.second)
#define itALL(v) v.begin(), v.end()
#define itALLc(v) v.cbegin(), v.cend()

int main() {

	auto start = std::chrono::high_resolution_clock::now();
	std::vector<std::tuple<int, int>> Sheeps, Ducks, Hides;

	ll x = 0, y = 0, tx = 0;

	std::pair<ll, ll> arrSize;
	std::vector<std::string> Boards;

	std::ifstream file("notes.txt");
	std::string line;
	while (std::getline(file, line)) {
		tx = 0;
		for (char &ch : line) {
			if (ch == 'S') {
				Sheeps.push_back({y, tx});
			} else if (ch == 'D') {
				Ducks.push_back({y, tx});
				// dStart = {y, tx};
			} else if (ch == '#') {
				Hides.push_back({y, tx});
			}
			tx++;
		}
		if (tx > x)
			x = tx;
		y++;
	}

	arrSize = {y, x};

	std::sort(itALL(Sheeps));
	std::sort(itALL(Ducks));
	std::sort(itALL(Hides));
	Sheeps.erase(std::unique(itALL(Sheeps)), Sheeps.end());
	Ducks.erase(std::unique(itALL(Ducks)), Ducks.end());
	Hides.erase(std::unique(itALL(Hides)), Hides.end());

	constexpr std::array<std::pair<int, int>, 8> dir = {{
	    {2, -1},  // down-left
	    {2, 1},   // down-right
	    {1, 2},   // right-down
	    {-1, 2},  // right-up
	    {-2, 1},  // up-right
	    {-2, -1}, // up-left
	    {-1, -2}, // left-up
	    {1, -2}   // left-down
	}};

	int round = 20;
	std::queue<std::tuple<int, int>> q;
	q.push(Ducks[0]);

	ll sum = 0;

	for (int r = 0; r <= round; ++r) {
		auto qT = q;
		q = std::queue<std::tuple<int, int>>();
		std::vector<std::tuple<int, int>> nDucks;

		while (!qT.empty()) {
			auto [cy, cx] = qT.front();
			qT.pop();

			bool isSheep = std::binary_search(itALLc(Sheeps), std::make_tuple(cy, cx));
			bool isHide = std::binary_search(itALLc(Hides), std::make_tuple(cy, cx));

			if (!isHide && isSheep) {
				Sheeps.erase(std::find(itALL(Sheeps), std::make_tuple(cy, cx)));
				sum++;
			}

			for (const auto &[dy, dx] : dir) {
				int ny = cy + dy;
				int nx = cx + dx;

				if (ny < 0 || ny >= arrSize.first || nx < 0 || nx >= arrSize.second)
					continue;

				if (std::find(itALL(nDucks), std::make_tuple(ny, nx)) == nDucks.end()) {
					nDucks.push_back({ny, nx});
					q.push({ny, nx});
				}
			}
		}

		std::sort(itALL(nDucks));
		for (auto it = Sheeps.begin(); r && it != Sheeps.end();) {
			auto &[cy, cx] = *it;
			cy++;
			bool isDuck = std::binary_search(itALL(Ducks), *it);
			bool isHide = std::binary_search(itALL(Hides), *it);

			if (isDuck && !isHide) {
				Sheeps.erase(it);
				sum++;
			} else {
				++it;
			}
		}
		Ducks.swap(nDucks);
	}

	std::cout << "Answer: " << sum << std::endl;

	auto end = std::chrono::high_resolution_clock::now();
	auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
	auto sec = std::chrono::duration_cast<std::chrono::duration<double>>(end - start).count();

	std::cout << "Elapsed time: " << ms << " ms (" << sec << " seconds)\n";
	return 0;
}
