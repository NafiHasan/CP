// call sieve and populate primes
ll phi(ll n) {
	ll ans = n, ind = 0;
	while (primes[ind] * primes[ind] <= n) {
		if (n % primes[ind] == 0)ans -= ans / primes[ind];
		while (n % primes[ind] == 0)n /= primes[ind];
		ind++;
	}
	if (n != 1)ans -= ans / n;
	return ans;
}
//phi without sieve
ll phi(ll n) {
	ll ans = n;
	for (ll i = 2; i * i <= n; i++) {
		if (n % i == 0) ans -= ans / i;
		while (n % i == 0) n /= i;
	}
	if (n != 1) ans -= ans / n;
	return ans;
}
