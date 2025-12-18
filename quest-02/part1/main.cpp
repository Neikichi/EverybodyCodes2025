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

	CNB cnbPos(0, 0);

	int cycle = 3;

	for (int i = 0; i < cycle; i++) {
		cnbPos = cnbPos * cnbPos;
		cnbPos = cnbPos / CNB(10, 10);
		cnbPos = cnbPos + numA;
	}

	std::cout << std::format("Answer: [{}, {}]", cnbPos.x, cnbPos.y) << std::endl;

	auto end = std::chrono::high_resolution_clock::now();
	auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
	auto sec = std::chrono::duration_cast<std::chrono::duration<double>>(end - start).count();

	std::cout << "Elapsed time: " << ms << " ms (" << sec << " seconds)\n";
	return 0;
}
