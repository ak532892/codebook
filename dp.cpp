// top-down 改成 button-up

// 以下都沒辦法再改成button-up
// 理論上會更快一點
// 可能還能做一點空間優化再次加速

// 速度最最快, 但空間不一定夠 (可能 MLE 要算一下)

int dp[2][1000][1000];
memset(dp, -1, sizeof(dp));
if (dp[i][j][k] != -1) { return dp[i][j][k]; }

// 速度最快, 但空間不一定夠 (可能 MLE 要算一下)

auto dp = vector(i, vector(j, vector<int>(k, -1)));
if (dp[i][j][k] != -1) { return dp[i][j][k]; }

// 速度次快, 通常空間會夠 (要算一下 BIT 存儲的空間夠不夠塞64 BIT)

long long key = (long long) i << 36 | (long long) j << 32 | k;
unordered_map<long long, int> dp;
if (dp.contains(key)) { return dp[key]; }

// 速度次次快 (?), 通常空間也會夠

struct state {
    int i;
    int j;
    int k;
    int l;
};
auto cmp = [](const state& a, const state& b) {
    return a.i < b.i || (a.i == b.i && a.j < b.j) ||
        (a.i == b.i && a.j == b.j && a.k < b.k) || 
        (a.i == b.i && a.j == b.j && a.k == b.k && a.l < b.l);
};

map<state, int, decltype(cmp)> dp(cmp); 

// 速度最慢, 通常空間也夠, 趕時間再用這招

map<array<int, 4>, int> dp;
