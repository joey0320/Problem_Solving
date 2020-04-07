void gettree(int p, int c) {
	d[c] = d[p] + 1;
	ac[c][0] = p;
	for (int i = 1; i <= dmax; i++) {
		int tmp = ac[c][i - 1];
		ac[c][i] = ac[tmp][i - 1];
	}
	for (auto cc : tree[c]) {	
		if (cc != p) {
			gettree(c, cc);
		}
	}
}

int lca = a;
		if (a != b) {
			for (int i = dmax; i >= 0; i--) {
				if (ac[a][i] != ac[b][i]) {
					a = ac[a][i];
					b = ac[b][i];
				}
				lca = ac[a][i];
			}
		}