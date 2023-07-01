//template
// algo : first do dfs traversal and save the height along with the first time when a node is visited. also the euler tour(DFS traversal tour).
// a node with k children will appear k + 1 times. So total entries in euler tour will be 2*n-1.
//to find the lca of nodes u and v, find the minimum depth node between the entries of u and v in euler tour using segment tree/sparse table
//O(nlogn) time preprocessing and O(1) for each query
const int N = 200005;
int timer = 0;
vector<int> edge[N], tin(N), tout(N);
vector<vector<int>> par(N, vector<int> (25, -1));
vector<bool> vis(N, 0);
int n;

//Run dfs from (root - 1), e.g. dfs(0)
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

void process() {
	int Log = ceil(log2(n));
	for (int i = 1; i <= Log; i++) {
		for (int j = 0; j < n; j++) {
			if (par[j][i - 1] != -1)par[j][i] = par[par[j][i - 1]][i - 1];
		}
	}
}

int FindLCA(int u, int v) {
	int cur = u;
	int Log = ceil(log2(n));
	cur = isAncestor(u, v);
	for (int i = Log; i >= 0; i--) {
		if (par[v][i] != -1 && isAncestor(u, par[v][i]) == -1) {
			v = par[v][i];
		}
	}
	if (cur == -1)cur = par[v][0];
	return cur;
}
