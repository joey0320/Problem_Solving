bool bellmanford(int s) {
	d[s] = 0;
	bool isneg = false;
	for (int i = 1; i <= V; i++) {
		for (int j = 0; j < edge.size(); j++) {
			int u = edge[j].u; int v = edge[j].v; int w = edge[j].w;
			if (d[u] == INF) continue;
			if ( d[v] > d[u] + w) {
				d[v] = d[u] + w;
				bef[v] = u;
			}
		}
	}
	for (int i = 1; i <= V; i++)
		check[i] = d[i];
	for (int i = 0; i < edge.size(); i++) {
		int u = edge[i].u; int v = edge[i].v; int w = edge[i].w;
		if (check[u] ==INF)continue;
		if (check[v] > check[u] + w) {
			check[v] = check[u] + w;
		}
	}
	for (int i = 1; i <= V; i++) {
		if (check[i] != d[i]) {
			isneg = true;
			neg.push_back(i);
		}
	}
	return isneg;
}