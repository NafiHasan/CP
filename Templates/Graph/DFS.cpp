//clear global variables for multiple test cases
const int N = 200005;
vector<int> edge[N];
vector<bool> vis(N, 0);

void DFS(int u){
	vis[u] = 1;

	for (int v : edge[u]){
		if(!vis[v]){
			DFS(v);
		}
	}
} 