#include <bits/stdc++.h>

typedef long long ll;

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

	std::vector<std::string> names;
	std::vector<std::pair<char, ll>> instructions;

	ll maxY = 0, maxX = 0;

	for (auto [yy, line] : std::views::enumerate(std::views::istream<std::string>(file))) {
		if (yy == 0) {
			for (auto word : std::views::split(line, ',')) {
				names.push_back(std::string(itN(word)));
			}
		} else {
			for (auto instruct : std::views::split(line, ',')) {
				auto str = std::string(itN(instruct));
				instructions.push_back({str[0], std::stoll(str.substr(1))});
			}
		}
	}

	for (auto &[dir, step] : instructions) {
		auto it = names.begin();
		if (dir == 'R') {
			it = names.begin() + (std::ranges::distance(names.begin(), it) + step) % names.size();
			std::ranges::swap(names.front(), *it);
		} else {
			it = names.begin() +
			    (std::ranges::distance(names.begin(), it) + names.size() - step % names.size()) %
			        names.size();
			std::ranges::swap(names.front(), *it);
		}
	}

	std::cout << std::format("Answer: {}", names.front()) << std::endl;

	auto end = std::chrono::high_resolution_clock::now();
	auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
	auto sec = std::chrono::duration_cast<std::chrono::duration<double>>(end - start).count();

	std::cout << "Elapsed time: " << ms << " ms (" << sec << " seconds)\n";
	return 0;
}
