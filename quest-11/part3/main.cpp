#include <bits/stdc++.h>

typedef long long ll;

int main() {

	auto start = std::chrono::high_resolution_clock::now();
	std::vector<ll> arr;

	std::ifstream file("notes.txt");
	std::string line;
	while (std::getline(file, line)) {
		arr.push_back(std::stoll(line));
	}

	ll nSum = std::accumulate(arr.begin(), arr.end(), 0LL);
	ll average = nSum / arr.size();
	ll sum = 0;

	for (auto &v : arr) {
		if (v < average) {
			sum += (average - v);
		}
	}

	std::cout << "Answer: " << sum << std::endl;

	auto end = std::chrono::high_resolution_clock::now();
	auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
	auto sec = std::chrono::duration_cast<std::chrono::duration<double>>(end - start).count();

	std::cout << "Elapsed time: " << ms << " ms (" << sec << " seconds)\n";
	return 0;
}
