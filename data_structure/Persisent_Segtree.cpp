struct Persisent_Segtree{
	int nextfree = 0;
	int root[MAXN];
	struct node{
		int sum, left, right;
	}tree[2*MAXN + (logN + 1) * MAXQ];

	int init(int nl, int nr){
		int idx = ++nextfree;
		if(nl == nr){
			tree[idx] = {0, 0, 0};
			return idx;	
		}
		int m = (nl + nr)>>1;
		int L = init(nl, m), R = init(m + 1, nr);
		tree[idx] = {tree[L].sum + tree[R].sum, L, R};
		return idx;
	}
	int update(int prev, int nl, int nr, int x, int val){
		if(nl > x || nr < x) return prev;
		int idx = ++nextfree;
		if(nl==nr){
			tree[idx] = {val, 0, 0};
			return idx;
		}
		int m = (nl + nr) >> 1;
		int L = update(tree[prev].left, nl, m, x, val);
		int R = update(tree[prev].right, m + 1, nr, x, val);
		tree[idx] = {tree[L].sum + tree[R].sum, L, R};
		return idx;
	}
	int rangesum(int n, int nl, int nr, int l, int r){
		if(nl > r || nr < l) return 0;
		if(l <= nl && nr <= r) return tree[n].sum;
		int m = (nl + nr) >> 1;
		return rangesum(tree[n].left, nl, m, l, r) + rangesum(tree[n].right, m + 1, nr, l, r);
	}

	void buildtree(){
		getnext();
		root[0] = init(1, N + 1);
		repp(i, 1, N){
			int x = nxt[i];
			int val = rangesum(root[i - 1], 1, N + 1, x, x) + 1;
			root[i] = update(root[i - 1], 1, N + 1, x, val);
		}
	}
};