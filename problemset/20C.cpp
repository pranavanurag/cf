#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include <set>
#include <map>
#include <cstring>

using namespace std;

typedef pair<long long, long long> pii;

const long long N = 212345;
const long long INF = N * (long long) 1e6;

long long n, m, d[N], parent[N];
vector<pair<long long, long long>> adj[N];
vector<long long> path;
priority_queue<pii, vector<pii>, greater<pii>> pq;

bool solve() {
    d[1] = 0;
    parent[1] = -1;
    pq.push({0, 1});
    while (!pq.empty()) {
        long long w = pq.top().first;
        long long u = pq.top().second;
        // cout << "picked u: " << u << ", with distance: " << w << " from source\n";
        pq.pop();
        
        for (auto edge: adj[u]) {
            long long v = edge.first;
            long long vw = edge.second;
            // cout << "\tpicked v: " << v << ", with distance: " << vw << " from u: " << u << "\n";
            if (d[v] > d[u] + vw) {
                d[v] = d[u] + vw;
                parent[v] = u;
                pq.push({d[v], v});
            }
        }
    }

    long long u = n;
    path.push_back(u);
    while (parent[u] != -1) {
        u = parent[u];
        path.push_back(u);
    }
    if (u == 1) return true;
    else return false;
}

void input() {
    cin >> n >> m;
    for (long long i = 0; i < m; i++) {
        long long u, v, w;
        cin >> u >> v >> w;
        adj[u].push_back({v, w});
        adj[v].push_back({u, w});
    }
}

int main() {
    for (long long i = 0; i < N; i++) { parent[i] = -1; d[i] = INF; }
    input();
    if (solve()) {
        reverse(path.begin(), path.end());
        for (long long u: path) cout << u << " "; cout << "\n";
    } else {
        cout << "-1\n";
    }
    return 0;
}
