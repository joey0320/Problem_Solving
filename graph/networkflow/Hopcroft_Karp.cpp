// version 2
// unmatched path : A - B
// matched path : A = B
// alternating path : A - B = A - B = A
// augmenting path : A - B = A - B

struct HopcroftKarp {
	int n, m;
	vector<vector<int>> graph; 
	vector<int> matchA, matchB;
	vector<int> level, start;

	void init ( int a, int b ) {
		n = a;
		m = b;
		graph.resize(n);
		matchA.assign(n, -1);
		matchB.assign(m, -1);
	}

	void addedge ( int u, int v ) {
		graph[u].push_back(v);
	}

	bool assignLevel () {
		memset(&level[0], -1, sizeof(level[0]) * level.size());
		
		queue<int> q;
		bool reachable = false;

		for ( int i = 0; i < n; i++ ) {
			if ( matchA[i] == - 1 ) {
				level[i] = 0;
				q.push(i);
			}
		}

		while ( !q.empty() ) {
			int u = q.front();
			q.pop();
			for ( auto v : graph[u] ) {
				int w = matchB[v];
				if ( w == - 1) {
					reachable = true; // if there is a node in B that is not yet matched
				}
				else if ( level[w] == - 1 ) { // A - B = A 
					level[w] = level[u] + 1;
					q.push(w);
				}
			}
		}
		return reachable;
	}

	int augmentpath ( int u ) {
		for ( int& i = start[u] ; i < (int) graph[u].size(); i++) {
			int v = graph[u][i];
			int w = matchB[v];
			if ( w != -1 && level[w] != level[u] + 1 ) continue; // cannot be A - B = A 
			if ( w == -1 || augmentpath(w) ) {
				// w = - 1: end of aug path
				// or find augment path recursively  ( A - B = A - B = A ) + ( A - B )
				matchA[u] = v;
				matchB[v] = u;
				return 1;
			}
		}
		return 0;
	}

	int solve () {
		level.resize(n);
		start.resize(m);
		int maxmatching = 0;
		while ( assignLevel() ) {
			memset( &start[0], 0, sizeof(start[0]) * start.size() );
			for ( int i = 0; i < n; i++ ) {
				if ( matchA[i] == - 1) maxmatching += augmentpath(i);
			}
		}
		return maxmatching;
	}
};
