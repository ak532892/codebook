template <typename T>
class prefixSumMatrix {
public:
    vector<vector<T>> prefix;
    int m, n;
    
    prefixSumMatrix(const vector<vector<int>>& matrix) {
        init(matrix);
    }
    prefixSumMatrix(const vector<vector<long long>>& matrix) {
        init(matrix);
    }
    prefixSumMatrix(const vector<vector<char>>& matrix) {
        init(matrix);
    }
    prefixSumMatrix() {}
    
    void init(const vector<vector<int>>& matrix) {
        m = matrix.size(), n = matrix[0].size();
        prefix = vector(m + 1, vector<T>(n + 1, 0));
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                prefix[i + 1][j + 1] = prefix[i + 1][j] + prefix[i][j + 1] - prefix[i][j] + matrix[i][j];
            }
        }
    }
    void init(const vector<vector<long long>>& matrix) {
        m = matrix.size(), n = matrix[0].size();
        prefix = vector(m + 1, vector<T>(n + 1, 0));
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                prefix[i + 1][j + 1] = prefix[i + 1][j] + prefix[i][j + 1] - prefix[i][j] + matrix[i][j];
            }
        }
    }
    void init(const vector<vector<char>>& matrix) {
        m = matrix.size(), n = matrix[0].size();
        prefix = vector(m + 1, vector<T>(n + 1, 0));
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                prefix[i + 1][j + 1] = prefix[i + 1][j] + prefix[i][j + 1] - prefix[i][j] + matrix[i][j] - '0';
            }
        }
    }

    // 0-index
    // sum region of top-left (r1,c1) to botton-right (r2,c2)
    T sumRegion(int r1, int c1, int r2, int c2) {
        return prefix[min(m, r2 + 1)][min(n, c2 + 1)] - prefix[min(m, r2 + 1)][max(0, c1)] - prefix[max(0, r1)][min(n, c2 + 1)] + prefix[max(0, r1)][max(0, c1)];
    }
};

int m = matrix.size(), n = matrix[0].size();
prefixSumMatrix<long long> prefix(matrix);
//prefix.init(matrix);
prefix.sumRegion(r1, c1, r2, c2);
