#include <bits/stdc++.h>
#include <boost/functional/hash.hpp>

typedef long long ll;
using C = std::complex<ll>;

#define itN(x) x.begin(), x.end()
#define itNr(x) x.rbegin(), x.rend()
#define itNc(x) x.cbegin(), x.cend()
#define itNrc(x) x.crbegin(), x.crend()

void printBoard(const std::vector<std::string> &board) {
	for (const auto &line : board) {
		std::cout << line << std::endl;
	}
}

struct pqCmp {
	bool operator()(const auto &a, const auto &b) const {
		auto &[da, pa] = a;
		auto &[db, pb] = b;

		if (da == db) {
			if (pa.real() == pb.real()) {
				return pa.imag() > pb.imag();
			}
			return pa.real() > pb.real();
		}
		return da > db;
	}
};

ll djikstra(const auto &board,
            const auto &lavaPos,
            const auto &loopPos,
            const auto &goalPos,
            auto &maxX,
            auto &maxY,
            const auto &NESW,
            char turns,
            ll timeLimit,
            ll costDist = 0) {

	std::priority_queue<std::pair<ll, C>, std::vector<std::pair<ll, C>>, pqCmp> pq;
	pq.push({costDist, loopPos});

	std::unordered_set<C, boost::hash<C>> visited;

	while (!pq.empty()) {
		auto [dist, curr] = pq.top();
		pq.pop();

		if (curr == goalPos) {
			return dist;
		}

		for (const auto &dir : NESW) {
			auto next = curr + dir;

			ll x = next.real(), y = next.imag();
			if (x < 0 || x >= maxX || y < 0 || y >= maxY)
				continue;

			if (turns == 'L' && x > lavaPos.real())
				continue;
			else if (turns == 'R' && y > lavaPos.real() && x < lavaPos.real())
				continue;

			if (!std::isdigit(board[y][x]) && board[y][x] != 'S')
				continue;

			ll cost = (board[y][x] == 'S' ? 0 : board[y][x] - '0');
			if (dist + cost >= timeLimit)
				continue;

			if (!visited.insert(next).second)
				continue;

			pq.push({dist + cost, next});
		}
	}
	return -1;
}

ll djikstraLoop(const auto &board,
                const auto &lavaPos,
                const auto &loopPos,
                auto &maxX,
                auto &maxY,
                const auto &NESW,
                ll timeLimit) {

	C botStart = [&board, &lavaPos, &maxY]() {
		ll x = lavaPos.real(), y = lavaPos.imag();
		for (ll yy = y + 1; yy < maxY; yy++) {
			if (std::isdigit(board[yy][x])) {
				return C(x, yy);
			}
		}
		return C(-1, -1);
	}();

	if (botStart == C(-1, -1)) {
		std::cerr << "No valid bot start found below lava at: (" << lavaPos.real() << ", "
		          << lavaPos.imag() << ")\n";
		return -1;
	}

	ll leftLoop = djikstra(board, lavaPos, loopPos, botStart, maxX, maxY, NESW, 'L', timeLimit, 0);
	if (leftLoop == -1) {
		return -1;
	}
	ll rightLoop =
	    djikstra(board, lavaPos, botStart, loopPos, maxX, maxY, NESW, 'R', timeLimit, leftLoop);
	if (rightLoop == -1) {
		return -1;
	}

	// ll totalLoop = leftLoop + rightLoop;
	if (rightLoop <= timeLimit) {
		return rightLoop;
	}
	return -1;
}

int main() {
	auto start = std::chrono::high_resolution_clock::now();

	std::vector<std::string> board;

	ll maxY = 0, maxX = 0;
	C stPos, stLoop;

	std::ifstream file("notes.txt");

	for (auto [yy, line] : std::views::enumerate(std::views::istream<std::string>(file))) {
		maxX = std::max(maxX, (ll)line.size());
		if (line.find('@') != std::string::npos) {
			stPos = C(line.find('@'), yy);
		}
		if (line.find('S') != std::string::npos)
			stLoop = C(line.find('S'), yy);
		board.emplace_back(line);
		maxY++;
	}

	// directions
	C N(0, 1);
	C E(1, 0);
	C S(0, -1);
	C W(-1, 0);
	C NESW[4] = {N, E, S, W};

	ll sum = 0;

	ll maxRadius =
	    std::max({stPos.real(), maxX - 1 - stPos.real(), stPos.imag(), maxY - 1 - stPos.imag()});
	std::pair<ll, ll> maxR(-1, -1);

	ll loopSum = 0, loopRadius = -1;
	for (ll r = 1; r <= maxRadius; r++) {

		if ((loopSum = djikstraLoop(board, stPos, stLoop, maxX, maxY, NESW, r * 30)) > 0) {
			break;
		}
		for (ll y = 0; y < maxY; y++) {
			for (ll x = 0; x < maxX; x++) {
				C currPos(x, y);
				if (currPos == stPos || !std::isdigit(board[y][x]))
					continue;
				ll dPos = std::norm(currPos - stPos);
				if (dPos <= r * r && dPos > (r - 1) * (r - 1)) {
					board[y][x] = '.';
				}
			}
		}

		loopRadius = r;
	}
	std::cout << "Answer: " << (loopSum * loopRadius) << std::endl;

	auto end = std::chrono::high_resolution_clock::now();
	auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
	auto sec = std::chrono::duration_cast<std::chrono::duration<double>>(end - start).count();

	std::cout << "Elapsed time: " << ms << " ms (" << sec << " seconds)\n";
	return 0;
}
