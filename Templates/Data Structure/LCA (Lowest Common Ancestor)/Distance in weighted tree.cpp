//Timus : Distance in Tree
//Finds the distance between 2 nodes in a weighted tree in log(n)

#include <bits/stdc++.h>
using namespace std;

#define FastIO ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL)

const int N = 50005;
int timer = 0;
int Log = 22;
vector<int> tin(N), tout(N);
vector<pair<int, int>> edge[N];
vector<vector<int>> par(N, vector<int> (25, -1)), mn(N, vector<int> (25, INT_MAX));
vector<bool> vis(N, 0);

void dfs(int u) {
	// cout << u << '\n';
	vis[u] = 1;
	tin[u] = timer++;
	for (pair<int, int> v : edge[u]) {
		// cout << v.first << '\n';
		if (!vis[v.first]) {
			dfs(v.first);
			par[v.first][0] = u;
			mn[v.first][0] = v.second;
		}
	}
	tout[u] = timer++;
}

int isAncestor(int u, int v) {
	if (tin[u] <= tin[v] && tout[u] >= tout[v])return u;
	if (tin[v] <= tin[u] && tout[v] >= tout[u])return v;
	return -1;
}

void preProcess(int n) {
	Log = ceil(log2(n)) + 1;
	for (int i = 1; i <= Log; i++) {
		for (int j = 0; j < n; j++) {
			if (par[j][i - 1] != -1) {
				int tmp = par[j][i - 1];
				par[j][i] = par[tmp][i - 1];
				mn[j][i] = mn[j][i - 1] + mn[tmp][i - 1];
			}
		}
	}
}

int kthParent(int parent, int node) {
	// cout << parent << ' ' << node << '\n';
	// if (parent == node)return 0;
	int k = 0;
	int i = Log;
	while (i >= 0 && node != parent) {
		if (isAncestor(par[node][i], parent) == parent) {
			k += (1 << i);
			node = par[node][i];
		}
		i--;
	}
	return k;
}

int calc(int node, int k) {
	if (k == 0)return 0;
	int ans = 0;
	int i = Log;
	while (k > 0 && i >= 0) {
		if ((1 << i) <= k) {
			k -= (1 << i);
			ans += mn[node][i];
			node = par[node][i];
		}
		i--;
	}
	return ans;
}

int main() {
	FastIO;
	int n;
	cin >> n;
	for (int i = 0; i < n - 1; i++) {
		int u, v, w;
		cin >> u >> v >> w;
		// u--, v--;
		edge[u].push_back({v, w});
		edge[v].push_back({u, w});

	}
	dfs(0);

	preProcess(n);

	int q;
	cin >> q;
	while (q--) {
		int u, v, tmpu, tmpv;
		cin >> u >> v;
		// u--, v--;
		tmpu = u, tmpv = v;
		int cur;
		// cout << u << ' ' << v << '\n';
		cur = isAncestor(u, v);
		for (int i = Log; i >= 0; i--) {
			if (par[v][i] != -1 && isAncestor(u, par[v][i]) == -1) {
				v = par[v][i];
			}
		}
		if (cur == -1)cur = par[v][0];
		// cout << u + 1 << ' ' << tmpv + 1 << ' ' << cur + 1 << '\n';
		int num1 = kthParent(cur, tmpu);
		int num2 = kthParent(cur, tmpv);

		int ansMin = calc(tmpu, num1) + calc(tmpv, num2);
		// int ansMax = max(calcMax(tmpu, num1), calcMax(tmpv, num2));
		cout << ansMin << '\n';
	}
	return 0;
}