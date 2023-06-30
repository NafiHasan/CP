//Don't forget to clear the global variables
// make sure to set the maximum size according to the problem

// Stores the parity distance for every node from itself to a specific node(e.g. node 1) 
// if 2 nodes are in same parity, then they are in same set
// if 2 nodes from same parity gets connected, the graph stops being bipartite. 

const int N = 1e5 + 10;
vector<int> par(N), len(N, 0), rnk(N, 0);

void makeset() {
	for (int i = 1; i < N; i++)par[i] = i;
}

pair<int, int> get(int a) {
	// path compressed, change if needed
	if (par[a] == a) {
		return {a, 0};
	} else {
		pair<int, int> x = get(par[a]);
		par[a] = x.first;
		len[a] = (len[a] + x.second) % 2;
		return {par[a], len[a]};
	}
}

void union_set(int a, int b) {
	pair<int, int> pa = get(a); // find the topmost parent
	pair<int, int> pb = get(b);

	if (pa == pb && len[a] == len[b]) {
		return;
	} // are in same set

	if (rnk[pa.first] == rnk[pb.first])rnk[pa.first]++;

	if (rnk[pa.first] > rnk[pb.first]) {
		par[pb.first] = pa.first;
		len[pb.first] = (1 + pa.second + pb.second) % 2;
		rnk[pa.first]++;
	} else {
		par[pa.first] = pb.first;
		len[pa.first] = (1 + pa.second + pb.second) % 2;
		rnk[pb.first]++;
	}
}