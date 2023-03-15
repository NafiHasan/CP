#include <bits/stdc++.h>
using namespace std;
#define FastIO ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL)

const int N = 200005;
int timer = 0;
vector<int> edge[N], tin(N), tout(N);
vector<vector<int>> par(N, vector<int> (25, -1));
vector<bool> vis(N, 0);

void dfs(int u) {
	vis[u] = 1;
	tin[u] = timer++;
	for (int v : edge[u]) {
		if (!vis[v]) {
			dfs(v);
			par[v][0] = u;
		}
	}
	tout[u] = timer++;
}

int isAncestor(int u, int v) {
	if (tin[u] <= tin[v] && tout[u] >= tout[v])return u;
	if (tin[v] <= tin[u] && tout[v] >= tout[u])return v;
	return -1;
}

int main() {
	FastIO;
	int n;
	cin >> n;
	for (int i = 0; i < n; i++) {
		int m; cin >> m;
		while (m--) {
			int v; cin >> v;
			edge[i].push_back(v);
			edge[v].push_back(i);
		}
	}
	dfs(0);

	int Log = ceil(log2(n));
	for (int i = 1; i <= Log; i++) {
		for (int j = 0; j < n; j++) {
			if (par[j][i - 1] != -1)par[j][i] = par[par[j][i - 1]][i - 1];
		}
	}

	int q;
	cin >> q;
	while (q--) {
		int u, v;
		cin >> u >> v;
		int cur = u;
		cur = isAncestor(u, v);
		for (int i = Log; i >= 0; i--) {
			if (par[v][i] != -1 && isAncestor(u, par[v][i]) == -1) {
				v = par[v][i];
			}
		}
		if (cur == -1)cur = par[v][0];
		cout << cur << '\n';
	}

	return 0;
}