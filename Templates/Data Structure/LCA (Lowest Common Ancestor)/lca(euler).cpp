// algo : first do dfs traversal and save the height along with the first time when a node is visited. also the euler tour(DFS traversal tour).
// a node with k children will appear k + 1 times. So total entries in euler tour will be 2*n-1.
//to find the lca of nodes u and v, find the minimum depth node between the entries of u and v in euler tour using segment tree/sparse table
//O(nlogn) time preprocessing and O(1) for each query

#include <bits/stdc++.h>
using namespace std;
#define FastIO ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL)

const int N = 200005;
vector<int> edge[N], euler(2 * N), height(N), firstVis(N), tree(2 * N);
vector<bool> vis(N, 0);
int ind;

void dfs(int u, int h = 0) {
	vis[u] = 1;

	euler[ind++] = u;
	firstVis[u] = ind - 1;
	height[u] = h;

	for (int v : edge[u]) {
		if (!vis[v]) {
			dfs(v, h + 1);
			euler[ind++] = u;
		}
	}
}

void build(int node, int left, int right) {
	if (left == right) {
		tree[node] = euler[left];
		return;
	}
	int mid = (left + right) / 2;
	build(node * 2, left, mid);
	build(node * 2 + 1, mid + 1, right);

	int l = tree[node * 2], r = tree[node * 2 + 1];
	tree[node] = (height[l] < height[r] ? l : r);
}

int query(int node, int b, int e, int l, int r) {
	if (l > e || r < b)return INT_MAX;

	if (b >= l && e <= r) {
		return tree[node];
	}
	int mid = (b + e) / 2;
	int val1 = query(2 * node, b, mid, l, r);
	int val2 = query(2 * node + 1, mid + 1, e, l, r);
	if (val1 == INT_MAX)return val2;
	if (val2 == INT_MAX)return val1;
	return (height[val1] < height[val2] ? val1 : val2);
}

int n;

int lca (int u, int v) {
	int left = firstVis[u], right = firstVis[v];
	if (left > right)swap(left, right);
	return query(1, 0, 2 * n - 1, left, right);
}

int main() {
	int tc;
	cin >> tc;
	for (int cs = 1; cs <= tc; cs++) {
		cout << "Case " << cs << ":\n";
		cin >> n;
		ind = 0;
		for (int i = 0; i <= n; i++) {
			edge[i].clear();
			vis[i] = 0;
			height[i] = INT_MAX;
			firstVis[i] = 0;
		}
		for (int i = 0; i < 2 * n; i++) {
			tree[i] = 0;
			euler[i] = 0;
		}
		for (int i = 1; i <= n; i++) {
			int m;
			cin >> m;
			for (int j = 0; j < m; j++) {
				int v;
				cin >> v;
				edge[i].push_back(v);
				edge[v].push_back(i);
			}
		}
		for (int i = 1; i <= n; i++) {
			if (!vis[i])dfs(1);
		}
		build(1, 0, 2 * n - 1);
		int q;
		cin >> q;
		while (q--) {
			int u, v;
			cin >> u >> v;
			cout << lca(u, v) << '\n';
		}
	}
	return 0;
}
