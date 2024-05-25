// #define localMinMax
template <typename T>
vector<T> discrete(const vector<T>& nums, int& size) {
	auto sorted_nums = nums;
	ranges::sort(sorted_nums);
	sorted_nums.erase(unique(sorted_nums.begin(), sorted_nums.end()), sorted_nums.end());
	size = sorted_nums.size();
	return sorted_nums;
}
template <typename T>
// lower_bound：找出 sorted_nums 中 >= val 的最小值的位置(最左邊的位置)
int findIdx(const vector<T>& sorted_nums, T val) {
    return ranges::lower_bound(sorted_nums, val) - sorted_nums.begin();
}
template <typename T>
// upper_bound - 1: 找出 sorted_nums 中 <= val 的最小值的位置(最左邊的位置)：
int findIdx2(const vector<T>& sorted_nums, T val) {
    return ranges::upper_bound(sorted_nums, val) - sorted_nums.begin() - 1;
}

template <typename T>
class fenwick_tree {
public:
    // Note: all arrays are 1-index
    vector<T> tree;
    int n;

#ifdef localMinMax
    // store original arrays value
    vector<T> treeMin;
    vector<T> treeMax;
    vector<T> nums;
#endif

    fenwick_tree(int _n) : n(_n) {
        tree.resize(n);
#ifdef localMinMax
        treeMin.resize(n);
        treeMax.resize(n);
        nums.resize(n);
#endif        
    }
    fenwick_tree() {}

    void init(int _n) {
        n = _n;
        tree.assign(_n, 0);
#ifdef localMinMax
        treeMin.assign(_n, 0);
        treeMax.assign(_n, 0);
        nums.assign(_n, 0);
#endif      
    }

    // increase tree[i] by delta
    // time: O(log(n))
    void updateDelta(int i, T delta) {
        while (i < n) {
            tree[i] += delta;
            i += i & -i; // lowbit
        }
    }

    // set tree[i] as value
    // time: O(log(n))
    void setValue(int i, T value) {
        T oldValue = sumRange(i, i);
        T delta = value - oldValue;

        while (i < n) {
            tree[i] += delta;
            i += i & -i; // lowbit
        }
    }

    // sum of a range nums[1, i] inclusively
    // time: O(log(n))
    T queryPreSum(int i) {
        T result = 0;
        while (i > 0) {
            result += tree[i];
            i &= i - 1;
        }
        return result;
    }

    // sum of a range nums[l, r] inclusively
    // time: O(log(n))
    T sumRange(int l, int r) {
        if ((l == 0) || (r == 0) || (l > r)) {
            return 0;
        }
        return queryPreSum(r) - ((l <= 1) ? 0 : queryPreSum(l - 1));
    }

    // find kth min_element value, use nums[i] as BIT ranges
    // time: O(log(n))
    T KthSmallest(int k) {
        int sum = 0, x = 0;
        for (int i = log2(n); ~i; --i) {
            x += 1 << i;
            if (x >= n || sum + tree[x] >= k)
                x -= 1 << i;
            else
                sum += tree[x];
        }
        return x + 1; // if ((x + 1) == n), it implies that values were not found
    }

    // find kth max_element value, use nums[i] as BIT ranges
    // time: O(log(n))
    T KthLargest(int k) {
        // same as KthSmallest(n + 1 - k)
        return KthSmallest(queryPreSum(n - 1) + 1 - k);
    }

#ifdef localMinMax    
    // set nums[i] as value, and update tree[x]
    // time: O((log(n))^2)
    void setValueMinMax(int i, T value) {
        nums[i] = value;
        while (i < n) {
            treeMin[i] = nums[i];
            treeMax[i] = nums[i];
            for (int j = 1; j < lowbit(i); j <<= 1) {
                treeMin[i] = min(treeMin[i], treeMin[i - j]);
                treeMax[i] = max(treeMax[i], treeMax[i - j]);
            }
            i += lowbit(i);
        }
    }

    // query min and max of range nums[l, r] inclusively 
    // time: O((log(n))^2)
    array<T, 2> queryRangeMinMax(int l, int r) {
        T resultMin = nums[r];
        T resultMax = nums[r];
        while (r >= l) {
            resultMin = min(resultMin, nums[r]);
            resultMax = max(resultMax, nums[r]);
            --r;
            for (; r - lowbit(r) >= l; r -= lowbit(r)) {
                resultMin = min(resultMin, treeMin[r]);
                resultMax = max(resultMax, treeMax[r]);
            }
        }
        return { resultMin, resultMax };
    }

    T lowbit(T num) {
        return num & -num;
    }
#endif    
};

// 可能要離散化, 也可能不用
// int m = 0;
// auto sorted_nums = discrete(nums, m);

fenwick_tree<int> t1(n + 1);
// or t1.init(n + 1);

// t1.setValueMinMax(i + 1, nums[i]);
// t1.queryRangeMinMax(l + 1, r + 1);
// t1.KthLargest(k)

// 在離散化陣列中 找到樹狀數組對應的下標 這樣就可以更新
// 1-index 所以要+1
t1.updateDelta(findIdx(sorted_nums, nums[i]) + 1, val);

// kth離散化後輸出value
// sorted_nums[t1.KthSmallest(k) - 1];