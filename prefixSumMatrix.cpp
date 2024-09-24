template <typename T>
class prefixSumMatrix {
public:
    vector<vector<T>> prefix;
    int ROWS, COLS;
    
    prefixSumMatrix() {}
    prefixSumMatrix(const vector<vector<int>>& matrix) {
        init(matrix);
    }
    prefixSumMatrix(const vector<vector<long long>>& matrix) {
        init(matrix);
    }
    prefixSumMatrix(const vector<vector<char>>& matrix) {
        init(matrix);
    }
    
    void init(const vector<vector<int>>& matrix) {
        ROWS = matrix.size(), COLS = matrix[0].size();
        prefix = vector(ROWS + 1, vector<T>(COLS + 1, 0));
        for (int r = 0; r < ROWS; r++) {
            for (int c = 0; c < COLS; c++) {
                prefix[r + 1][c + 1] = prefix[r + 1][c] + prefix[r][c + 1] - prefix[r][c] + matrix[r][c];
            }
        }
    }
    void init(const vector<vector<long long>>& matrix) {
        ROWS = matrix.size(), COLS = matrix[0].size();
        prefix = vector(ROWS + 1, vector<T>(COLS + 1, 0));
        for (int r = 0; r < ROWS; r++) {
            for (int c = 0; c < COLS; c++) {
                prefix[r + 1][c + 1] = prefix[r + 1][c] + prefix[r][c + 1] - prefix[r][c] + matrix[r][c];
            }
        }
    }
    void init(const vector<vector<char>>& matrix) {
        ROWS = matrix.size(), COLS = matrix[0].size();
        prefix = vector(ROWS + 1, vector<T>(COLS + 1, 0));
        for (int r = 0; r < ROWS; r++) {
            for (int c = 0; c < COLS; c++) {
                prefix[r + 1][c + 1] = prefix[r + 1][c] + prefix[r][c + 1] - prefix[r][c] + matrix[r][c] - '0';
            }
        }
    }

    // 0-index
    // sum region of top-left (r1, c1) to botton-right (r2, c2)
    T sumRegion(int r1, int c1, int r2, int c2) {
        return prefix[min(ROWS, r2 + 1)][min(COLS, c2 + 1)] - prefix[min(ROWS, r2 + 1)][max(0, c1)] - prefix[max(0, r1)][min(COLS, c2 + 1)] + prefix[max(0, r1)][max(0, c1)];
    }
};

int ROWS = matrix.size(), COLS = matrix[0].size();
prefixSumMatrix<long long> prefix(matrix);
//prefix.init(matrix);
prefix.sumRegion(r1, c1, r2, c2);
