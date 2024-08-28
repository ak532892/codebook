class UnionFind {
public:
    vector<int> parent, rank;

    UnionFind(){}
    UnionFind(int n) : parent(n), rank(n, 1) {
        for (int i = 0; i < n; i++) {
            parent[i] = i;
        }
    }

    void init(int n) {
        parent.assign(n, 0);
        rank.assign(n, 1);
        for (int i = 0; i < n; i++) {
            parent[i] = i;
        }
    }

    int find(int x) {
        x = parent[x];
        while (x != parent[x]) {
            parent[x] = parent[parent[x]];
            x = parent[x];
        }
        return x;
    }
	
    void union_set(int x, int y) {
        x = find(x), y = find(y);
 
        if (x == y) {
            return;
        } 
        if (rank[x] < rank[y]) {
            swap(x, y);
        }
        parent[y] = x;
        rank[x] += rank[y];
    }
    
    // need to check if delete elements is leaf or not
    void erase(int x) {
        --rank[find(x)];
        parent[x] = x;
    }
	
    void move(int x, int y) {
        int fx = find(x), fy = find(y);

        if (fx == fy) {
            return;
        }
        parent[x] = fy;
        --rank[fx], ++rank[fy];
    }
};

UnionFind dsu(n);
// dsu.init(n);

dsu.union_set(x, y);
