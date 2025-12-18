#include <bits/stdc++.h>
#include <boost/functional/hash.hpp>

typedef long long ll;
using C = std::complex<ll>;

#define itN(x) x.begin(), x.end()
#define itNr(x) x.rbegin(), x.rend()
#define itNc(x) x.cbegin(), x.cend()
#define itNrc(x) x.crbegin(), x.crend()

struct State {
	std::unordered_set<C, boost::hash<C>> sheepPos;
	C duckPos;
	bool turn;

	bool operator==(const State &other) const {
		return sheepPos == other.sheepPos && duckPos == other.duckPos && turn == other.turn;
	}

	bool noSheep() const {
		return sheepPos.empty();
	}
};

struct StateHash {
	std::size_t operator()(const State &s) const {
		std::size_t seed = 0;

		auto hashSet = [&](const auto &st) {
			std::vector<C> v(st.begin(), st.end());
			std::sort(v.begin(), v.end(), [](const C &a, const C &b) {
				if (a.real() != b.real())
					return a.real() < b.real();
				return a.imag() < b.imag();
			});
			for (const auto &pos : v) {
				boost::hash_combine(seed, boost::hash_value(pos));
			}
		};

		hashSet(s.sheepPos);
		boost::hash_combine(seed, boost::hash_value(s.duckPos));
		boost::hash_combine(seed, std::hash<bool>()(s.turn));

		return seed;
	}
};

int main() {
	auto chronoSt = std::chrono::high_resolution_clock::now();

	constexpr C UR(1, -1);  // up right
	constexpr C UL(-1, -1); // up left
	constexpr C DR(1, 1);   // down right
	constexpr C DL(-1, 1);  // down left
	constexpr C N(0, -1);   // up
	constexpr C S(0, 1);    // down
	constexpr C E(1, 0);    // right
	constexpr C W(-1, 0);   // left

	constexpr auto dirz = std::array<C, 8>{N, E, S, W, UR, DR, DL, UL};

	constexpr std::array<C, 8> duckMoves = {
	    C{2, 1}, C{1, 2}, C{-1, 2}, C{-2, 1}, C{-2, -1}, C{-1, -2}, C{1, -2}, C{2, -1}};

	std::ifstream file("notes.txt");
	if (!file) {
		std::cerr << "Error: cannot open notes.txt\n";
		return 1;
	}

	std::unordered_set<C, boost::hash<C>> sheepPos, hidePos;
	C duckPos;
	ll maxX = 0, maxY = 0;

	for (auto [yy, line] : std::views::enumerate(std::views::istream<std::string>(file))) {
		for (auto [xx, ch] : std::views::enumerate(line)) {
			C pos(xx, yy);
			if (ch == 'S') {
				sheepPos.insert(pos);
			} else if (ch == 'D') {
				duckPos = (pos);
			} else if (ch == '#') {
				hidePos.insert(pos);
			}
		}
		if (line.size() > maxX) {
			maxX = line.size();
		}
		if (yy + 1 > maxY) {
			maxY = yy + 1;
		}
	}

	ll sum = 0;

	auto createState = [](const auto &sheepPos, const auto &duckPos, bool turn) {
		return State{sheepPos, duckPos, turn};
	};

	std::unordered_map<State, ll, StateHash> memo;

	std::function<ll(State)> dfs = [&](State currState) {
		if (currState.noSheep()) {
			return 1LL;
		}

		if (memo.count(currState)) {
			return memo[currState];
		}

		ll localSum = 0;

		// turn: true = duck, false = sheep
		if (currState.turn) {
			for (const auto &move : duckMoves) {
				C nPos = currState.duckPos + move;
				if (nPos.real() < 0 || nPos.real() >= maxX || nPos.imag() < 0 || nPos.imag() >= maxY) {
					continue;
				}

				if (currState.sheepPos.count(nPos) && !hidePos.count(nPos)) {
					auto newState = currState;
					newState.sheepPos.erase(nPos);
					newState.duckPos = nPos;
					newState.turn = !currState.turn;
					localSum += dfs(newState);
				} else {
					auto newState = currState;
					newState.duckPos = nPos;
					newState.turn = !currState.turn;
					localSum += dfs(newState);
				}
			}
		} else {
			bool canMove = false;
			for (const auto &curPos : currState.sheepPos) {
				C nPos = curPos + S;
				if (nPos.imag() >= maxY) {
					canMove = true;
					continue;
				}

				if (currState.duckPos == nPos && !hidePos.count(nPos)) {
					continue;
				}
				canMove = true;
				auto newState = currState;
				newState.sheepPos.erase(curPos);
				newState.sheepPos.insert(nPos);
				newState.turn = !currState.turn;
				localSum += dfs(newState);
			}
			if (!canMove) {
				auto newState = currState;
				newState.turn = !currState.turn;
				localSum += dfs(newState);
			}
		}
		memo[currState] = localSum;
		return localSum;
	};

	sum = dfs(createState(sheepPos, duckPos, false));

	std::cout << "Answer: " << sum << "\n";

	{
		// End computation time
		auto chronoEnd = std::chrono::high_resolution_clock::now();
		auto chronoMS =
		    std::chrono::duration_cast<std::chrono::milliseconds>(chronoEnd - chronoSt).count();
		auto sec =
		    std::chrono::duration_cast<std::chrono::duration<double>>(chronoEnd - chronoSt).count();

		std::cout << "Elapsed time: " << chronoMS << " ms (" << sec << " seconds)\n";
	}
	return 0;
}
