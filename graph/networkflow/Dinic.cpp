struct Dinic{

	struct Edge{
		int to, ri, cap;
	};

	vector<vector<Edge>> graph;
	vector<int> level, start;
	int n;

	void init ( int sz ) {
		n = sz;
		graph.resize(n);
		for ( int i = 0; i < n ; i++ ) graph[i].clear();
	}

	void addedge ( int u, int v, int cap, int rcap = 0 ) {
		Edge forward = {v, (int) graph[v].size(), cap};
		Edge reverse = {u, (int) graph[u].size(), rcap};
		graph[u].push_back(forward);
		graph[v].push_back(reverse);
	}

	bool assign_level ( int source, int sink ) {
		memset(&level[0], 0, sizeof(level[0]) * level.size());
		level[source] = 1;
		queue<int> que;
		que.push(source);

		while ( !que.empty() && !level[sink] ) {
			int u = que.front();
			que.pop();

			for ( auto e : graph[u] ) {
				if ( level[e.to] || e.cap==0 ) continue;
				level[e.to] = level[u] + 1;
				que.push(e.to);
			}
		}
		return level[sink] != 0;
	}

	// if there exists an augmenting path, add to flow
	int blocking_flow ( int u, int sink, int flow ) {
		if ( u == sink ) return flow;
		for ( int &i = start[u]; i < (int)graph[u].size(); i++ ) {
			Edge &e = graph[u][i];
			if ( e.cap == 0 || level[e.to] != level[u] + 1) continue;
			if ( int f = blocking_flow(e.to, sink, min(flow, e.cap)) ) {
				graph[u][i].cap -= f;
				graph[e.to][e.ri].cap += f;
				return f;
			}
		}
		return 0;
	}

	int solve ( int source, int sink ) {
		level.resize(n);
		start.resize(n);
		int maxflow = 0;

		while ( assign_level(source, sink) ) {
			memset( &start[0], 0, sizeof(start[0]) * start.size());
			while ( int f = blocking_flow(source, sink, numeric_limits<int>::max()) )
				maxflow += f;
		}
		return maxflow;
	}
};
