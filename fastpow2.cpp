using ll = long long;
const int MOD = 1e9 + 7;
const int SIZE = 26;
using Matrix = array<array<ll, SIZE>, SIZE>;

// 計算矩陣 a 和 矩陣 b 相乘的結果
Matrix mul(Matrix& a, Matrix& b) {
    Matrix c{};
    for (int i = 0; i < SIZE; i++) {
        for (int k = 0; k < SIZE; k++) {
            if (a[i][k] == 0) {
                continue;
            }
            for (int j = 0; j < SIZE; j++) {
                c[i][j] = (c[i][j] + a[i][k] * b[k][j]) % MOD;
            }
        }
    }
    return c;
}

// 計算 n 個矩陣 a 相乘的結果, 相當於是 [a]^n
Matrix fp2(Matrix a, int n) {
    Matrix res = {};
    for (int i = 0; i < SIZE; i++) {
        res[i][i] = 1; // 單位矩陣, 也可當成是 SIZE*1 其值全為 1 的矩陣
    }
    while (n) {
        if (n & 1) {
            res = mul(res, a);
        }
        a = mul(a, a);
        n >>= 1;
    }
    return res;
}
    
// Matrix mat{};

// for (int i = 0; i < SIZE; ++i) {
//    for (int j = ?; j <= ?; ++j) {
//        mat[i][j]++;
//    }
// }

// mat = fp2(mat, t);

// for (int i = 0; i < SIZE; i++) {
//     sum = (sum + reduce(mat[i].begin(), mat[i].end(), 0LL)) % MOD;
// }
