#include<iostream>
#include<vector>

using namespace std;

const int N = 54;
const int MOD = 998244353;

int fastexp(int x, int y) {
	int ans = 1;
	while (y > 0) {
		if (y & 1) ans = (1LL * ans * x) % MOD;
		x = (1LL * x * x) % MOD;
		y >>= 1;
	}
	return ans;
}

int f[N];
void pre() {
	f[0] = 1;
	for (int i = 1; i < N; i++) f[i] = (1LL * f[i-1] * i) % MOD;
}

int nck(int n, int k) {
	int numer = f[n];
	int denom = (1LL * f[n-k] * f[k]) % MOD;
	int invdenom = fastexp(denom, MOD - 2);
	return (1LL * numer * invdenom) % MOD;
}

int n, reserve;
int total = 0;
vector<int> a;

void input() {
	cin>>n;
	a.resize(n);
	cin>>reserve;
	total = reserve;
	for (int &x: a) {
		cin>>x;
		total += x;
	}
}

void solve() {
	// cout<<total<<"\n";
	bool possible = true;
	int k = (total/n), empty = 0;
	// cout<<"every person must hang "<<k<<" decorations\n";
	for (int i = 0; i < n; i++) {
		if (a[i] < k) {
			reserve -= (k - a[i]);
			a[i] = 0;
		} else {
			a[i] -= k;
		}
		empty += (a[i] == 0);
		possible &= (a[i] <= 1 && reserve >= 0);
	}
	int excluded = empty - reserve;
	// cout<<"in the final round, "<<excluded<<" people will not participate\n";
	if (possible) {
		// cout<<"calculating!\n";
		int ans = nck(empty, excluded);
		ans = (1LL * ans * f[excluded]) % MOD;
		ans = (1LL * ans * f[n - excluded]) % MOD;
		cout<<ans<<"\n";
	} else {
		cout<<0<<"\n";
	}
}

int main() {
	pre();
	int t; cin>>t; while (t--) {
		input();
		solve();
	}
	return 0;
}
