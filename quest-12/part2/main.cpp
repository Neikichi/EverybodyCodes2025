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

	ll row = gRow(pos);
	ll col = gCol(pos);
	ll res = 1;

	if (row + 1 < arrSize.first) {
		ll down = rnc(row + 1, col);
		if (arr[down] <= arr[pos])
			res += dfs(down, arr, arrSize, visited);
	}
	if (col + 1 < arrSize.second) {
		ll right = rnc(row, col + 1);
		if (arr[right] <= arr[pos])
			res += dfs(right, arr, arrSize, visited);
	}

	if (row - 1 >= 0) {
		ll up = rnc(row - 1, col);
		if (arr[up] <= arr[pos])
			res += dfs(up, arr, arrSize, visited);
	}

	if (col - 1 >= 0) {
		ll left = rnc(row, col - 1);
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

	std::vector<bool> visited(arr.size(), false);
	ll ssum = dfs(0, arr, arrSize, visited);
	ll esum = dfs(arr.size() - 1, arr, arrSize, visited);
	ll sum = ssum + esum;

	std::cout << "Answer: " << sum << std::endl;

	auto end = std::chrono::high_resolution_clock::now();
	auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
	auto sec = std::chrono::duration_cast<std::chrono::duration<double>>(end - start).count();

	std::cout << "Elapsed time: " << ms << " ms (" << sec << " seconds)\n";
	return 0;
}
