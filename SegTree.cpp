using LL = long long;

template <typename T>
class SegTreeNode {
public:
	// Note: all arrays are 1-index
	vector<T> tree;
	vector<T> treeMin;
	vector<T> treeMax;

	// init for range [1, n] with val
	SegTreeNode(int n, T val) {
		int SIZE = 4 * n;
		tree.assign(SIZE, val);
		treeMin.assign(SIZE, val);
		treeMax.assign(SIZE, val);
		init(1, 1, n, val);
	}
	
	// init for range [1, n] with nums
	// 1-index
	SegTreeNode(int n, const vector<T>& nums) {
		int SIZE = 4 * n;
		tree.assign(SIZE, 0);
		treeMin.assign(SIZE, 0);
		treeMax.assign(SIZE, 0);
		init(1, 1, n, nums);
	}
	SegTreeNode(){}

	void pull(int id) {
		tree[id] = tree[id * 2] + tree[id * 2 + 1];
		treeMin[id] = min(treeMin[id * 2], treeMin[id * 2 + 1]);
		treeMax[id] = max(treeMax[id * 2], treeMax[id * 2 + 1]);
	}
	void initSize(int n) {
		int SIZE = 4 * n;
		tree.assign(SIZE, 0);
		treeMin.assign(SIZE, 0);
		treeMax.assign(SIZE, 0);
	}
	void init(int id, int L, int R, T val) {
		if (L == R) {
			tree[id] = val;
			treeMin[id] = val;
			treeMax[id] = val;
			return;
		}
		int mid = L + (R - L) / 2;
		init(id * 2, L, mid, val);
		init(id * 2 + 1, mid + 1, R, val);
		pull(id);
	}
	// 1-index, so nums index should -1
	void init(int id, int L, int R, const vector<T>& nums) {
		if (L == R) {
			tree[id] = nums[L - 1];
			treeMin[id] = nums[L - 1];
			treeMax[id] = nums[L - 1];
			return;
		}
		int mid = L + (R - L) / 2;
		init(id * 2, L, mid, nums);
		init(id * 2 + 1, mid + 1, R, nums);
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
		return queryRangeSum(id * 2, l, mid, L, min(R, mid)) +
			   queryRangeSum(id * 2 + 1, mid + 1, r, max(L, mid + 1), R);
	}

	// setValue(1, 1, n, pos, val)
	// set treeVal[pos] as value, 1-index
	// time: O(log(n))
	void setValue(int id, int l, int r, int pos, T val) {
		if (l == r) {
			tree[id] = val;
			treeMin[id] = val;
			treeMax[id] = val;
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
			treeMin[id] += val;
			treeMax[id] += val;
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
};

// SegTreeNode<LL> seg(n);
// SegTreeNode<LL> seg;
// seg.initSize(n);
// updateDelta(1, 1, n, pos, val)
// setValue(1, 1, n, pos, val)
// 使用上是1-index
// 所以如果nums為0-index 使用上[L+1, R+1]
// queryRangeSum(1, 1, n, L + 1, R + 1)
// 如果nums為1-index 使用上[L, R]
// queryRangeSum(1, 1, n, L, R)
