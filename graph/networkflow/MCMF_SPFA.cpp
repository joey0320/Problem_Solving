struct MCMF {
	typedef ll flow_t;
	const flow_t IINF = numeric_limits<flow_t>::max();

	struct Edge {
		int to, ri;
		flow_t cap, cost;
	};

	int n;
	vector<vector<Edge>> graph;
	vector<int> pv, pe;
	vector<flow_t> dist;
	vector<bool> inq;

	void init ( int sz ) {
		n = sz;
		graph.resize(n);
		pv.resize(n);
		pe.resize(n);
		dist.resize(n);
		inq.resize(n);
	}

	void addedge ( int u, int v, flow_t cap, flow_t cost ) {
		Edge forward = { v, (int) graph[v].size(), cap, cost };
		Edge reverse = { u, (int) graph[u].size(), 0,  -cost };
		graph[u].push_back( forward );
		graph[v].push_back( reverse );
	}

	bool spfa ( int source, int sink, flow_t& totflow, flow_t& totcost ) {
		fill( dist.begin(), dist.end(), IINF );
		fill( inq.begin(), inq.end(), false );

		queue<int> q;
		q.push(source);
		dist[source] = 0, inq[source] = true;

		while ( !q.empty() ) {
			int u = q.front();
			q.pop();
			inq[u] = false;

			for ( int i = 0; i < (int) graph[u].size(); i++ ) {
				Edge& e = graph[u][i];
				if ( e.cap > 0 && dist[e.to] > dist[u] + e.cost ) {
					dist[e.to] = dist[u] + e.cost;
					pv[e.to] = u, pe[e.to] = i;
					if ( !inq[e.to] ) {
						q.push(e.to);
						inq[e.to] = true;
					}
				}
			}
		}

		if ( dist[sink] == IINF ) return false;
		// add this limit when we don't require maxflow
		// if( dist[sink] > 0 ) return false;

		flow_t block_flow = IINF;
		for ( int v = sink; v != source; v = pv[v] ) {
			block_flow = min( block_flow, graph[pv[v]][pe[v]].cap );
		}
		for ( int v = sink; v !=source; v = pv[v] ) {
			int ri = graph[pv[v]][pe[v]].ri;
			graph[pv[v]][pe[v]].cap -= block_flow;
			graph[v][ri].cap += block_flow;
		}
		totflow += block_flow;
		totcost += block_flow * dist[sink];
		return true;
	}

	pair<flow_t, flow_t> solve ( int source, int sink ) {
		flow_t totflow = 0, totcost = 0;
		while ( spfa(source, sink, totflow, totcost) );
		return {totflow, totcost};
	}
};

