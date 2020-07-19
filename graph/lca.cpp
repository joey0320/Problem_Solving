// LCA tree;
// tree.init(N);
// tree.assignLevel(root);

struct LCA {
	int n, k;
	vector<vector<int>> graph, par;
	vector<int> dist;

	void init ( int sz ) {
		n = sz;
		k = (int) ceil(log2(n)) + 1;
		graph.resize(n);
		par.resize(n);
		for ( int i = 0; i < n; i ++ ) par[i].assign(k, -1);
		dist.assign(n, -1);
	}

	void addedge ( int u, int v ) {
		graph[u].push_back(v);
		graph[v].push_back(u);
	}

	void dfs ( int u, int p ) {
		if ( p == - 1 ) dist[u] = 0;
		for ( auto v : graph[u] ) if ( v != p ) {
			dist[v] = dist[u] + 1;
			par[v][0] = u;
			dfs(v, u);
		}
	}

	void assignParent ( int root ) {
		dfs(root, -1);

		for ( int j = 0; j < k; j++ ) {
			for ( int i = 0; i < n; i++ ) {
				int mid = par[i][j];
				if ( mid != -1 ) par[i][j + 1] = par[mid][j];
			}
		}
	}

	int solve ( int x, int y ) {
		if ( dist[x] < dist[y] ) swap(x, y);

		int diff = dist[x] - dist[y];
		int a = 0;
		while ( diff ) {
			if ( diff & 1 ) x = par[x][a];
			a++;
			diff >>= 1;
		}

		if ( x != y ) {
			for ( int i = k - 1; i >=0; i-- ) {
				if ( par[x][i] != -1 && par[x][i] != par[y][i] ) {
					x = par[x][i];
					y = par[y][i];
				}
			}
			x = par[x][0];
			y = par[y][0];
		}
		return x;
	}
};

