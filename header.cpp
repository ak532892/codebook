// =======================
#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")

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
// =======================