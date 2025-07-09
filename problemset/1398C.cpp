// https://codeforces.com/problemset/problem/1398/C
#include <iostream>
#include <algorithm>
#include <vector>
#include <map>
#include <cstring>

using namespace std;

long long n, x[123456], pre[123456];
map<long long, long long> cnt;
string s;

long long solve() {
    cnt.clear();
    pre[0] = s[0] - '0';
    for (long long i = 0; i < n; i++) {
        x[i] = s[i] - '0';
        if (i > 0) pre[i] = pre[i - 1] + x[i];
        cnt[pre[i] - i - 1]++;
    }

    long long ans = 0;
    if (cnt.find(0) != cnt.end()) ans += cnt[0];
    for (auto it = cnt.begin(); it != cnt.end(); ++it) {
        long long key = it->first;
        long long value = it->second;
        // cout << "key = " << key << ", value = " << value << "\n";
        if (value > 1) ans += value * (value - 1) / 2;
    }
    return ans;
}

int main() {
    long long t; cin >> t;
    while (t--) {
        cin >> n >> s;
        cout << solve() << "\n";
    }
    return 0;
}
