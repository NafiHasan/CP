//for min/max queries
const int K = 25, N = 300005; // K is a rough value for log(N), can change if needed.
int table[K + 1][N];

//O(nlogn)
void process(vector<int> a) {
	int n = a.size();
	for (int i = 0; i < a.size(); i++) table[0][i] = a[i]; // for length = 1

	for (int i = 1; i < K; i++) {
		for (int j = 0; j + (1 << i) <= n; j++) {
			table[i][j] = min(table[i - 1][j], table[i - 1][j + (1 << (i - 1))]); //using previously calculated lengths to find range value for double lengths.
		}
	}
}

//O(1)
int query(int l, int r) {
	int lg = 31 - __builtin_clz(r - l + 1);  //taking largest log value which is not greater than the length
	return min(table[lg][l], table[lg][r - (1 << lg) + 1]);
}
