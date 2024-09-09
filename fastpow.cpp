//求 base^n 快速冪

const long long MOD = 1000000007;

long long fp (long long base, long long n) {
    long long res = 1;
    while (n > 0) {
        if (n & 1) {
            res = res * base % MOD;
        }
        base = base * base % MOD;
        n >>= 1;
    }
    return res;
}
