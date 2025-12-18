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

	int rounds = 10;
	std::vector<std::vector<ll>> states;

	// phase 1
	bool ableToContinue = true;
	while (ableToContinue) {
		ableToContinue = false;
		for (int i = 1; i < arr.size(); i++) {
			if (arr[i] > arr[i - 1] || arr[i] == arr[i - 1]) {
				continue;
			}
			ableToContinue = true;
			arr[i]++;
			arr[i - 1]--;
		}
		if (ableToContinue) {
			states.push_back(arr);
		} else {
			break;
		}
	}

	ableToContinue = true;
	while (ableToContinue) {
		ableToContinue = false;
		for (int i = 1; i < arr.size(); i++) {
			if (arr[i] == arr[i - 1]) {
				continue;
			}
			ableToContinue = true;
			if (arr[i] > arr[i - 1]) {
				arr[i]--;
				arr[i - 1]++;
			} else {
				arr[i]++;
				arr[i - 1]--;
			}
		}
		if (ableToContinue) {
			states.push_back(arr);
		} else {
			break;
		}
	}

	ll sum = 0;

	for (int i = 0; i < states[rounds - 1].size(); i++) {
		sum += (i + 1) * states[rounds - 1][i];
	}

	std::cout << "Answer: " << sum << std::endl;

	auto end = std::chrono::high_resolution_clock::now();
	auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
	auto sec = std::chrono::duration_cast<std::chrono::duration<double>>(end - start).count();

	std::cout << "Elapsed time: " << ms << " ms (" << sec << " seconds)\n";
	return 0;
}
