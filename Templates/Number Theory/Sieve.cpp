const int N = 200005;
vector<bool>prime(N+1, 1);

void sieve(){
	prime[0] = prime[1] = 0;
	for (int i=2; i*i <= N; i++){
		if(!prime[i])continue;
		for (int j = i*i ; j <= N; j+=i)prime[j] = 0;
	}
}
