// sieve with bitset
const int N = 10000010;
bitset < N + 5 > bs;
vector<int> primes;
void sieve() {
	bs.set();
	bs[0] = bs[1] = 0;
	for (int i = 2; i * i <= N; i++) {
		if (!bs[i])continue;
		for (int j = i * i ; j <= N; j += i)bs[j] = 0;
	}
	for (int i = 2; i <= N; i++)if (bs[i])primes.push_back(i);
}
