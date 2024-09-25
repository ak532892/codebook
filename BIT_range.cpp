template <typename T>
class fenwick_tree2 {
public:
    // Range update
    // Note: all arrays are 1-index
    vector<T> sum1;
    vector<T> sum2;
    int n;

    fenwick_tree2(const vector<T>& nums) {
        n = nums.size();
        sum1.resize(n + 2);
        sum2.resize(n + 2);
        init(nums);
    }
    fenwick_tree2(int _n) : n(_n) {
        sum1.resize(n + 2);
        sum2.resize(n + 2);
    }
    fenwick_tree2() {}
	
    void init(int _n) {
        n = _n;
        sum1.resize(n + 2);
        sum2.resize(n + 2);
    }
	
    void init(const vector<T>& nums) {
        n = nums.size();
        sum1.resize(n + 2);
        sum2.resize(n + 2);
        for (int i = 0; i < n;i++) {
            if (i == 0) {
                updateDelta(i + 1, nums[i], sum1);
                updateDelta(i + 1, nums[i], sum2);
            }
            else {
                T diff = nums[i] - nums[i - 1];
                updateDelta(i + 1, diff, sum1);
                updateDelta(i + 1, diff * (i + 1), sum2);
            }
        }
    }

    // increase tree[i] by delta
    void updateDelta(int i, T delta, vector<T>& tree) {
        while (i <= n) {
            tree[i] += delta;
            i += i & -i;
        }
    }
    void add(int p, T delta) {
        for (int i = p; i <= n; i += i & -i) {
            sum1[i] += delta, sum2[i] += delta * p;
        }
    }

    void updateRange(int left, int right, T delta) {
        add(left, delta);
        add(right + 1, -delta);
    }

    // sum of a range nums[1, p] inclusively
    T queryPreSum(T p) {
        T res = 0;
        for (int i = p; i; i -= i & -i)
            res += (p + 1) * sum1[i] - sum2[i];
        return res;
    }

    // sum of a range nums[l, r] inclusively
    T queryRangeSum(T left, T right) {
        return queryPreSum(right) - queryPreSum(left - 1);
    }
};

fenwick_tree2<long long> t2(nums);
// fenwick_tree2<long long> t2(n);
// or t2.init(nums);
int val;
t2.updateRange(left, right, val);
t2.queryRangeSum(left, right);
