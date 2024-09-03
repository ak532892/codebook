using LL = long long;

// #define localMinMax
template <typename T>
class SegTreeNode {
public:
    // Note: all arrays are 1-index
    vector<T> tree;
    vector<T> lazy;
#ifdef localMinMax
    const long long LINF = 0x3f3f3f3f3f3f3f3fLL;
    vector<T> treeMin;
    vector<T> treeMax;
#endif

    SegTreeNode() {}

    // init for range [1, n] with val
    SegTreeNode(int n, T val = 0) {
        initSize(n);
        init(1, 1, n, val);
    }

    // init for range [1, n] with nums
    // 1-index
    SegTreeNode(int n, vector<int>& nums) {
        initSize(n);
        init(1, 1, n, nums);
    }

    // init for range [1, n] with nums
    // 1-index
    SegTreeNode(int n, vector<long long>& nums) {
        initSize(n);
        init(1, 1, n, nums);
    }
    int my__builtin_clz(int n) {
        int sum = 0;
        for (int i = 31; i >= 0; --i) {
            if (n & (1 << i)) {
                sum = i;
                break;
            }
        }
        return 31 - sum;
    }
    void initSize(int n) {
        int SIZE = 2 << (32 - my__builtin_clz(n));
        tree.assign(SIZE, 0);
        lazy.assign(SIZE, 0);
#ifdef localMinMax
        treeMin.assign(SIZE, LINF);
        treeMax.assign(SIZE, -LINF);
#endif
    }

    void pull(int id) {
        tree[id] = tree[id * 2] + tree[id * 2 + 1];
#ifdef localMinMax
        treeMin[id] = min(treeMin[id * 2], treeMin[id * 2 + 1]);
        treeMax[id] = max(treeMax[id * 2], treeMax[id * 2 + 1]);
#endif
    }

    void init(int id, int L, int R, T val) {
        if (L == R) {
            tree[id] = val;
#ifdef localMinMax
            treeMin[id] = val;
            treeMax[id] = val;
#endif
            return;
        }
        int mid = L + (R - L) / 2;
        init(id * 2, L, mid, val);
        init(id * 2 + 1, mid + 1, R, val);
        pull(id);
    }

    // 1-index, so nums index should -1
    void init(int id, int L, int R, vector<int>& nums) {
        if (L == R) {
            tree[id] = nums[L - 1];
#ifdef localMinMax
            treeMin[id] = nums[L - 1];
            treeMax[id] = nums[L - 1];
#endif
            return;
        }
        int mid = L + (R - L) / 2;
        init(id * 2, L, mid, nums);
        init(id * 2 + 1, mid + 1, R, nums);
        pull(id);
    }

    // 1-index, so nums index should -1
    void init(int id, int L, int R, vector<long long>& nums) {
        if (L == R) {
            tree[id] = nums[L - 1];
#ifdef localMinMax
            treeMin[id] = nums[L - 1];
            treeMax[id] = nums[L - 1];
#endif
            return;
        }
        int mid = L + (R - L) / 2;
        init(id * 2, L, mid, nums);
        init(id * 2 + 1, mid + 1, R, nums);
        pull(id);
    }

    // setValue(1, 1, n, pos, val)
    // set treeVal[pos] as value, 1-index
    // time: O(log(n))
    void setValue(int id, int l, int r, int pos, T val) {
        if (l == r) {
            tree[id] = val;
#ifdef localMinMax
            treeMin[id] = val;
            treeMax[id] = val;
#endif
            return;
        }

        int mid = l + (r - l) / 2;
        if (pos <= mid) {
            setValue(id * 2, l, mid, pos, val);
        }
        else {
            setValue(id * 2 + 1, mid + 1, r, pos, val);
        }
        pull(id);
    }

    // updateDelta(1, 1, n, pos, val)
    // increase treeVal[pos] by delta
    // time: O(log(n))
    void updateDelta(int id, int l, int r, int pos, T val) {
        if (l == r) {
            tree[id] += val;
#ifdef localMinMax
            treeMin[id] += val;
            treeMax[id] += val;
#endif
            return;
        }

        int mid = l + (r - l) / 2;
        if (pos <= mid) {
            updateDelta(id * 2, l, mid, pos, val);
        }
        else {
            updateDelta(id * 2 + 1, mid + 1, r, pos, val);
        }
        pull(id);
    }

    void do_(int id, int l, int r, T val) {
        tree[id] += (r - l + 1) * val;
        lazy[id] += val;
#ifdef localMinMax
        treeMin[id] += val;
        treeMax[id] += val;
#endif
    }

    // use for assign value
    void do2_(int id, int l, int r, T val) {
        tree[id] = (r - l + 1) * val;
        lazy[id] = val;
#ifdef localMinMax
        treeMin[id] = val;
        treeMax[id] = val;
#endif
    }

    // updateRangeDelta(1, 1, n, L, R, val)
    // increase treeVal[L, R] by val
    // time: O(log(n))
    void updateRangeDelta(int id, int l, int r, int L, int R, T val) {
        if (L <= l && r <= R) {
            do_(id, l, r, val);
            // not update to the next level
            return;
        }

        int mid = l + (r - l) / 2;
        // need update lazy tag to the left and right sub node
        if (lazy[id]) {
            do_(id * 2, l, mid, lazy[id]);
            do_(id * 2 + 1, mid + 1, r, lazy[id]);
            lazy[id] = 0;
        }

        if (mid >= L) {
            updateRangeDelta(id * 2, l, mid, L, R, val);
        }
        if (mid < R) {
            updateRangeDelta(id * 2 + 1, mid + 1, r, L, R, val);
        }
        pull(id);
    }

    // queryRangeSum(1, 1, n, L, R)
    // sum of a range nums[L, R] inclusively
    // time: O(log(n))
    T queryRangeSum(int id, int l, int r, int L, int R) {
        if (L > R) {
            return 0;
        }
        if (L == l && R == r) {
            return tree[id];
        }
        int mid = (l + r) / 2;

        if (lazy[id]) {
            do_(id * 2, l, mid, lazy[id]);
            do_(id * 2 + 1, mid + 1, r, lazy[id]);
            lazy[id] = 0;
        }

        return queryRangeSum(id * 2, l, mid, L, min(R, mid)) +
               queryRangeSum(id * 2 + 1, mid + 1, r, max(L, mid + 1), R);
    }

#ifdef localMinMax
    // queryRangeMinMax(1, 1, n, L, R)
    // query min and max of range nums[L, R] inclusively 
    // time: O(log(n))
    array<T, 2> queryRangeMinMax(int id, int l, int r, int L, int R) {
        if (L > R) {
            return {LINF, -LINF};
        }
        if (L == l && R == r) {
            return {treeMin[id], treeMax[id]};
        }
        int mid = (l + r) / 2;

        if (lazy[id]) {
            do_(id * 2, l, mid, lazy[id]);
            do_(id * 2 + 1, mid + 1, r, lazy[id]);
            lazy[id] = 0;
        }

        array<T, 2> leftRes = queryRangeMinMax(id * 2, l, mid, L, min(R, mid));
        array<T, 2> rightRes = queryRangeMinMax(id * 2 + 1, mid + 1, r, max(L, mid + 1), R);
        array<T, 2> res = { min(leftRes[0], rightRes[0]), max(leftRes[1], rightRes[1]) };

        return res;
    }
#endif
};

// SegTreeNode<LL> seg(n, nums);
// SegTreeNode<LL> seg(n);
// SegTreeNode<LL> seg;
// seg.initSize(n);
// seg.updateDelta(1, 1, n, pos, val)
// seg.setValue(1, 1, n, pos, val)
// seg.updateRangeDelta(1, 1, n, l, r, val);
// auto res = seg.queryRangeMinMax(1, 1, n, l, r);
// 使用上是1-index
// 所以如果nums為0-index 使用上[L+1, R+1]
// seg.queryRangeSum(1, 1, n, L + 1, R + 1)
// 如果nums為1-index 使用上[L, R]
// seg.queryRangeSum(1, 1, n, L, R)
