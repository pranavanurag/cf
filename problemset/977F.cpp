// https://codeforces.com/problemset/problem/977/F
#include <iostream>
#include <map>
#include <vector>
#include <algorithm>

using namespace std;

const int N = 212345;

int n, a[N], dp[N], successor[N];
// indices where a particular number exists (indices in ascending order)
map<int, vector<int>> indices;
vector<int> result;

int successor_index(int idx) {
    int val = a[idx];
    auto skiplist = indices[val + 1];
    if (skiplist.size() == 0) return -1;
    auto it = lower_bound(skiplist.begin(), skiplist.end(), idx + 1);
    if (it != skiplist.end()) return *it;
    else return -1;
}

void pre() {
    for (int i = 0; i < n; i++) {
        dp[i] = 1;
        successor[i] = successor_index(i);
    }
}

void solve() {
    pre();
    for (int i = n - 1; i >= 0; i--) {
        int sidx = successor[i];
        if (sidx != -1) dp[i] = max(dp[i], dp[successor[i]] + 1);
    }
    
    int best_len = 0, best_idx = -1;
    for (int i = 0; i < n; i++) {
        int l = dp[i];
        if (best_len < l) {
            best_len = l;
            best_idx = i;
        }
    }

    int curr_idx = best_idx;
    while (best_len--) {
        result.push_back(curr_idx + 1);
        curr_idx = successor[curr_idx]; // greedily pick the first available successor
    }
}

void display_result() {
    cout << result.size() << "\n";
    for (int i: result) cout << i << " "; cout << "\n";
}

void input() {
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        indices[a[i]].push_back(i);
    }
}

int main() {
    input();
    solve();
    display_result();
    return 0;
}
