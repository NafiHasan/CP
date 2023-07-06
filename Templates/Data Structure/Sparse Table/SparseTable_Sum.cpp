//for sum queries
const int K = 25, N = 300005; // K is a rough value for log(N), can change if needed.
long long table[K + 1][N];

//O(nlogn)
void process(vector<long long> a) {
	int n = a.size();
	for (int i = 0; i < a.size(); i++) table[0][i] = a[i]; // for length = 1

	for (int i = 1; i < K; i++) {
		for (int j = 0; j + (1 << i) <= n; j++) {
			table[i][j] = table[i - 1][j] + table[i - 1][j + (1 << (i - 1))]; //using previously calculated lengths to find range value for double lengths.
		}
	}
}

//O(logn)
//0-based indexing
long long query(int l, int r) {
	long long sum = 0;
	for (int i=K; i>=0; i--){ // trying the biggest power of 2 which is not less than the current length
		if((1 << i) <= (r - l + 1)){
			sum += table[i][l];
			l += (1 << i);   //increasing the left bound which is already calculated
		}
	}
	return sum;
}