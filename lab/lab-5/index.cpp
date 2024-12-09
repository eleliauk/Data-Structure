#include <iostream>
#include <vector>
#include <algorithm>
#include <limits>

using namespace std;

// 边结构体
struct Edge {
    int u, v, weight;
    Edge(int u, int v, int weight) : u(u), v(v), weight(weight) {}
};

// 并查集结构体
class DSU {
public:
    vector<int> parent, rank;

    DSU(int n) {
        parent.resize(n + 1);
        rank.resize(n + 1, 0);
        for (int i = 1; i <= n; i++) {
            parent[i] = i;
        }
    }

    int find(int x) {
        if (parent[x] != x) {
            parent[x] = find(parent[x]); // 路径压缩
        }
        return parent[x];
    }

    void unite(int x, int y) {
        int rootX = find(x);
        int rootY = find(y);
        if (rootX != rootY) {
            if (rank[rootX] > rank[rootY]) {
                parent[rootY] = rootX;
            } else if (rank[rootX] < rank[rootY]) {
                parent[rootX] = rootY;
            } else {
                parent[rootY] = rootX;
                rank[rootX]++;
            }
        }
    }
};

// Kruskal 算法
int kruskal(int n, vector<Edge>& edges, vector<Edge>& mst) {
    sort(edges.begin(), edges.end(), [](Edge& a, Edge& b) {
        return a.weight < b.weight; // 按权重升序排序
    });

    DSU dsu(n);
    int totalWeight = 0;

    for (Edge& edge : edges) {
        if (dsu.find(edge.u) != dsu.find(edge.v)) {
            dsu.unite(edge.u, edge.v);
            mst.push_back(edge);
            totalWeight += edge.weight;
            if (mst.size() == n - 1) break; // 最小生成树完成
        }
    }

    return totalWeight;
}

// 输入验证函数
bool validateInput(int& n, int& m) {
    if (n < 2) {
        cout << "居民区数量必须大于等于2，请重新输入。\n";
        return false;
    }
    if (m < n - 1 || m > n * (n - 1) / 2) {
        cout << "边的数量必须在 [" << n - 1 << ", " << n * (n - 1) / 2 << "] 范围内，请重新输入。\n";
        return false;
    }
    return true;
}

int main() {
    int n, m;
    while (true) {
        cout << "输入居民区数量 n 和管道候选路径数量 m: ";
        cin >> n >> m;
        if (cin.fail() || !validateInput(n, m)) {
            cin.clear(); // 清除错误状态
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // 丢弃输入缓冲区中的内容
            continue; // 提示用户重新输入
        }
        break;
    }

    vector<Edge> edges;
    cout << "输入每条路径的起点、终点和权重 (u v w):\n";
    for (int i = 0; i < m; i++) {
        int u, v, w;
        while (true) {
            cout << "路径 " << i + 1 << ": ";
            cin >> u >> v >> w;
            if (cin.fail() || u <= 0 || v <= 0 || u > n || v > n || w <= 0) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "输入无效，请确保起点和终点在 1 到 " << n << " 范围内，权重为正数。\n";
                continue;
            }
            edges.emplace_back(u, v, w);
            break;
        }
    }

    vector<Edge> mst;
    int totalWeight = kruskal(n, edges, mst);

    cout << "\n=== 最小生成树结果 ===\n";
    cout << "最小生成树总费用: " << totalWeight << "\n";
    cout << "选取的路径:\n";
    for (Edge& edge : mst) {
        cout << edge.u << " - " << edge.v << " : " << edge.weight << "\n";
    }

    return 0;
}