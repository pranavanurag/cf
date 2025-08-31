#include <iostream>
#include <algorithm>

using namespace std;

string s;

int main() {
    int t; cin >> t;
    while (t--) {
        cin >> s;
        sort(s.begin(), s.end());
        reverse(s.begin(), s.end());
        cout << s << "\n";
    }
    return 0;
}
