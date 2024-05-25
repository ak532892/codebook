class UnionFind {
public:
	vector<int> parent, size;

	// size 是那一塊的連通圖元素個數(大小)
    UnionFind(int n) : parent(n), size(n, 1) {
        for (int i = 0; i < n; i++) {
            parent[i] = i;
        }
    }
    UnionFind(){}

    void init(int n) {
        parent.assign(n, 0);
        size.assign(n, 1);
        for (int i = 0; i < n; i++) {
            parent[i] = i;
        }
    }

    int find(int x) {
        if (parent[x] != x) {
        	parent[x] = find(parent[x]);
        }
        return parent[x];
    }
	
	void erase(int x) {
		--size[find(x)];
		parent[x] = x;
	}

    void union_set(int x, int y) {
        x = find(x), y = find(y);
 
        if (x == y) {
            return;
        } 
		if (size[x] < size[y]) {
			swap(x, y);
		}
		parent[y] = x;
		size[x] += size[y];
    }
};

UnionFind dsu(n);
// dsu.init(n);

dsu.union_set(x, y);