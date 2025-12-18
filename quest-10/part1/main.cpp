#include <bits/stdc++.h>

typedef long long ll;

#define rnc(y, x) ((y) * arrSize.second + (x))
#define gRow(rnc) ((rnc) / arrSize.second)
#define gCol(rnc) ((rnc) % arrSize.second)
#define itALL(v) v.begin(), v.end()
#define itALLc(v) v.cbegin(), v.cend()

int main() {

	auto start = std::chrono::high_resolution_clock::now();
	std::vector<std::tuple<char, int, int>> arr;

	ll x = 0, y = 0, tx = 0;

	std::pair<ll, ll> arrSize, dStart;

	std::ifstream file("notes.txt");
	std::string line;
	while (std::getline(file, line)) {
		tx = 0;
		for (char &ch : line) {
			if (ch == 'S') {
				arr.push_back(std::make_tuple(ch, 0, 0));
			} else if (ch == 'D') {
				arr.push_back(std::make_tuple('.', 1, 0));
				dStart = {y, tx};
			} else {
				arr.push_back(std::make_tuple(ch, 0, 0));
			}
			tx++;
		}
		if (tx > x)
			x = tx;
		y++;
	}

	arrSize = {y, x};
	ll dPos = rnc(dStart.first, dStart.second);

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

	int round = 4;
	std::queue<ll> q;
	q.push(dPos);

	ll sum = 0;

	for (int r = 0; r <= round; ++r) {
		auto qT = q;
		q = std::queue<ll>();

		while (!qT.empty()) {
			ll curr = qT.front();
			qT.pop();

			auto &[cch, cd, cvis] = arr[curr];
			sum += (cvis == 0 && cch == 'S') ? 1 : 0;
			cvis = 1;

			for (const auto &[dy, dx] : dir) {
				int ny = gRow(curr) + dy;
				int nx = gCol(curr) + dx;

				if (ny < 0 || ny > arrSize.first || nx < 0 || nx > arrSize.second)
					continue;

				ll npos = rnc(ny, nx);
				auto &[nch, nd, nvis] = arr[npos];

				if (!nvis) {
					q.push(npos);
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
