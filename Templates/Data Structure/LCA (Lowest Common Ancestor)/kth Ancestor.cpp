// finds the k-th ancestor of a node in a tree in log(n)
// almost same approach as sparse table

#include <bits/stdc++.h>
using namespace std;

#define FastIO ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL)


int main() {
	FastIO;
	int n; cin >> n;
	int par[n + 5][(int)log2(n) + 2];
	memset(par, -1, sizeof par);
	for (int i = 0; i < n; i++)cin >> par[i][0];

	for (int i = 1; i <= log2(n) + 1; i++) {
		for (int j = 0; j < n; j++) {
			if (par[j][i - 1] != -1)par[j][i] = par[par[j][i - 1]][i - 1];
		}
	}
	int node, k;
	cin >> node >> k;
	int ans = node;
	for (int i = 0; (1 << i) <= k; i++) {
		if (((1 << i) & k) != 0 && ans != -1) {
			ans = par[ans][i];
		}
	}
	cout << ans << '\n';
	return 0;
}