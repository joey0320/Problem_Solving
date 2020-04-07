struct Segtree {
	int n;
	vector<int> st;
	void build(int sz) {
		n = 1; 
		while (n < sz) n *=2;
		st.assign(2 * n, 0);
	}
	void update(int idx, int val) {
		idx += n - 1;
		st[idx] = val;
		for (idx /= 2; idx; idx /= 2) 
			st[idx] = st[2*idx] + st[2*idx + 1];
	}
	int range(int l, int r) {
		int sum = 0;
		for (l += n - 1, r += n - 1; l <= r; l /= 2, r /= 2) {
			if ((l & 1)) sum += st[l++];
			if (!(r & 1)) sum += st[r--];
		}
		return sum;
	}
};