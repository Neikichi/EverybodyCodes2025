#include <bits/stdc++.h>

typedef long long ll;

#define rnc(y, x) ((y) * arrSize.second + (x))
#define gRow(rnc) ((rnc) / arrSize.second)
#define gCol(rnc) ((rnc) % arrSize.second)
#define itALL(v) v.begin(), v.end()
#define itALLc(v) v.cbegin(), v.cend()

ll dfs(ll pos, std::vector<ll> &arr, std::pair<ll, ll> &arrSize, std::vector<bool> &visited) {

	if (visited[pos])
		return 0;

	visited[pos] = true;

	ll y = gRow(pos);
	ll x = gCol(pos);
	ll res = 1;

	if (y + 1 < arrSize.first) {
		ll down = rnc(y + 1, x);
		if (arr[down] <= arr[pos])
			res += dfs(down, arr, arrSize, visited);
	}
	if (x + 1 < arrSize.second) {
		ll right = rnc(y, x + 1);
		if (arr[right] <= arr[pos])
			res += dfs(right, arr, arrSize, visited);
	}

	if (y - 1 >= 0) {
		ll up = rnc(y - 1, x);
		if (arr[up] <= arr[pos])
			res += dfs(up, arr, arrSize, visited);
	}

	if (x - 1 >= 0) {
		ll left = rnc(y, x - 1);
		if (arr[left] <= arr[pos])
			res += dfs(left, arr, arrSize, visited);
	}

	return res;
}

int main() {

	auto start = std::chrono::high_resolution_clock::now();
	std::vector<ll> arr;

	ll x = 0, y = 0, tx = 0;

	std::pair<ll, ll> arrSize;

	std::ifstream file("notes.txt");
	std::string line;
	while (std::getline(file, line)) {
		tx = 0;
		for (char &ch : line) {
			tx++;
			arr.push_back(ch - '0');
		}
		if (tx > x)
			x = tx;
		y++;
	}

	arrSize = {y, x};

	std::vector<bool> allVisited(arr.size(), false);
	ll sum = 0;

	for (ll i = 0; i < 3; i++) {
		std::vector<bool> maxVisited(arr.size(), false);
		ll maxVal = -1;
		for (ll j = 0; j < arr.size(); j++) {
			std::vector<bool> visited = allVisited;
			ll res = dfs(j, arr, arrSize, visited);
			if (res > maxVal) {
				maxVal = res;
				maxVisited = visited;
			}
		}
		allVisited = maxVisited;
		sum += maxVal;
	}

	std::cout << "Answer: " << sum << std::endl;

	auto end = std::chrono::high_resolution_clock::now();
	auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
	auto sec = std::chrono::duration_cast<std::chrono::duration<double>>(end - start).count();

	std::cout << "Elapsed time: " << ms << " ms (" << sec << " seconds)\n";
	return 0;
}
