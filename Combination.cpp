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