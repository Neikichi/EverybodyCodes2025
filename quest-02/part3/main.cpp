#include <bits/stdc++.h>

typedef long long ll;
using C = std::complex<ll>;

#define itN(x) x.begin(), x.end()
#define itNr(x) x.rbegin(), x.rend()
#define itNc(x) x.cbegin(), x.cend()
#define itNrc(x) x.crbegin(), x.crend()

struct CNB {
	ll x;
	ll y;

	CNB operator+(const CNB &other) const {
		return CNB(x + other.x, y + other.y);
	}

	CNB operator-(const CNB &other) const {
		return CNB(x - other.x, y - other.y);
	}

	CNB operator*(const CNB &other) const {
		return CNB(x * other.x - y * other.y, x * other.y + y * other.x);
	}

	CNB operator/(const CNB &other) const {
		if (!other.x || !other.y)
			return CNB(0, 0);
		return CNB(x / other.x, y / other.y);
	}
};

int main() {
	auto start = std::chrono::high_resolution_clock::now();

	std::ifstream file("notes.txt");
	if (!file) {
		std::cerr << "Error: cannot open notes.txt\n";
		return 1;
	}

	CNB numA;

	for (auto [yy, line] : std::views::enumerate(std::views::istream<std::string>(file))) {
		std::string str(itN(line));

		int stPos = str.find('[');
		int enPos = str.find(']');
		int comma = str.find(',', stPos);
		numA = CNB({std::stoll(str.substr(stPos + 1, comma - stPos - 1)),
		            std::stoll(str.substr(comma + 1, enPos - comma - 1))});
	}

	CNB endA = numA + CNB(1000, 1000);

	CNB abs = (endA - numA) / CNB(1000, 1000);

	std::vector<C> engraving;

	ll sum = 0;
	for (ll iy = 0; iy <= 1000; ++iy) {
		CNB currY = numA + CNB(0, iy * abs.y);
		for (ll ix = 0; ix <= 1000; ++ix) {
			ll both = iy * 10 + ix;
			CNB currX = currY + CNB(ix * abs.x, 0);
			CNB cycleP = CNB(0, 0);
			int cycle = 100;

			for (int i = 0; i < cycle; i++) {
				cycleP = cycleP * cycleP;
				cycleP = cycleP / CNB(100000, 100000);
				cycleP = cycleP + currX;
				if (std::abs(cycleP.x) > 1000000 || std::abs(cycleP.y) > 1000000) {
					goto nextVal;
				}
			}
			engraving.push_back(C(ix, iy));
			sum++;
		nextVal:;
		}
	}

	std::cout << "Answer: " << sum << std::endl;

	auto end = std::chrono::high_resolution_clock::now();
	auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
	auto sec = std::chrono::duration_cast<std::chrono::duration<double>>(end - start).count();

	std::cout << "Elapsed time: " << ms << " ms (" << sec << " seconds)\n";
	return 0;
}
