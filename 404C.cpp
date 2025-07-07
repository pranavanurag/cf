// https://codeforces.com/problemset/problem/404/C
#include <iostream>
#include <algorithm>
#include <vector>
#include <map>
#include <cstring>

using namespace std;

long long n, k;
map<long long, vector<long long>> d;

int main() {
    cin >> n >> k;
    for (long long i = 0; i < n; i++) {
        long long temp; cin >> temp;
        d[temp].push_back(i + 1);
    }
    if (d[0].size() != 1) {
        cout << "-1\n";
        return 0;
    }

    vector<pair<long long, long long>> edges;
    vector<long long> parents, current;
    
    long long root = d[0][0];
    if (d[1].size() > k) {
        cout << "-1\n";
        return 0;
    }

    int prev_dist = -1;
    for (auto it = d.begin(); it != d.end(); ++it) {
        int dist = it->first;
        if (dist != prev_dist + 1) {
            cout << "-1\n";
            return 0;
        }
        prev_dist = dist;
    }

    for (auto v: d[1]) {
        edges.push_back({root, v});
        parents.push_back(v);
    }

    long long threshold = 1, idx = 1;
    for (auto it = d.begin(); it != d.end(); ++it) {
        long long dist = it->first;
        if (dist < 2) continue; // skip root and first-level
        current = it->second;
        if ((parents.size() * (k - 1)) < current.size()) {
            cout << "-1\n";
            return 0;
        }

        long long p_idx = 0, c_idx = 0;
        for (long long c : current) {
            edges.push_back({parents[p_idx], c});
            c_idx++;
            if (c_idx % (k - 1) == 0) p_idx++;
        }
        parents = current;
    }
    cout << edges.size() << "\n";
    for (auto e: edges) cout << e.first << " " << e.second << "\n";
    return 0;
}
