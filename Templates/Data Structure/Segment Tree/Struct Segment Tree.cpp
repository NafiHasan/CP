struct segtree {
	int size; // set size of the tree as the closest value which is power of 2 and not less than the given array size n.

	vector<long long> tree;

	segtree(int n) {
		size = 1;
		while (size < n)size *= 2;
		tree.assign(2 * size, 0LL); // increase the size if n is bigger than 1e5.
	}

	void build(vector<int> &a, int node, int lo, int hi) {
		if (lo == hi) {
			if (lo < (int)a.size()) tree[node] = a[lo]; // check if the index is lower than the size of actual array as the tree size if greater than the actual array size.
			return;
		}
		int mid = (lo + hi) / 2;
		build(a, node * 2, lo, mid);
		build(a, node * 2 + 1, mid + 1, hi);
		tree[node] = tree[node * 2] + tree[node * 2 + 1];
	}

	void build(vector<int> &a) {
		build(a, 1, 0, size - 1);
	}

	void update(int node, int lo, int hi, int ind, int value) {
		if (ind < lo || ind > hi)return;
		if (lo == hi) {
			tree[node] = value;
			return;
		}

		int mid = (lo + hi) / 2;
		update(node * 2, lo, mid, ind, value);
		update(node * 2 + 1, mid + 1, hi, ind, value);

		tree[node] = tree[node * 2] + tree[node * 2 + 1];
	}

	//0-based indexing
	void update(int ind, int value) {
		update(1, 0, size - 1, ind, value);
	}

	long long query(int node, int lo, int hi, int l, int r) {
		if (hi < l || lo > r) {
			return 0;
		}
		if (lo >= l && hi <= r) {
			return tree[node];
		}

		int mid = (lo + hi) / 2;
		long long q1 = query(node * 2, lo, mid, l, r);
		long long q2 = query(node * 2 + 1, mid + 1, hi, l, r);
		return q1 + q2;
	}

	//0-based indexing
	long long query(int l, int r) {
		return query(1, 0, size - 1, l, r);
	}

};