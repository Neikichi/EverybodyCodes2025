#include <bits/stdc++.h>

typedef long long ll;

#define itALL(v) v.begin(), v.end()
#define itALLc(v) v.cbegin(), v.cend()

int main() {

	auto start = std::chrono::high_resolution_clock::now();
	std::vector<ll> arr;
	std::vector<ll> clockArr;

	std::ifstream file("notes.txt");
	std::string line;
	while (std::getline(file, line)) {
		arr.push_back(std::stoll(line));
	}

	clockArr.push_back(1);
	for (int i = 0; i < arr.size(); i++) {
		if (i % 2 == 0) {
			clockArr.push_back(arr[i]);
		}
	}

	for (int i = arr.size() - 1; i > 0; i--) {
		if (i % 2 != 0) {
			clockArr.push_back(arr[i]);
		}
	}

	int idx = 0;
	for (int i = 0; i < 2025 + 1; i++) {
		idx = i % clockArr.size();
	}

	std::cout << "Final Index: " << idx << " Value: " << clockArr[idx] << std::endl;

	// std::cout << "Answer: " << sum << std::endl;

	auto end = std::chrono::high_resolution_clock::now();
	auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
	auto sec = std::chrono::duration_cast<std::chrono::duration<double>>(end - start).count();

	std::cout << "Elapsed time: " << ms << " ms (" << sec << " seconds)\n";
	return 0;
}
