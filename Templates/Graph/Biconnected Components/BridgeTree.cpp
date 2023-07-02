const int N = 300005;
vector<pair<int, int> > edge[N];  // {adjacent edge, index}
vector<int> dfsTime(N), low(N), comp(N), bridgeTree[N];
vector<bool> vis(N, 0), isBridge(N, 0);
int timer = 0;

//to find bridges
void dfs(int u, int par) {
	vis[u] = 1;
	dfsTime[u] = low[u] = ++timer;
	for (int i = 0; i < edge[u].size(); i++) {
		int v = edge[u][i].first, ind = edge[u][i].second;
		if (v == par)
			continue; // don't visit the parent node
		if (vis[v]) {  // cross edge
			low[u] = min(low[u], dfsTime[v]);
		} else {
			dfs(v, u);
			low[u] = min(low[u], low[v]);
			if (low[v] > dfsTime[u]) {  // checking among the back edges
				// u->v is a bridge
				isBridge[ind] = 1;
			}
		}
	}
}

// to assign unique component number to each component and its children
void dfs2(int u, int comp_number) {
	vis[u] = 1;
	comp[u] = comp_number;
	for (int i = 0; i < edge[u].size(); i++) {
		int v = edge[u][i].first, ind = edge[u][i].second;
		if (!vis[v] && !isBridge[ind]) {
			dfs2(v, comp_number);
		}
	}
}

void make_bridge_tree(int n) {
	// assign unique component number to each component
	vis.assign(n + 1, 0);
	comp.assign(n + 1, -1);
	int comp_number = 1;
	for (int i = 1; i <= n; i++) {
		if (!vis[i]) {
			dfs2(i, i);
			//i will be the root of its component
		}
	}
	for (int i = 0; i <= n; i++)bridgeTree[i].clear();

	//creating bridge tree
	for (int i = 1; i <= n; i++) {
		for (int j = 0; j < edge[i].size(); j++) {
			int v = edge[i][j].first;
			if (comp[i] != comp[v]) {
				bridgeTree[comp[i]].push_back(comp[v]);
				bridgeTree[comp[v]].push_back(comp[i]);
			}
		}
	}
}

void find_bridges(int n) {
	timer = 0;
	vis.assign(n + 1, 0);
	low.assign(n + 1, -1);
	dfsTime.assign(n + 1, -1);
	for (int i = 1; i <= n; i++) {
		if (!vis[i])dfs(i, -1);
	}
}