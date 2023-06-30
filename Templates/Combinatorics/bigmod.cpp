// for (a^n) % mod
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