// https://codeforces.com/contest/777/problem/E
// https://codeforces.com/contest/777/submission/31449989
#include <iostream>
#include <algorithm>
#include <vector>
#include <unordered_map>
#include <cstring>

using namespace std;

const long long N = 123456;

long long tr[4*N];

void update(long long i, long long tx1, long long tx2, long long x, long long val) {
	if (tx1 > x || tx2 < x || tx1 > tx2)
		return;

	if (tx1 == tx2)
		tr[i] = max(tr[i], val);
	else {
		long long txm = (tx1 + tx2)/2;
		update(2*i, tx1, txm, x, val);
		update(2*i + 1, txm + 1, tx2, x, val);
		tr[i] = max(tr[2*i], tr[2*i + 1]);
	}
}

long long query(long long i, long long tx1, long long tx2, long long x1, long long x2) {
	if (tx1 > tx2 || x1 > x2 || tx1 > x2 || tx2 < x1)
		return 0;

	if (tx1 >= x1 && tx2 <= x2)
		return tr[i];

	long long txm = (tx1 + tx2)/2;
	return max(query(2*i, tx1, txm, x1, x2), query(2*i + 1, txm + 1, tx2, x1, x2));
}


struct ring {
	long long a, b, h;
	ring() {
		a = b = h = 0;
	}
	ring(long long x, long long y, long long z) {
		a = x, b = y, h = z;
	}
};

bool outer_cmp(const ring &lhs, const ring &rhs) {
	if (lhs.b != rhs.b)
		return lhs.b < rhs.b;
	return lhs.a < rhs.a;
}

long long n;
vector <ring> v;
vector <long long> ir, dp;
unordered_map <long long, long long> ir_to_idx;

long long q_idx(long long otr) {
	auto lb = lower_bound(ir.begin(), ir.end(), otr);
	if (lb == ir.end())
		return n;
	return lb - ir.begin();
}

long long s_idx(long long inr) {
	auto lb = lower_bound(ir.begin(), ir.end(), inr);
	return lb - ir.begin() + 1;
}

int main() {
	ios::sync_with_stdio(false);
	memset(tr, 0, sizeof tr);

	cin>>n;
	v.resize(n), ir.resize(n);
	for (long long i = 0; i < n; i++) {
		cin>>v[i].a>>v[i].b>>v[i].h;
		ir[i] = v[i].a;
	}

	sort(ir.begin(), ir.end());
	for (long long i = 0; i < n; i++) {
		ir_to_idx[ir[i]] = i;
	}

	sort(v.begin(), v.end(), outer_cmp);
	reverse(v.begin(), v.end());

	dp.resize(n);
	dp[0] = v[0].h;
	update(1, 1, n, s_idx(v[0].a), dp[0]);
	for (long long i = 1; i < n; i++) {
		dp[i] = v[i].h + query(1, 1, n, 1, q_idx(v[i].b));
		update(1, 1, n, s_idx(v[i].a), dp[i]);
	}
	
	long long ans = 0;
	for (long long candidate: dp)
		ans = max(candidate, ans);

	cout<<ans<<endl;
	return 0;
}
