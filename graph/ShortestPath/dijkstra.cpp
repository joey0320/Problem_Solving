void dijkstra () {
	for ( int i = 1; i <= V; i++ ) dis[i] = numeric_limits<int>::max();

	priority_queue<pii> pq;
	pq.push({0, S});

	while ( !pq.empty() ) {
		int d = - pq.top().F;
		int u = pq.top().S;
		pq.pop();

		if ( d > dis[u] ) continue;
		dis[u] = d;

		for ( auto e : graph[u] ) {
			int v = e.F;
			int w = e.S;

			if ( dis[u] + w < dis[v] ) {
				dis[v] = dis[u] + w;
				pq.push( { -dis[v], v } );
			}
		}
	}
}
