#include <bits/stdc++.h>
using namespace std;

// DFS function to detect cycles in a directed graph
bool dfsCheck(int node, vector<vector<int>> &adj, vector<int> &vis, vector<int> &pathVis) {
    vis[node] = 1;
    pathVis[node] = 1;

    for (int neighbor : adj[node]) {
        if (!vis[neighbor]) {
            if (dfsCheck(neighbor, adj, vis, pathVis))
                return true;
        } else if (pathVis[neighbor]) {
            return true;  // Found a cycle
        }
    }

    pathVis[node] = 0;  // Backtrack
    return false;
}

// Function to check for circular dependency
bool hasCircularDependency(int n, vector<vector<int>> &edges) {
    vector<vector<int>> adj(n);

    // Build adjacency list
    for (auto &edge : edges) {
        int from = edge[0];
        int to = edge[1];
        adj[from].push_back(to);
    }

    vector<int> vis(n, 0), pathVis(n, 0);

    for (int i = 0; i < n; ++i) {
        if (!vis[i]) {
            if (dfsCheck(i, adj, vis, pathVis))
                return true;
        }
    }
    return false;
}

int main() {
    int n, m;
    cin >> n >> m;

    vector<vector<int>> edges;
    for (int i = 0; i < m; ++i) {
        int a, b;
        cin >> a >> b;
        edges.push_back({a, b});
    }

    bool result = hasCircularDependency(n, edges);
    cout << (result ? "True" : "False") << endl;

    return 0;
}
