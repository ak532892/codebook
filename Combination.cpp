========verson1========
    
const int MOD = 1e9 + 7, maxCombSize1 = size + 1, maxCombSize2 = size + 1;
long long comb[maxCombSize1][maxCombSize2];
int combPrecompute = []() {
    comb[0][0] = 1;
    for (int i = 1; i < maxCombSize1; ++i) {
        comb[i][0] = 1;
        for (int j = 1; j < maxCombSize2; ++j)
            comb[i][j] = (comb[i - 1][j] + comb[i - 1][j - 1]) % MOD;
    }
    return 0;
}();

cout<<comb[n][k];

========verson2========
    
const int MOD = 1'000'000'007;
const int MX = 2001;

long long q_pow(long long x, int n) {
    long long res = 1;
    for (; n > 0; n /= 2) {
        if (n % 2) {
            res = res * x % MOD;
        }
        x = x * x % MOD;
    }
    return res;
}

// 组合数模板
long long fac[MX], inv_fac[MX];

auto init = [] {
    fac[0] = 1;
    for (int i = 1; i < MX; i++) {
        fac[i] = fac[i - 1] * i % MOD;
    }
    inv_fac[MX - 1] = q_pow(fac[MX - 1], MOD - 2);
    for (int i = MX - 1; i > 0; i--) {
        inv_fac[i - 1] = inv_fac[i] * i % MOD;
    }
    return 0;
}();

long long comb(int n, int k) {
    return fac[n] * inv_fac[k] % MOD * inv_fac[n - k] % MOD;
}

cout<<comb(n, k);
