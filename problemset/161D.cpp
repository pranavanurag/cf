#include <iostream>

using namespace std;

const int N = 543210;
const int K = 500;

int n, k;
vector<int> adj[N];
int parent[N], dp[N][K];
bool visited[N];

/*
 * dp[u][dist] = number of nodes in the subtree of u at a distance of dist from u
 */


void dfs(int u) {
    visited[u] = true;
    cout << "dfs: " << u << "\tparent: " << parent[u] << "\n";
    for (int v: adj[u]) if (!visited[v]) {
        parent[v] = u;
        dfs(v);
    }
}

void pre() {
    for (int i = 0; i < N; i++) {
        parent[i] = -1;
        visited[i] = false;
    }
}

void solve() {
    pre();
    for (int i = 1; i <= k; i++) {

    }
    dfs(1);
}

void input() {
    cin >> n >> k;
    for (int i = 0; i < n - 1; i++) {
        int u, v; cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
}

int main() {
    input();
    solve();
    return 0;
}
