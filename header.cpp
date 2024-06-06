// =======================
static const int __ = []() { std::ios::sync_with_stdio(false); std::cin.tie(nullptr); std::cout.tie(nullptr); return 0; }();
#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")

template<typename A> string to_string(A* ptr) { stringstream ss; ss << "0x" << std::setw(16) << std::setfill ('0') << std::hex << (uint64_t)(uintptr_t)ptr; return ss.str(); }
string to_string(char c) { return ((string)"'"+c)+ "'"; }
template <typename A, typename B> string to_string(pair<A, B> p);
template <typename A, typename B, typename C> string to_string(tuple<A, B, C> p);
template <typename A, typename B, typename C, typename D> string to_string(tuple<A, B, C, D> p);
string to_string(const string& s) { return '"' + s + '"'; }
string to_string(const char* s) { return to_string((string) s); }
string to_string(bool b) { return (b ? "true" : "false"); }
string to_string(vector<bool> v) {
    bool first = true; string res = "{";
	for (int i = 0; i < static_cast<int>(v.size()); i++) { if (!first) { res += ", "; } first = false; res += to_string(v[i]); }
	res += "}"; return res;
}
template <size_t N> string to_string(bitset<N> v) { string res = ""; for (size_t i = 0; i < N; i++) { res += static_cast<char>('0' + v[i]); } return res; }
template <typename A> string to_string(A v) {
	bool first = true; string res = "{";
	for (const auto &x : v) {
		if (!first) { res += ", "; }
		first = false; res += to_string(x);
	}
	res += "}"; return res;
}
template <typename A, typename B> string to_string(pair<A, B> p) { return "(" + to_string(p.first) + ", " + to_string(p.second) + ")"; }
template <typename A, typename B, typename C> string to_string(tuple<A, B, C> p) { return "(" + to_string(get<0>(p)) + ", " + to_string(get<1>(p)) + ", " + to_string(get<2>(p)) + ")"; }
template <typename A, typename B, typename C, typename D>
string to_string(tuple<A, B, C, D> p) { return "(" + to_string(get<0>(p)) + ", " + to_string(get<1>(p)) + ", " + to_string(get<2>(p)) + ", " + to_string(get<3>(p)) + ")"; }
void debug_out() { cout << endl; }
template <typename Head, typename... Tail> void debug_out(Head H, Tail... T) { cout << " " << to_string(H); debug_out(T...); }

#include <ext/pb_ds/tree_policy.hpp>
#include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;
template<typename T> using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

using ll = long long;
using ld = long double;

#define pb push_back
#define pp pop_back
#define mp make_pair
#define x first
#define y second
#define pii pair<int, int>
#define pll pair<ll, ll>
#define pdd pair<ld, ld>

#define lb lower_bound
#define ub upper_bound
#define all(x) x.begin(), x.end()
#define rall(x) x.rbegin(), x.rend()
#define sz(x) (int)x.size()

#define ZERO(x) memset(x, 0, sizeof(x))
#define MINUS(x) memset(x, 0xff, sizeof(x))
#define MAX(x) *max_element(all(x))
#define MIN(x) *min_element(all(x))
#define sum(x) accumulate(x.begin(), x.end(), 0LL)

const ll MOD = 1e9 + 7;
const int INF = 0x3f3f3f3f;
const long long LINF = 0x3f3f3f3f3f3f3f3fLL;
const int dx[] = {0, 1, 0, -1, 1, 1, -1, -1};
const int dy[] = {1, 0, -1, 0, 1, -1, -1, 1};

#if 1
#define dbg(...) cout << "[" << #__VA_ARGS__ << "]:", debug_out(__VA_ARGS__)
#else
#define dbg(...) 42
#endif
// =======================
