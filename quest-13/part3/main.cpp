#include <bits/stdc++.h>

typedef long long ll;

std::vector<std::string> splitString(const std::string &str, char c) {
	std::vector<std::string> ret;
	std::string word;
	for (char ch : str) {
		if (ch == c && !word.empty()) {
			ret.push_back(word);
			word.clear();
		} else {
			word += ch;
		}
	}
	if (!word.empty()) {
		ret.push_back(word);
		word.clear();
	}
	return ret;
}

#define itALL(v) v.begin(), v.end()
#define itALLc(v) v.cbegin(), v.cend()

int main() {

	auto start = std::chrono::high_resolution_clock::now();
	std::vector<std::pair<ll, ll>> arr;
	std::vector<ll> clockArr;

	std::ifstream file("notes.txt");
	std::string line;
	while (std::getline(file, line)) {
		auto split = splitString(line, '-');
		ll first = std::stoll(split[0]);
		ll second = std::stoll(split[1]);
		arr.push_back({first, second});
	}

	clockArr.push_back(1);
	for (int i = 0; i < arr.size(); i++) {
		if (i % 2 == 0) {
			auto &[first, second] = arr[i];
			for (int j = first; j <= second; j++) {
				clockArr.push_back(j);
			}
		}
	}

	for (int i = arr.size() - 1; i > 0; i--) {
		if (i % 2 != 0) {
			auto &[first, second] = arr[i];
			for (int j = second; j >= first; j--) {
				clockArr.push_back(j);
			}
		}
	}

	ll idx = 202520252025LL % clockArr.size();

	std::cout << "Final Index: " << idx << " Value: " << clockArr[idx] << std::endl;

	// std::cout << "Answer: " << sum << std::endl;

	auto end = std::chrono::high_resolution_clock::now();
	auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
	auto sec = std::chrono::duration_cast<std::chrono::duration<double>>(end - start).count();

	std::cout << "Elapsed time: " << ms << " ms (" << sec << " seconds)\n";
	return 0;
}
