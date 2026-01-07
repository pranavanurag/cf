#include<iostream>
#include<vector>

using namespace std;

int n;
vector<int> a, b, c;

void input() {
	cin>>n;
	a.resize(n); b.resize(n); c.resize(n);
	for(int &x: a) cin>>x;
	for(int &x: b) cin>>x;
	for(int &x: c) cin>>x;
}

void solve() {
	int k1 = 0, k2 = 0;
	for (int i_start = 0; i_start < n; i_start++) {
		bool flag = true;
		for (int offset = 0; offset < n; offset++) {
			int check_index = (offset + i_start) % n;
			flag &= (a[check_index] < b[offset]);
		}
		if (flag) k1++;
	}

	for (int k_start = 0; k_start < n; k_start++) {
		bool flag = true;
		for (int offset = 0; offset < n; offset++) {
			int check_index = (offset + k_start) % n;
			flag &= (c[check_index] > b[offset]);
		}
		if (flag) k2++;
	}
	long long ans = (long long) k1 * k2 * n;
	cout<<ans<<"\n";
}

int main() {
	int t; cin>>t; while (t--) {
		input();
		solve();
	}
	return 0;
}
