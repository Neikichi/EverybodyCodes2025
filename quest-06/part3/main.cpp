#include <bits/stdc++.h>

typedef long long ll;

int main() {

	std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
	std::vector<ll> tentAll;
	std::string nList;

	std::ifstream file("notes.txt");
	std::string line;
	while (std::getline(file, line)) {
		nList += line;
	}

	for (auto it = nList.begin(); it != nList.end(); ++it) {
		if (std::islower(*it)) {
			ll mCount = 0;

			auto itr = it;
			for (int n = 0; n < 1000; ++n) {
				if (++itr == nList.end())
					itr = nList.begin();
				if (*itr == std::toupper(*it))
					mCount++;
			}

			auto itl = it;
			for (int n = 0; n < 1000; ++n) {
				if (itl == nList.begin())
					itl = nList.end();
				--itl;
				if (*itl == std::toupper(*it))
					mCount++;
			}

			tentAll.push_back(mCount);
		}
	}

	ll midbefore = std::accumulate(tentAll.begin(), tentAll.end(), 0LL);
	ll midsum = std::accumulate(tentAll.begin(), tentAll.end(), 0LL) * 998;
	tentAll.clear();

	for (auto it = nList.begin(); it != nList.end(); ++it) {
		if (std::islower(*it)) {
			ll mCount = 0;

			auto itr = it;
			for (int n = 0; n < 1000; ++n) {
				if (++itr == nList.end())
					itr = nList.begin();
				if (*itr == std::toupper(*it))
					mCount++;
			}

			auto itl = it;
			for (int n = 0; n < 1000; ++n) {
				if (itl == nList.begin())
					break;
				--itl;
				if (*itl == std::toupper(*it))
					mCount++;
			}

			tentAll.push_back(mCount);
		}
	}

	for (auto it = nList.begin(); it != nList.end(); ++it) {
		if (std::islower(*it)) {
			ll mCount = 0;

			auto itr = it;
			for (int n = 0; n < 1000; ++n) {
				if (++itr == nList.end())
					break;
				if (*itr == std::toupper(*it))
					mCount++;
			}

			auto itl = it;
			for (int n = 0; n < 1000; ++n) {
				if (itl == nList.begin())
					itl = nList.end();
				--itl;
				if (*itl == std::toupper(*it))
					mCount++;
			}

			tentAll.push_back(mCount);
		}
	}

	ll sum = std::accumulate(tentAll.begin(), tentAll.end(), 0LL) + midsum;

	std::cout << "Answer: " << sum << std::endl;
	std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
	auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count();
	std::cout << "Time taken: " << duration << " ms (" << duration / 1000.0 << " s)" << std::endl;
	// 1666147626
	return 0;
}
