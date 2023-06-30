//find all the lengths of the longest substring starting from index i which is prefix of the main string
// more formally, z[i] = length of longest substring starting from i which is prefix of the main string
vector<int> z_fun(string s) {
    int n = (int) s.length();
    vector<int> z(n);
    for (int i = 1, l = 0, r = 0; i < n; ++i) {
        if (i <= r)
            z[i] = min (r - i + 1, z[i - l]);
        while (i + z[i] < n && s[z[i]] == s[i + z[i]])
            ++z[i];
        if (i + z[i] - 1 > r)
            l = i, r = i + z[i] - 1;
    }
    return z;
}// for (a^n) % mod
// Runs in O(logn)
const long long mod = 1e9 + 7;
long long bigmod (long long a, long long n){
	a %= mod;
	long long ans = 1;
	while(n){
		if (n & 1) ans = ans * a % mod;
		a = a * a % mod;
		n >>= 1;
	}
	return ans;
}