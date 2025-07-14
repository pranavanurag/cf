// https://codeforces.com/problemset/problem/1037/D
#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include <set>
#include <map>
#include <cstring>

using namespace std;

const int N = 543210;

int n, givenorder[N], resorder[N];
vector<int> adj[N];
set<int> bfsv;
queue<int> bfsq;

bool bfscompare() {
    for (int u = 1; u <= n; u++)
        if (givenorder[u] != resorder[u]) return false;
    return true;
}

void sortadj() {
    for (int u = 1; u <= n; u++) {
        sort(adj[u].begin(), adj[u].end(), [](int a, int b) {
            return givenorder[a] < givenorder[b];
        });
    }
}

void bfs() {
    int order = 0;
    bfsq.push(1); bfsv.insert(1);
    while (!bfsq.empty()) {
        int u = bfsq.front(); bfsq.pop();
        resorder[u] = order++;
        for (int v: adj[u]) {
            if (bfsv.find(v) == bfsv.end()) {
                bfsv.insert(v); bfsq.push(v);
            }
        }
    }
}

bool solve() {
    sortadj();
    bfs();
    return bfscompare();
}

int main() {
    cin >> n;
    int u, v;
    for (int i = 0; i < n - 1; i++) {
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    for (int i = 0; i < n; i++) {
        int t; cin >> t;
        givenorder[t] = i;
    }
    if (solve()) cout << "Yes\n";
    else cout << "No\n";
    return 0;
}
