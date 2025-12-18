#include <bits/stdc++.h>

typedef long long ll;

#define rnc(y, x) ((y) * arrSize.second + (x))
#define gRow(rnc) ((rnc) / arrSize.second)
#define gCol(rnc) ((rnc) % arrSize.second)
#define itALL(v) v.begin(), v.end()
#define itALLc(v) v.cbegin(), v.cend()

bool outOfBounds(ll pos, std::pair<ll, ll> &arrSize) {
	if (gRow(pos) < 0 || gRow(pos) >= arrSize.first || gCol(pos) < 0 || gCol(pos) >= arrSize.second)
		return true;
	return false;
}

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

ll bfs(ll pos, std::vector<ll> &arr, std::pair<ll, ll> &arrSize, std::vector<bool> &visited) {
	std::queue<ll> q;
	q.push(pos);
	visited[pos] = true;
	ll res = 1;
	while (!q.empty()) {
		ll curr = q.front();
		q.pop();
		ll row = gRow(curr);
		ll col = gCol(curr);

		std::vector<ll> next;

		if (row + 1 < arrSize.first)
			next.push_back(rnc(row + 1, col));
		if (col + 1 < arrSize.second)
			next.push_back(rnc(row, col + 1));
		if (row - 1 >= 0)
			next.push_back(rnc(row - 1, col));
		if (col - 1 >= 0)
			next.push_back(rnc(row, col - 1));

		for (ll idx : next) {
			if (!visited[idx] && arr[idx] <= arr[curr]) {
				visited[idx] = true;
				q.push(idx);
				res++;
			}
		}
	}
	return res;
}

ll getVisitedSum(std::vector<bool> &visited) {
	ll sum = 0;
	for (bool v : visited) {
		if (v)
			sum++;
	}
	return sum;
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
	auto bfsVisited = visited;
	ll sum = dfs(0, arr, arrSize, visited);

	std::cout << "Answer: " << sum << std::endl;
	std::cout << "BFS: " << bfs(0, arr, arrSize, bfsVisited) << std::endl;

	auto end = std::chrono::high_resolution_clock::now();
	auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
	auto sec = std::chrono::duration_cast<std::chrono::duration<double>>(end - start).count();

	std::cout << "Elapsed time: " << ms << " ms (" << sec << " seconds)\n";
	return 0;
}
