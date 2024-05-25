#if 0
// Dijkstra
// Single source, one start and one end
// O(n + Elog(E)), E = edges.len
// vector<vector<pair<int, int>>> graph;
const long long LINF = 0x3f3f3f3f3f3f3f3fLL;
class Graph {
public:
    vector<vector<pair<int, int>>> graph;
    int n;
    Graph(int n, vector<vector<int>>& edges) {
        graph.resize(n);
        for (auto& e : edges) {
            int from = e[0], to = e[1], cost = e[2];
            graph[from].push_back({to, cost});
        }
        this->n = n;
    }
    
    void addEdge(vector<int> edge) {
        graph[edge[0]].push_back({edge[1], edge[2]});
    }
    
    int shortestPath(int start, int end) {
        vector<long long> minCost(n, LINF);
        priority_queue<pair<long long, int>, vector<pair<long long, int>>, greater<>> pq;
        
        minCost[start] = 0;
        pq.push({0, start});
        while (!pq.empty()) {
            auto [curCost, curNode] = pq.top();
            pq.pop();
            if (curNode == end) {
                return minCost[curNode];
            }
            if (curCost > minCost[curNode]) {
                continue;
            }
            for (auto& [neighbor, cost] : graph[curNode]) {
                long long newCost = curCost + cost;
                if (newCost < minCost[neighbor]) {
                    minCost[neighbor] = newCost;
                    pq.push({minCost[neighbor], neighbor});
                }
            }
        }
        return -1;
    }
};
#endif
#if 0
// Dijkstra
// Single source, one start and one end
// O(n + Elog(E)), E = edges.len
// 基本跟上面一樣 只是存graph方式不同 稍微慢一點
// vector<vector<int>> graph;
const long long LINF = 0x3f3f3f3f3f3f3f3fLL;
class Graph {
public:
    vector<vector<long long>> graph;
    int n;
    Graph(int n, vector<vector<int>>& edges) {
        graph = vector(n, vector<long long>(n, LINF));
        for (auto& e : edges) {
            graph[e[0]][e[1]] = e[2];
        }
        this->n = n;
    }
    
    void addEdge(vector<int> edge) {
        graph[edge[0]][edge[1]] = edge[2];
    }
    
    int shortestPath(int start, int end) {
        vector<long long> minCost(n, LINF);
        priority_queue<pair<long long, int>, vector<pair<long long, int>>, greater<>> pq;
        
        minCost[start] = 0;
        pq.push({0, start});
        while (!pq.empty()) {
            auto [curCost, curNode] = pq.top();
            pq.pop();
			if (curNode == end) {
                return minCost[curNode];
            }
            if (curCost > minCost[curNode]) {
                continue;
            }
            for (int neighbor = 0; neighbor < n; ++neighbor) {
            	long long newCost = curCost + graph[curNode][neighbor];
                if (newCost < minCost[neighbor]) {
                    minCost[neighbor] = newCost;
                    pq.push({minCost[neighbor], neighbor});
                }
            }
        }
        return -1;
    }
};

// if (curCost > minCost[curNode]) continue;
// => 會加這條的原因是
// => 走訪過程中同一個 node 如果出現多次更低的 min cost 那會被重複壓入pq裡面
// => 但可能先處理過最小的 cost 這樣一來 之前同個點次低的 cost 就不用再處理一次
#endif
#if 0
// Dijkstra
// 樸素版本, 稠密圖適用
// 貪心算法
// time: O(n^2)
// space: O(n^2)
const long long LINF = 0x3f3f3f3f3f3f3f3fLL;
class Graph {
public:
    vector<vector<long long>> graph;
    int n;
    Graph(int n, vector<vector<int>>& edges) {
        graph = vector(n, vector<long long>(n, LINF));
        for (auto& e : edges) {
            graph[e[0]][e[1]] = e[2];
        }
        this->n = n;
    }
    
    void addEdge(vector<int> edge) {
        graph[edge[0]][edge[1]] = edge[2];
    }
    
    int shortestPath(int start, int end) {
        vector<long long> minCost(n, LINF);
        vector<bool> visited(n, false);
        
        minCost[start] = 0;
        while (1) {
            int x = -1;
            for (int i = 0; i < n; ++i) {
                if (!visited[i] && (x == -1 || minCost[i] < minCost[x])) {
                    x = i;
                }
            }
            if (x == -1 || minCost[x] == LINF) {
                return -1;
            }
            if (x == end) {
                return minCost[end];
            }
            visited[x] = true;
            for (int y = 0; y < n; ++y) {
                minCost[y] = min(minCost[y], minCost[x] + graph[x][y]);
            }
        }
        return -1;
    }
};
// 利用權重 >= 0的條件去貪心
// 1. 創一個陣列表示起點到每個點的最短路
// vector<int> minCost(n, 0x3f3f3f3f);
// minCost[start] = 0
// 2. 創一個陣列表示已經被更新成最短路的點
// 這樣後續就不用處理這個點
// 因為假設這個點其他的邊都已經更新過最短路
// 那之後就用不上這個點，也就是說要找其他的點
// vector<bool> vis(n, false);
// 3. 跑迴圈跑n次
// 首先在內部迴圈從minCost找到一個最短路的點 x
// 如果x < 0 或者 minCost[x] == 0x3f3f3f3f (表示起點到達不了x)
//    表示走不到end return -1
// 如果x == end
//    找到最短路 return minCost[x]
// 接著更新vis[x] = true
// 然後看一下其餘點minCost[y]是否會比minCost[x] + graph[x][y]還要小
// 並更新
// 這表示說目前有一個最短路minCost[x]
// 問你原本的最短路start->y需不需要更新成可能更小的start->x->y路線
// https://l...content-available-to-author-only...e.cn/problems/design-graph-with-shortest-path-calculator/solutions/2229013/dijkstra-suan-fa-mo-ban-pythonjavacgo-by-unmv/
#endif

#if 0
// Floyd–Warshall
// Multiple source
// time: O(n^3)
// space: O(n^2)
const long long LINF = 0x3f3f3f3f3f3f3f3fLL;
class Graph {
public:
    vector<vector<long long>> graph;
    int n;
    Graph(int n, vector<vector<int>>& edges) {
        //need to check MAX weight, should be max weight * node count
        graph = vector<vector<long long>>(n, vector<long long>(n, LINF));
        //need to check bidirectional or directional
        for (auto &e : edges) {
            int from = e[0], to = e[1], cost = e[2];
            graph[from][to] = cost;
        }
        for (int i = 0; i < n; ++i) {
            graph[i][i] = 0;
        }
        for (int k = 0; k < n; ++k) {
            for (int i = 0; i < n; ++i) {
            	// optimize
            	if (graph[i][k] == LINF) {
            		continue;
            	}
                for (int j = 0; j < n; ++j) {
                    graph[i][j] = min(graph[i][j], graph[i][k] + graph[k][j]);
                }
            }
        }
        this->n = n;
    }
    void addEdge(vector<int> edge) {
        int from = edge[0];
        int to = edge[1];
        int cost = edge[2];
		if (cost >= graph[from][to]) // 无需更新
            return;
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                graph[i][j] = min(graph[i][j], graph[i][from] + cost + graph[to][j]);
            }
        }
    }
    int shortestPath(int start, int end) {
        return graph[start][end] == LINF ? -1 : graph[start][end];
    }
};
#endif

#if 0
// SPFA
// Single source, one start and one end
// O(nE), E = edges.len
// vector<vector<pair<int, int>>> graph;
// 用來處理有負環的情況
// 如果有負環isNegCycleExisted == true
const long long LINF = 0x3f3f3f3f3f3f3f3fLL;
class Graph {
public:
    vector<vector<pair<int, int>>> graph;
    int n;
    Graph(int n, vector<vector<int>>& edges) {
        graph.resize(n);
        for (auto& e : edges) {
            int from = e[0], to = e[1], cost = e[2];
            graph[from].push_back({ to, cost });
        }
        this->n = n;
    }

    void addEdge(vector<int> edge) {
        graph[edge[0]].push_back({ edge[1], edge[2] });
    }

    int shortestPath(int start, int end) {
        vector<long long> minCost(n, LINF);
        vector<bool> isVisited(n, false);
        vector<int> cnt(n, 0);
        queue<int> q;
        bool isNegCycleExisted = false;

        minCost[start] = 0, isVisited[start] = true;
        q.push(start);
        while (!q.empty()) {
            int curNode = q.front();
            q.pop();
            isVisited[curNode] = false;
            for (auto& [neighbor, cost] : graph[curNode]) {
                long long newCost = minCost[curNode] + cost;
                if (newCost < minCost[neighbor]) {
                    minCost[neighbor] = newCost;
                    cnt[neighbor] = cnt[curNode] + 1;  // 记录最短路经过的边数

                    // 在不经过负环的情况下，最短路至多经过 n - 1 条边
                    // 因此如果经过了多于 n 条边，一定说明经过了负环
                    if (cnt[neighbor] >= n) {
                        isNegCycleExisted = true;
                        //cout << "Find neg Cycle!!\n";
                        return -1;
                    }

                    if (!isVisited[neighbor]) {
                        q.push(neighbor);
                        isVisited[neighbor] = 1;
                    }
                }
            }
        }
        isNegCycleExisted = false;
        //cout << "No neg Cycle\n";
        return minCost[end] == LINF ? -1 : minCost[end];
    }
};
#endif